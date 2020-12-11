// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "slua_remote_profile.h"
#include "slua_profile.h"
#include "Common/TcpListener.h"
#include "Templates/SharedPointer.h"
#include "SocketSubsystem.h"
#include "SluaUtil.h"
#include "LuaProfiler.h"

namespace NS_SLUA
{
	FProfileServer::FProfileServer()
		: Thread(nullptr)
		, bStop(true)
	{
		Thread = FRunnableThread::Create(this, TEXT("FProfileServer"), 0, TPri_Normal);
	}

	FProfileServer::~FProfileServer()
	{
		StopTransport();
        
		Thread->WaitForCompletion();
		SafeDelete(Thread);
	}

	FOnProfileMessageDelegate& FProfileServer::OnProfileMessageRecv()
	{
		return OnProfileMessageDelegate;
	}

	bool FProfileServer::Init()
	{
		bStop = false;

		ListenEndpoint.Address = FIPv4Address(0, 0, 0, 0);
		ListenEndpoint.Port = 8081;
		Listener = new FTcpListener(ListenEndpoint);
		Listener->OnConnectionAccepted().BindRaw(this, &FProfileServer::HandleConnectionAccepted);
		return true;
	}
    
    TArray<TSharedPtr<FProfileConnection>> FProfileServer::GetConnections() {
        return Connections;
    }

	uint32 FProfileServer::Run()
	{
		while (!bStop)
		{
			TSharedPtr<FProfileConnection> Connection;
			while (PendingConnections.Dequeue(Connection))
			{
				Connection->Start();
				Connections.Add(Connection);
			}

			int32 ActiveConnections = 0;
			for (int32 Index = 0; Index < Connections.Num(); Index++)
			{
				auto& conn = Connections[Index];

				// handle disconnected by remote
				switch (conn->GetConnectionState())
				{
				case FProfileConnection::STATE_Connected:
					ActiveConnections++;
					break;

				case FProfileConnection::STATE_Disconnected:
					Connections.RemoveAtSwap(Index);
					Index--;
					break;

				default:
					break;
				}
			}

			for (auto& conn : Connections)
			{
				TSharedPtr<FProfileMessage, ESPMode::ThreadSafe> Message;

				while (conn->ReceiveData(Message))
				{
					OnProfileMessageDelegate.ExecuteIfBound(Message);
				}
			}

			FPlatformProcess::Sleep(ActiveConnections > 0 ? 0.01f : 1.f);
		}
		return 0;
	}

	void FProfileServer::Stop()
	{
		bStop = true;
	}

	void FProfileServer::StopTransport()
	{
		bStop = true;

		if (Listener)
		{
			delete Listener;
			Listener = nullptr;
		}

		for (auto& Connection : Connections)
		{
			Connection->Close();
		}

		Connections.Empty();
		PendingConnections.Empty();
	}

	bool FProfileServer::HandleConnectionAccepted(FSocket* ClientSocket, const FIPv4Endpoint& ClientEndpoint)
	{
		PendingConnections.Enqueue(MakeShareable(new FProfileConnection(ClientSocket, ClientEndpoint)));

		return true;
	}

	FProfileConnection::FProfileConnection(FSocket* InSocket, const FIPv4Endpoint& InRemoteEndpoint)
		: RemoteEndpoint(InRemoteEndpoint)
		, Socket(InSocket)
		, Thread(nullptr)
		, TotalBytesReceived(0)
		, RecvMessageDataRemaining(0)
		, ConnectionState(EConnectionState::STATE_Connecting)
		, bRun(false)
	{
		int32 NewSize = 0;
		Socket->SetReceiveBufferSize(2 * 1024 * 1024, NewSize);
		Socket->SetSendBufferSize(2 * 1024 * 1024, NewSize);
	}

	FProfileConnection::~FProfileConnection()
	{
		if (Thread != nullptr)
		{
			if (bRun)
			{
				bRun = false;
				Thread->WaitForCompletion();
			}
			delete Thread;
		}

		if (Socket)
		{
			Socket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
			Socket = nullptr;
		}
	}

	void FProfileConnection::Start()
	{
		check(Thread == nullptr);
		bRun = true;
		Thread = FRunnableThread::Create(this, *FString::Printf(TEXT("FProfileConnection %s"), *RemoteEndpoint.ToString()), 128 * 1024, TPri_Normal);
	}

	FProfileConnection::EConnectionState FProfileConnection::GetConnectionState() const
	{
		return ConnectionState;
	}

	bool FProfileConnection::ReceiveData(TSharedPtr<FProfileMessage, ESPMode::ThreadSafe>& OutMessage)
	{
		if (Inbox.Dequeue(OutMessage))
		{
			return true;
		}
		return false;
	}

