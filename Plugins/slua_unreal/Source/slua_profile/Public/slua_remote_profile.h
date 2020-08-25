// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Containers/Queue.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "LuaMemoryProfile.h"
#include "Templates/SharedPointer.h"
#include "Serialization/ArrayWriter.h"
#include "Serialization/ArrayReader.h"
#include "Delegates/DelegateCombinations.h"

class FSocket;
class FTcpListener;

namespace NS_SLUA {
	class FProfileConnection;
	class FProfileMessage;
    
	typedef TSharedPtr<FProfileMessage, ESPMode::ThreadSafe> FProfileMessagePtr;
	DECLARE_DELEGATE_OneParam(FOnProfileMessageDelegate, FProfileMessagePtr);

	class FProfileServer : public FRunnable
	{
	public:
		FProfileServer();
		~FProfileServer();

		FOnProfileMessageDelegate& OnProfileMessageRecv();

        TArray<TSharedPtr<FProfileConnection>> GetConnections();
        
	protected:
		bool Init() override;
		uint32 Run() override;
		void Stop() override;
		
		void StopTransport();

	private:
		/** Callback for accepted connections to the local server. */
		bool HandleConnectionAccepted(FSocket* ClientSocket, const FIPv4Endpoint& ClientEndpoint);

		FRunnableThread* Thread;

		FIPv4Endpoint ListenEndpoint;

		FTcpListener* Listener;

		/** Current connections */
		TArray<TSharedPtr<FProfileConnection>> Connections;

		/** Holds a queue of pending connections. */
		TQueue<TSharedPtr<FProfileConnection>, EQueueMode::Mpsc> PendingConnections;
        
        FOnProfileMessageDelegate OnProfileMessageDelegate;

		bool bStop;
	};

	/**
	* Implements a TCP message tunnel connection.
	*/
	class FProfileConnection
		: public FRunnable
		, public TSharedFromThis<FProfileConnection>
	{
	public:
		FProfileConnection(FSocket* InSocket, const FIPv4Endpoint& InRemoteEndpoint);

		/** Virtual destructor. */
		virtual ~FProfileConnection();

		void Start();

	public:
		enum EConnectionState
		{
			STATE_Connecting,					// connecting but don't yet have RemoteNodeId
			STATE_Connected,					// connected and RemoteNodeId is valid
			STATE_Disconnected					// disconnected. Previous RemoteNodeId is retained
		};

		EConnectionState GetConnectionState() const;

        FSocket* GetSocket();
        
		bool ReceiveData(TSharedPtr<FProfileMessage, ESPMode::ThreadSafe>& OutMessage);
        
		void Close();

	private:
		//~ FRunnable interface
		virtual bool Init() override;
		virtual uint32 Run() override;
		virtual void Stop() override;
		virtual void Exit() override;

	protected:
		bool ReceiveMessages();

		/** Holds the IP endpoint of the remote client. */
		FIPv4Endpoint RemoteEndpoint;

		/** Holds the connection socket. */
		FSocket* Socket;

		FRunnableThread* Thread;

		/** Holds the total number of bytes received from the connection. */
		uint64 TotalBytesReceived;

		/** Holds the collection of received Messages. */
		TQueue<TSharedPtr<FProfileMessage, ESPMode::ThreadSafe>, EQueueMode::Mpsc> Inbox;

		/** Message data we're currently in the process of receiving, if any */
		TSharedPtr<FArrayReader, ESPMode::ThreadSafe> RecvMessageData;

		int32 RecvMessageDataRemaining;
        
        int hookEvent;

		EConnectionState ConnectionState;

		bool bRun;
	};

	class FProfileMessage
	{
	public:
		FProfileMessage();
		~FProfileMessage();

		bool Deserialize(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& Message);

	public:
		int Event;
		int64 Time;

		int Linedefined;
		FString Name;
		FString ShortSrc;
        
        //Memory infomation
        TArray<NS_SLUA::LuaMemInfo> memoryInfoList;
		TArray<NS_SLUA::LuaMemInfo> memoryIncrease;
		TArray<NS_SLUA::LuaMemInfo> memoryDecrease;
	};
}
