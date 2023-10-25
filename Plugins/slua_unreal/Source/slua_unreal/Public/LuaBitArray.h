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

class SLUA_UNREAL_API LuaBitArray
{
public:
    typedef uint32 WordType;

    LuaBitArray();
    LuaBitArray(int32 Len);
    LuaBitArray(const LuaBitArray& Other);
    LuaBitArray(LuaBitArray&& Other);
    
    ~LuaBitArray();

    bool Add(int32 Index);
    // Range[BeginIndex, EndIndex] include EndIndex, not Range[BeginIndex, EndIndex)
    bool AddRange(int32 BeginIndex, int32 EndIndex);
    bool Remove(int32 Index);
    bool RemoveRange(int32 BeginIndex, int32 EndIndex);
    bool Clear();
    bool MarkAll();
    bool IsEmpty() const;

    LuaBitArray& operator = (const LuaBitArray& Other);
    LuaBitArray& operator = (LuaBitArray&& Other);
    LuaBitArray& operator &= (const LuaBitArray& Other);
    LuaBitArray& operator |= (const LuaBitArray& Other);
    
    friend FArchive& operator<<(FArchive& Ar, const LuaBitArray& A)
    {
        int32 RealBitSize = 0;
        if (Ar.IsSaving())
        {
            for (int32 Index = A.BitSize - 1; Index >= 0; --Index)
            {
                if (A.BitData[Index] != 0)
                {
                    RealBitSize = Index + 1;
                    break;
                }
            }
        }

        Ar << RealBitSize;
        for (int32 Index = 0; Index < RealBitSize; ++Index)
        {
            if (Index < A.BitSize)
            {
                Ar << A.BitData[Index];
            }
            else
            {
                // Drop it
                WordType Bit;
                Ar << Bit;
            }
        }
        return Ar;
    }

    class FIterator
    {
    public:
        FORCEINLINE FIterator(const LuaBitArray& Array)
            : BitIndex(0)
            , MaxIndex(-1)
            , CurrentWord(0)
            , BitArray(Array)
        {
            for (int32 Index = BitArray.BitSize - 1; Index >= 0; --Index)
            {
                if (BitArray.BitData[Index])
                {
                    MaxIndex = Index;
                    break;
                }
            }

            for (int32 Index = 0; Index <= MaxIndex; ++Index)
            {
                if (BitArray.BitData[Index])
                {
                    BitIndex = Index;
                    CurrentWord = BitArray.BitData[Index];
                    break;
                }
            }
        }

        FORCEINLINE operator bool()
        {
            if (BitIndex < MaxIndex)
            {
                return true;
            }
            return CurrentWord != 0;
        }
        
        FORCEINLINE FIterator& operator++()
        {
            CurrentWord &= CurrentWord - 1;
            for (; CurrentWord == 0 && BitIndex < MaxIndex;)
            {
                CurrentWord = BitArray.BitData[++BitIndex];
            }
            return *this;
        }

        // From http://graphics.stanford.edu/~seander/bithacks.html
        FORCEINLINE static int32 Log2(WordType Power2Num)
        {
            //x=2^k
            static const int32 Log2Map[32]={31,0,27,1,28,18,23,2,29,21,19,12,24,9,14,3,30,26,17,22,20,11,8,13,25,16,10,7,15,6,5,4};
            return Log2Map[Power2Num*263572066>>27];
        }

        FORCEINLINE int32 operator * () const
        {
            return BitIndex * WordSize + Log2(CurrentWord ^ (CurrentWord & (CurrentWord - 1)));
        }

    protected:
        int32 BitIndex;
        int32 MaxIndex;
        WordType CurrentWord;
        const LuaBitArray& BitArray;
    };
    
protected:
    static constexpr WordType FullWordMask = (WordType)-1;
    static constexpr int32 WordSize = sizeof(WordType) * 8;
    static constexpr int32 UnitWordMask = WordSize - 1;

    int32 BitLength;
    int32 BitSize;
    WordType* BitData;
};