	void FProfileConnection::Close()
	{
		// let the thread shutdown on its own
		if (Thread != nullptr)
		{
			bRun = false;
			Thread->WaitForCompletion();
			delete Thread;
			Thread = nullptr;
		}

		// if there a socket, close it so our peer will get a quick disconnect notification
		if (Socket)
		{
			Socket->Close();
		}
	}

	bool FProfileConnection::Init()
	{
		ConnectionState = EConnectionState::STATE_Connected;
		return true;
	}

    FSocket* FProfileConnection::GetSocket()
    {
        if(Socket) return Socket;
        return nullptr;
    }
    
	uint32 FProfileConnection::Run()
	{
         
		while (bRun)
		{
			if ((!ReceiveMessages() || Socket->GetConnectionState() == SCS_ConnectionError) && bRun)
			{
				bRun = false;
			}

			FPlatformProcess::SleepNoStats(0.0001f);
		}

		ConnectionState = EConnectionState::STATE_Disconnected;
		return 0;
	}

	void FProfileConnection::Stop()
	{
		if (Socket)
		{
			Socket->Close();
		}
	}

	void FProfileConnection::Exit()
	{

	}

	bool FProfileConnection::ReceiveMessages()
	{
		ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
		uint32 PendingDataSize = 0;

		// check if the socket has closed
		{
			int32 BytesRead;
			uint8 Dummy;
			if (!Socket->Recv(&Dummy, 1, BytesRead, ESocketReceiveFlags::Peek))
			{
				UE_LOG(LogSluaProfile, Verbose, TEXT("Dummy read failed with code %d"), (int32)SocketSubsystem->GetLastErrorCode());
				return false;
			}
		}

		// Block waiting for some data
		if (!Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(1.0)))
		{
			return (Socket->GetConnectionState() != SCS_ConnectionError);
		}

		// keep going until we have no data.
		for (;;)
		{
			int32 BytesRead = 0;
			// See if we're in the process of receiving a (large) message
			if (RecvMessageDataRemaining == 0)
			{
				// no partial message. Try to receive the size of a message
				if (!Socket->HasPendingData(PendingDataSize) || (PendingDataSize < sizeof(uint32)))
				{
					// no messages
					return true;
				}

				FArrayReader MessagesizeData = FArrayReader(true);
                MessagesizeData.SetNumUninitialized(sizeof(uint32));

				// read message size from the stream
                BytesRead = 0;
                if (!Socket->Recv(MessagesizeData.GetData(), sizeof(uint32), BytesRead))
                {
                    UE_LOG(LogSluaProfile, Verbose, TEXT("In progress read failed with code %d"), (int32)SocketSubsystem->GetLastErrorCode());
                    return false;
                }

                check(BytesRead == sizeof(uint32));
                TotalBytesReceived += BytesRead;
				// Setup variables to receive the message
				MessagesizeData << RecvMessageDataRemaining;

				RecvMessageData = MakeShareable(new FArrayReader(true));
				RecvMessageData->SetNumUninitialized(RecvMessageDataRemaining);
				check(RecvMessageDataRemaining > 0);
			}

			BytesRead = 0;
			if (!Socket->Recv(RecvMessageData->GetData() + RecvMessageData->Num() - RecvMessageDataRemaining, RecvMessageDataRemaining, BytesRead))
			{
				UE_LOG(LogSluaProfile, Verbose, TEXT("Read failed with code %d"), (int32)SocketSubsystem->GetLastErrorCode());
				return false;
			}

			if (BytesRead > 0)
			{
				check(BytesRead <= RecvMessageDataRemaining);
				TotalBytesReceived += BytesRead;
				RecvMessageDataRemaining -= BytesRead;
				if (RecvMessageDataRemaining == 0)
				{
                    FProfileMessage* DeserializedMessage = new FProfileMessage();
                    if (DeserializedMessage->Deserialize(RecvMessageData))
                    {
                        Inbox.Enqueue(MakeShareable(DeserializedMessage));
                    }
					RecvMessageData.Reset();
				}
			}
			else
			{
				// no data
				return true;
			}
		}

		return true;
	}

	FProfileMessage::FProfileMessage()
		: Linedefined(-1)
		, Name()
		, ShortSrc()
    {

	}

	FProfileMessage::~FProfileMessage()
	{

	}

	bool FProfileMessage::Deserialize(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& Message)
	{
		FArrayReader& MessageReader = Message.ToSharedRef().Get();

		MessageReader << Event;
		switch (Event)
		{
		case NS_SLUA::ProfilerHookEvent::PHE_MEMORY_TICK:
			MessageReader << memoryInfoList;
			return true;
		case NS_SLUA::ProfilerHookEvent::PHE_MEMORY_INCREACE:
			MessageReader << memoryIncrease;
			return true;
		}
        
		MessageReader << Time;
		MessageReader << Linedefined;
		MessageReader << Name;
		MessageReader << ShortSrc;
        
		return true;
	}
}
