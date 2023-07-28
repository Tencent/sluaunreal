#pragma once

//#include <lstate.h> // For PUBG Mobile
#ifdef G
    #undef G
#endif

#include "CoreMinimal.h"
#include "UObject/CoreNative.h"
#include "Runtime/Launch/Resources/Version.h"

namespace NS_SLUA
{
    //typedef lua_State lua_State; // For PUBG Mobile

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
    #define CastField Cast
    typedef UProperty FProperty;
    typedef UField FField;
    typedef UClass FFieldClass;
    
    typedef UIntProperty FIntProperty;
    typedef UUInt32Property FUInt32Property;
    typedef UInt64Property FInt64Property;
    typedef UUInt64Property FUInt64Property;
    typedef UInt16Property FInt16Property;
    typedef UUInt16Property FUInt16Property;
    typedef UInt8Property FInt8Property;
    typedef UByteProperty FByteProperty;
    typedef UFloatProperty FFloatProperty;
    typedef UDoubleProperty FDoubleProperty;
    typedef UBoolProperty FBoolProperty;
    typedef UTextProperty FTextProperty;
    typedef UStrProperty FStrProperty;
    typedef UNameProperty FNameProperty;
    typedef UMulticastDelegateProperty FMulticastDelegateProperty;
    typedef UObjectProperty FObjectProperty;
    typedef UEnumProperty FEnumProperty;
    typedef UArrayProperty FArrayProperty;
    typedef UMapProperty FMapProperty;
    typedef USetProperty FSetProperty;
    typedef USoftObjectProperty FSoftObjectProperty;
    typedef USoftClassProperty FSoftClassProperty;
    typedef UWeakObjectProperty FWeakObjectProperty;
    typedef UDelegateProperty FDelegateProperty;
    typedef UStructProperty FStructProperty;
    typedef UClassProperty FClassProperty;
    typedef UInterfaceProperty FInterfaceProperty;
#else
    typedef FProperty FProperty;
    typedef FStructProperty FStructProperty;
    typedef FMapProperty FMapProperty;
    typedef FArrayProperty FArrayProperty;
    typedef FField FField;
#endif

#if (ENGINE_MINOR_VERSION<19) && (ENGINE_MAJOR_VERSION==4)
    typedef Native FNativeFuncPtr;
#else
    typedef FNativeFuncPtr FNativeFuncPtr;
#endif
}