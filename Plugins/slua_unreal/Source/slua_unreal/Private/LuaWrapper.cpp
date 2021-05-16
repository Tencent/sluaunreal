// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaWrapper.h"
#include "LuaObject.h"
#include "Runtime/Launch/Resources/Version.h"

namespace NS_SLUA {

	static UScriptStruct* FRotatorStruct = nullptr;
	static UScriptStruct* FTransformStruct = nullptr;
	static UScriptStruct* FLinearColorStruct = nullptr;
	static UScriptStruct* FColorStruct = nullptr;
	static UScriptStruct* FVectorStruct = nullptr;
	static UScriptStruct* FVector2DStruct = nullptr;
	static UScriptStruct* FRandomStreamStruct = nullptr;
	static UScriptStruct* FGuidStruct = nullptr;
	static UScriptStruct* FBox2DStruct = nullptr;
	static UScriptStruct* FFloatRangeBoundStruct = nullptr;
	static UScriptStruct* FFloatRangeStruct = nullptr;
	static UScriptStruct* FInt32RangeBoundStruct = nullptr;
	static UScriptStruct* FInt32RangeStruct = nullptr;
	static UScriptStruct* FFloatIntervalStruct = nullptr;
	static UScriptStruct* FInt32IntervalStruct = nullptr;
	static UScriptStruct* FPrimaryAssetTypeStruct = nullptr;
	static UScriptStruct* FPrimaryAssetIdStruct = nullptr;
	static UScriptStruct* FDateTimeStruct = nullptr;

	typedef void(*pushStructFunction)(lua_State* L, FStructProperty* p, uint8* parms);
	typedef void(*checkStructFunction)(lua_State* L, FStructProperty* p, uint8* parms, int i);

	TMap<UScriptStruct*, pushStructFunction> _pushStructMap;
	TMap<UScriptStruct*, checkStructFunction> _checkStructMap;

	static inline FRotator* __newFRotator() {
		return new FRotator();
	}

	static void __pushFRotator(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFRotator();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FRotator>(L, "FRotator", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFRotator(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FRotator*>(L, i);
		if (!v) {
			luaL_error(L, "check FRotator nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FTransform* __newFTransform() {
		return new FTransform();
	}

	static void __pushFTransform(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFTransform();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FTransform>(L, "FTransform", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFTransform(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FTransform*>(L, i);
		if (!v) {
			luaL_error(L, "check FTransform nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FLinearColor* __newFLinearColor() {
		return new FLinearColor();
	}

	static void __pushFLinearColor(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFLinearColor();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FLinearColor>(L, "FLinearColor", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFLinearColor(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FLinearColor*>(L, i);
		if (!v) {
			luaL_error(L, "check FLinearColor nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FColor* __newFColor() {
		return new FColor();
	}

	static void __pushFColor(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFColor();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FColor>(L, "FColor", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFColor(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FColor*>(L, i);
		if (!v) {
			luaL_error(L, "check FColor nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FVector* __newFVector() {
		return new FVector();
	}

	static void __pushFVector(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFVector();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FVector>(L, "FVector", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFVector(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FVector*>(L, i);
		if (!v) {
			luaL_error(L, "check FVector nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FVector2D* __newFVector2D() {
		return new FVector2D();
	}

	static void __pushFVector2D(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFVector2D();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FVector2D>(L, "FVector2D", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFVector2D(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FVector2D*>(L, i);
		if (!v) {
			luaL_error(L, "check FVector2D nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FRandomStream* __newFRandomStream() {
		return new FRandomStream();
	}

	static void __pushFRandomStream(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFRandomStream();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FRandomStream>(L, "FRandomStream", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFRandomStream(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FRandomStream*>(L, i);
		if (!v) {
			luaL_error(L, "check FRandomStream nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FGuid* __newFGuid() {
		return new FGuid();
	}

	static void __pushFGuid(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFGuid();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FGuid>(L, "FGuid", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFGuid(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FGuid*>(L, i);
		if (!v) {
			luaL_error(L, "check FGuid nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FBox2D* __newFBox2D() {
		return new FBox2D();
	}

	static void __pushFBox2D(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFBox2D();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FBox2D>(L, "FBox2D", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFBox2D(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FBox2D*>(L, i);
		if (!v) {
			luaL_error(L, "check FBox2D nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FFloatRangeBound* __newFFloatRangeBound() {
		return new FFloatRangeBound();
	}

	static void __pushFFloatRangeBound(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFFloatRangeBound();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFFloatRangeBound(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FFloatRangeBound*>(L, i);
		if (!v) {
			luaL_error(L, "check FFloatRangeBound nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FFloatRange* __newFFloatRange() {
		return new FFloatRange();
	}

	static void __pushFFloatRange(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFFloatRange();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FFloatRange>(L, "FFloatRange", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFFloatRange(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FFloatRange*>(L, i);
		if (!v) {
			luaL_error(L, "check FFloatRange nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FInt32RangeBound* __newFInt32RangeBound() {
		return new FInt32RangeBound();
	}

	static void __pushFInt32RangeBound(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFInt32RangeBound();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFInt32RangeBound(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FInt32RangeBound*>(L, i);
		if (!v) {
			luaL_error(L, "check FInt32RangeBound nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FInt32Range* __newFInt32Range() {
		return new FInt32Range();
	}

	static void __pushFInt32Range(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFInt32Range();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FInt32Range>(L, "FInt32Range", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFInt32Range(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FInt32Range*>(L, i);
		if (!v) {
			luaL_error(L, "check FInt32Range nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FFloatInterval* __newFFloatInterval() {
		return new FFloatInterval();
	}

	static void __pushFFloatInterval(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFFloatInterval();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FFloatInterval>(L, "FFloatInterval", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFFloatInterval(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FFloatInterval*>(L, i);
		if (!v) {
			luaL_error(L, "check FFloatInterval nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FInt32Interval* __newFInt32Interval() {
		return new FInt32Interval();
	}

	static void __pushFInt32Interval(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFInt32Interval();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FInt32Interval>(L, "FInt32Interval", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFInt32Interval(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FInt32Interval*>(L, i);
		if (!v) {
			luaL_error(L, "check FInt32Interval nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FPrimaryAssetType* __newFPrimaryAssetType() {
		return new FPrimaryAssetType();
	}

	static void __pushFPrimaryAssetType(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFPrimaryAssetType();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FPrimaryAssetType>(L, "FPrimaryAssetType", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFPrimaryAssetType(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FPrimaryAssetType*>(L, i);
		if (!v) {
			luaL_error(L, "check FPrimaryAssetType nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FPrimaryAssetId* __newFPrimaryAssetId() {
		return new FPrimaryAssetId();
	}

	static void __pushFPrimaryAssetId(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFPrimaryAssetId();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFPrimaryAssetId(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FPrimaryAssetId*>(L, i);
		if (!v) {
			luaL_error(L, "check FPrimaryAssetId nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	static inline FDateTime* __newFDateTime() {
		return new FDateTime();
	}

	static void __pushFDateTime(lua_State* L, FStructProperty* p, uint8* parms) {
		auto ptr = __newFDateTime();
		p->CopyCompleteValue(ptr, parms);
		LuaObject::push<FDateTime>(L, "FDateTime", ptr, UD_AUTOGC | UD_VALUETYPE);
	}

	static void __checkFDateTime(lua_State* L, FStructProperty* p, uint8* parms, int i) {
		auto v = LuaObject::checkValue<FDateTime*>(L, i);
		if (!v) {
			luaL_error(L, "check FDateTime nil value");
			return;
		}
		p->CopyCompleteValue(parms, v);
	}

	struct FRotatorWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FRotator();
				LuaObject::push<FRotator>(L, "FRotator", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InF = LuaObject::checkValue<float>(L, 2);
				auto self = new FRotator(InF);
				LuaObject::push<FRotator>(L, "FRotator", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 4) {
				auto InPitch = LuaObject::checkValue<float>(L, 2);
				auto InYaw = LuaObject::checkValue<float>(L, 3);
				auto InRoll = LuaObject::checkValue<float>(L, 4);
				auto self = new FRotator(InPitch, InYaw, InRoll);
				LuaObject::push<FRotator>(L, "FRotator", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FRotator);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __add(lua_State* L) {
			CheckSelf(FRotator);
			if (LuaObject::matchType(L, 2, "FRotator")) {
				auto R = LuaObject::checkValue<FRotator*>(L, 2);
				auto& RRef = *R;
				auto ret = __newFRotator();
				*ret = (*self + RRef);
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FRotator operator__add error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __sub(lua_State* L) {
			CheckSelf(FRotator);
			if (LuaObject::matchType(L, 2, "FRotator")) {
				auto R = LuaObject::checkValue<FRotator*>(L, 2);
				auto& RRef = *R;
				auto ret = __newFRotator();
				*ret = (*self - RRef);
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FRotator operator__sub error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __mul(lua_State* L) {
			CheckSelf(FRotator);
			if (lua_isnumber(L, 2)) {
				auto Scale = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFRotator();
				*ret = (*self * Scale);
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FRotator operator__mul error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FRotator);
			if (LuaObject::matchType(L, 2, "FRotator")) {
				auto R = LuaObject::checkValue<FRotator*>(L, 2);
				auto& RRef = *R;
				auto ret = (*self == RRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int get_Pitch(lua_State* L) {
			CheckSelf(FRotator);
			auto& Pitch = self->Pitch;
			LuaObject::push(L, Pitch);
			return 1;
		}

		static int set_Pitch(lua_State* L) {
			CheckSelf(FRotator);
			auto& Pitch = self->Pitch;
			auto PitchIn = LuaObject::checkValue<float>(L, 2);
			Pitch = PitchIn;
			LuaObject::push(L, PitchIn);
			return 1;
		}

		static int get_Yaw(lua_State* L) {
			CheckSelf(FRotator);
			auto& Yaw = self->Yaw;
			LuaObject::push(L, Yaw);
			return 1;
		}

		static int set_Yaw(lua_State* L) {
			CheckSelf(FRotator);
			auto& Yaw = self->Yaw;
			auto YawIn = LuaObject::checkValue<float>(L, 2);
			Yaw = YawIn;
			LuaObject::push(L, YawIn);
			return 1;
		}

		static int get_Roll(lua_State* L) {
			CheckSelf(FRotator);
			auto& Roll = self->Roll;
			LuaObject::push(L, Roll);
			return 1;
		}

		static int set_Roll(lua_State* L) {
			CheckSelf(FRotator);
			auto& Roll = self->Roll;
			auto RollIn = LuaObject::checkValue<float>(L, 2);
			Roll = RollIn;
			LuaObject::push(L, RollIn);
			return 1;
		}

		static int get_ZeroRotator(lua_State* L) {
			auto& ZeroRotator = FRotator::ZeroRotator;
			LuaObject::push<FRotator>(L, "FRotator", &ZeroRotator);
			return 1;
		}

		static int DiagnosticCheckNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				self->DiagnosticCheckNaN();
				return 0;
			}
			if (argc == 2) {
				CheckSelf(FRotator);
				auto Message = LuaObject::checkValue<const char*>(L, 2);
				auto MessageVal = FString(UTF8_TO_TCHAR(Message));
				self->DiagnosticCheckNaN(*MessageVal);
				return 0;
			}
			luaL_error(L, "call FRotator::DiagnosticCheckNaN error, argc=%d", argc);
			return 0;
		}

		static int IsNearlyZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRotator);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsNearlyZero(Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::IsNearlyZero error, argc=%d", argc);
			return 0;
		}

		static int IsZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = self->IsZero();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::IsZero error, argc=%d", argc);
			return 0;
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FRotator);
				auto R = LuaObject::checkValue<FRotator*>(L, 2);
				auto& RRef = *R;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(RRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::Equals error, argc=%d", argc);
			return 0;
		}

		static int Add(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				CheckSelf(FRotator);
				auto DeltaPitch = LuaObject::checkValue<float>(L, 2);
				auto DeltaYaw = LuaObject::checkValue<float>(L, 3);
				auto DeltaRoll = LuaObject::checkValue<float>(L, 4);
				auto ret = __newFRotator();
				*ret = self->Add(DeltaPitch, DeltaYaw, DeltaRoll);
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::Add error, argc=%d", argc);
			return 0;
		}

		static int GetInverse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = __newFRotator();
				*ret = self->GetInverse();
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::GetInverse error, argc=%d", argc);
			return 0;
		}

		static int GridSnap(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRotator);
				auto RotGrid = LuaObject::checkValue<FRotator*>(L, 2);
				auto& RotGridRef = *RotGrid;
				auto ret = __newFRotator();
				*ret = self->GridSnap(RotGridRef);
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::GridSnap error, argc=%d", argc);
			return 0;
		}

		static int Vector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = __newFVector();
				*ret = self->Vector();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::Vector error, argc=%d", argc);
			return 0;
		}

		static int Euler(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = __newFVector();
				*ret = self->Euler();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::Euler error, argc=%d", argc);
			return 0;
		}

		static int RotateVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRotator);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->RotateVector(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::RotateVector error, argc=%d", argc);
			return 0;
		}

		static int UnrotateVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRotator);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->UnrotateVector(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::UnrotateVector error, argc=%d", argc);
			return 0;
		}

		static int Clamp(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = __newFRotator();
				*ret = self->Clamp();
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::Clamp error, argc=%d", argc);
			return 0;
		}

		static int GetNormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = __newFRotator();
				*ret = self->GetNormalized();
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::GetNormalized error, argc=%d", argc);
			return 0;
		}

		static int GetDenormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = __newFRotator();
				*ret = self->GetDenormalized();
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::GetDenormalized error, argc=%d", argc);
			return 0;
		}

		static int GetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRotator);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto AxisVal = (EAxis::Type)Axis;
				auto ret = self->GetComponentForAxis(AxisVal);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::GetComponentForAxis error, argc=%d", argc);
			return 0;
		}

		static int SetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FRotator);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto AxisVal = (EAxis::Type)Axis;
				auto Component = LuaObject::checkValue<float>(L, 3);
				self->SetComponentForAxis(AxisVal, Component);
				return 0;
			}
			luaL_error(L, "call FRotator::SetComponentForAxis error, argc=%d", argc);
			return 0;
		}

		static int Normalize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				self->Normalize();
				return 0;
			}
			luaL_error(L, "call FRotator::Normalize error, argc=%d", argc);
			return 0;
		}

		static int GetWindingAndRemainder(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FRotator);
				auto Winding = LuaObject::checkValue<FRotator*>(L, 2);
				auto& WindingRef = *Winding;
				auto Remainder = LuaObject::checkValue<FRotator*>(L, 3);
				auto& RemainderRef = *Remainder;
				self->GetWindingAndRemainder(WindingRef, RemainderRef);
				LuaObject::push<FRotator>(L, "FRotator", Winding);
				LuaObject::push<FRotator>(L, "FRotator", Remainder);
				return 2;
			}
			luaL_error(L, "call FRotator::GetWindingAndRemainder error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::ToString error, argc=%d", argc);
			return 0;
		}

		static int ToCompactString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = self->ToCompactString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::ToCompactString error, argc=%d", argc);
			return 0;
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRotator);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::InitFromString error, argc=%d", argc);
			return 0;
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRotator);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::ContainsNaN error, argc=%d", argc);
			return 0;
		}

		static int ClampAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Angle = LuaObject::checkValue<float>(L, 1);
				auto ret = FRotator::ClampAxis(Angle);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::ClampAxis error, argc=%d", argc);
			return 0;
		}

		static int NormalizeAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Angle = LuaObject::checkValue<float>(L, 1);
				auto ret = FRotator::NormalizeAxis(Angle);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::NormalizeAxis error, argc=%d", argc);
			return 0;
		}

		static int CompressAxisToByte(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Angle = LuaObject::checkValue<float>(L, 1);
				auto ret = FRotator::CompressAxisToByte(Angle);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::CompressAxisToByte error, argc=%d", argc);
			return 0;
		}

		static int DecompressAxisFromByte(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Angle = LuaObject::checkValue<int>(L, 1);
				auto AngleVal = (unsigned short)Angle;
				auto ret = FRotator::DecompressAxisFromByte(AngleVal);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::DecompressAxisFromByte error, argc=%d", argc);
			return 0;
		}

		static int CompressAxisToShort(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Angle = LuaObject::checkValue<float>(L, 1);
				auto ret = FRotator::CompressAxisToShort(Angle);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::CompressAxisToShort error, argc=%d", argc);
			return 0;
		}

		static int DecompressAxisFromShort(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Angle = LuaObject::checkValue<int>(L, 1);
				auto AngleVal = (unsigned short)Angle;
				auto ret = FRotator::DecompressAxisFromShort(AngleVal);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRotator::DecompressAxisFromShort error, argc=%d", argc);
			return 0;
		}

		static int MakeFromEuler(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Euler = LuaObject::checkValue<FVector*>(L, 1);
				auto& EulerRef = *Euler;
				auto ret = __newFRotator();
				*ret = FRotator::MakeFromEuler(EulerRef);
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRotator::MakeFromEuler error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FRotator");
			LuaObject::addOperator(L, "__add", __add);
			LuaObject::addOperator(L, "__sub", __sub);
			LuaObject::addOperator(L, "__mul", __mul);
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addField(L, "Pitch", get_Pitch, set_Pitch, true);
			LuaObject::addField(L, "Yaw", get_Yaw, set_Yaw, true);
			LuaObject::addField(L, "Roll", get_Roll, set_Roll, true);
			LuaObject::addField(L, "ZeroRotator", get_ZeroRotator, nullptr, false);
			LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
			LuaObject::addMethod(L, "IsNearlyZero", IsNearlyZero, true);
			LuaObject::addMethod(L, "IsZero", IsZero, true);
			LuaObject::addMethod(L, "Equals", Equals, true);
			LuaObject::addMethod(L, "Add", Add, true);
			LuaObject::addMethod(L, "GetInverse", GetInverse, true);
			LuaObject::addMethod(L, "GridSnap", GridSnap, true);
			LuaObject::addMethod(L, "Vector", Vector, true);
			LuaObject::addMethod(L, "Euler", Euler, true);
			LuaObject::addMethod(L, "RotateVector", RotateVector, true);
			LuaObject::addMethod(L, "UnrotateVector", UnrotateVector, true);
			LuaObject::addMethod(L, "Clamp", Clamp, true);
			LuaObject::addMethod(L, "GetNormalized", GetNormalized, true);
			LuaObject::addMethod(L, "GetDenormalized", GetDenormalized, true);
			LuaObject::addMethod(L, "GetComponentForAxis", GetComponentForAxis, true);
			LuaObject::addMethod(L, "SetComponentForAxis", SetComponentForAxis, true);
			LuaObject::addMethod(L, "Normalize", Normalize, true);
			LuaObject::addMethod(L, "GetWindingAndRemainder", GetWindingAndRemainder, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "ToCompactString", ToCompactString, true);
			LuaObject::addMethod(L, "InitFromString", InitFromString, true);
			LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
			LuaObject::addMethod(L, "ClampAxis", ClampAxis, false);
			LuaObject::addMethod(L, "NormalizeAxis", NormalizeAxis, false);
			LuaObject::addMethod(L, "CompressAxisToByte", CompressAxisToByte, false);
			LuaObject::addMethod(L, "DecompressAxisFromByte", DecompressAxisFromByte, false);
			LuaObject::addMethod(L, "CompressAxisToShort", CompressAxisToShort, false);
			LuaObject::addMethod(L, "DecompressAxisFromShort", DecompressAxisFromShort, false);
			LuaObject::addMethod(L, "MakeFromEuler", MakeFromEuler, false);
			LuaObject::finishType(L, "FRotator", __ctor, __gc);
		}

	};

	struct FTransformWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FTransform();
				LuaObject::push<FTransform>(L, "FTransform", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InTranslation = LuaObject::checkValue<FVector*>(L, 2);
				auto& InTranslationRef = *InTranslation;
				auto self = new FTransform(InTranslationRef);
				LuaObject::push<FTransform>(L, "FTransform", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 5) {
				auto InX = LuaObject::checkValue<FVector*>(L, 2);
				auto& InXRef = *InX;
				auto InY = LuaObject::checkValue<FVector*>(L, 3);
				auto& InYRef = *InY;
				auto InZ = LuaObject::checkValue<FVector*>(L, 4);
				auto& InZRef = *InZ;
				auto InTranslation = LuaObject::checkValue<FVector*>(L, 5);
				auto& InTranslationRef = *InTranslation;
				auto self = new FTransform(InXRef, InYRef, InZRef, InTranslationRef);
				LuaObject::push<FTransform>(L, "FTransform", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FTransform);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __add(lua_State* L) {
			CheckSelf(FTransform);
			if (LuaObject::matchType(L, 2, "FTransform")) {
				auto Atom = LuaObject::checkValue<FTransform*>(L, 2);
				auto& AtomRef = *Atom;
				auto ret = __newFTransform();
				*ret = (*self + AtomRef);
				LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FTransform operator__add error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __mul(lua_State* L) {
			CheckSelf(FTransform);
			if (LuaObject::matchType(L, 2, "FTransform")) {
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = __newFTransform();
				*ret = (*self * OtherRef);
				LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FTransform operator__mul error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int get_Identity(lua_State* L) {
			auto& Identity = FTransform::Identity;
			LuaObject::push<FTransform>(L, "FTransform", &Identity);
			return 1;
		}

		static int DiagnosticCheckNaN_Translate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->DiagnosticCheckNaN_Translate();
				return 0;
			}
			luaL_error(L, "call FTransform::DiagnosticCheckNaN_Translate error, argc=%d", argc);
			return 0;
		}

		static int DiagnosticCheckNaN_Rotate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->DiagnosticCheckNaN_Rotate();
				return 0;
			}
			luaL_error(L, "call FTransform::DiagnosticCheckNaN_Rotate error, argc=%d", argc);
			return 0;
		}

		static int DiagnosticCheckNaN_Scale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->DiagnosticCheckNaN_Scale3D();
				return 0;
			}
			luaL_error(L, "call FTransform::DiagnosticCheckNaN_Scale3D error, argc=%d", argc);
			return 0;
		}

		static int DiagnosticCheckNaN_All(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->DiagnosticCheckNaN_All();
				return 0;
			}
			luaL_error(L, "call FTransform::DiagnosticCheckNaN_All error, argc=%d", argc);
			return 0;
		}

		static int DiagnosticCheck_IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->DiagnosticCheck_IsValid();
				return 0;
			}
			luaL_error(L, "call FTransform::DiagnosticCheck_IsValid error, argc=%d", argc);
			return 0;
		}

		static int DebugPrint(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->DebugPrint();
				return 0;
			}
			luaL_error(L, "call FTransform::DebugPrint error, argc=%d", argc);
			return 0;
		}

		static int ToHumanReadableString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->ToHumanReadableString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::ToHumanReadableString error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::ToString error, argc=%d", argc);
			return 0;
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::InitFromString error, argc=%d", argc);
			return 0;
		}

		static int Inverse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = __newFTransform();
				*ret = self->Inverse();
				LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::Inverse error, argc=%d", argc);
			return 0;
		}

		static int Blend(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				CheckSelf(FTransform);
				auto Atom1 = LuaObject::checkValue<FTransform*>(L, 2);
				auto& Atom1Ref = *Atom1;
				auto Atom2 = LuaObject::checkValue<FTransform*>(L, 3);
				auto& Atom2Ref = *Atom2;
				auto Alpha = LuaObject::checkValue<float>(L, 4);
				self->Blend(Atom1Ref, Atom2Ref, Alpha);
				return 0;
			}
			luaL_error(L, "call FTransform::Blend error, argc=%d", argc);
			return 0;
		}

		static int BlendWith(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto OtherAtom = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherAtomRef = *OtherAtom;
				auto Alpha = LuaObject::checkValue<float>(L, 3);
				self->BlendWith(OtherAtomRef, Alpha);
				return 0;
			}
			luaL_error(L, "call FTransform::BlendWith error, argc=%d", argc);
			return 0;
		}

		static int ScaleTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto InScale3D = LuaObject::checkValue<FVector*>(L, 2);
				auto& InScale3DRef = *InScale3D;
				self->ScaleTranslation(InScale3DRef);
				return 0;
			}
			luaL_error(L, "call FTransform::ScaleTranslation error, argc=%d", argc);
			return 0;
		}

		static int RemoveScaling(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				self->RemoveScaling(Tolerance);
				return 0;
			}
			luaL_error(L, "call FTransform::RemoveScaling error, argc=%d", argc);
			return 0;
		}

		static int GetMaximumAxisScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->GetMaximumAxisScale();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::GetMaximumAxisScale error, argc=%d", argc);
			return 0;
		}

		static int GetMinimumAxisScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->GetMinimumAxisScale();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::GetMinimumAxisScale error, argc=%d", argc);
			return 0;
		}

		static int GetRelativeTransform(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = __newFTransform();
				*ret = self->GetRelativeTransform(OtherRef);
				LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetRelativeTransform error, argc=%d", argc);
			return 0;
		}

		static int GetRelativeTransformReverse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = __newFTransform();
				*ret = self->GetRelativeTransformReverse(OtherRef);
				LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetRelativeTransformReverse error, argc=%d", argc);
			return 0;
		}

		static int SetToRelativeTransform(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto ParentTransform = LuaObject::checkValue<FTransform*>(L, 2);
				auto& ParentTransformRef = *ParentTransform;
				self->SetToRelativeTransform(ParentTransformRef);
				return 0;
			}
			luaL_error(L, "call FTransform::SetToRelativeTransform error, argc=%d", argc);
			return 0;
		}

		static int TransformPosition(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->TransformPosition(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::TransformPosition error, argc=%d", argc);
			return 0;
		}

		static int TransformPositionNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->TransformPositionNoScale(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::TransformPositionNoScale error, argc=%d", argc);
			return 0;
		}

		static int InverseTransformPosition(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->InverseTransformPosition(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::InverseTransformPosition error, argc=%d", argc);
			return 0;
		}

		static int InverseTransformPositionNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->InverseTransformPositionNoScale(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::InverseTransformPositionNoScale error, argc=%d", argc);
			return 0;
		}

		static int TransformVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->TransformVector(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::TransformVector error, argc=%d", argc);
			return 0;
		}

		static int TransformVectorNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->TransformVectorNoScale(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::TransformVectorNoScale error, argc=%d", argc);
			return 0;
		}

		static int InverseTransformVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->InverseTransformVector(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::InverseTransformVector error, argc=%d", argc);
			return 0;
		}

		static int InverseTransformVectorNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = self->InverseTransformVectorNoScale(VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::InverseTransformVectorNoScale error, argc=%d", argc);
			return 0;
		}

		static int GetScaled(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Scale = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFTransform();
				*ret = self->GetScaled(Scale);
				LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetScaled error, argc=%d", argc);
			return 0;
		}

		static int GetScaledAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto InAxis = LuaObject::checkValue<int>(L, 2);
				auto InAxisVal = (EAxis::Type)InAxis;
				auto ret = __newFVector();
				*ret = self->GetScaledAxis(InAxisVal);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetScaledAxis error, argc=%d", argc);
			return 0;
		}

		static int GetUnitAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto InAxis = LuaObject::checkValue<int>(L, 2);
				auto InAxisVal = (EAxis::Type)InAxis;
				auto ret = __newFVector();
				*ret = self->GetUnitAxis(InAxisVal);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetUnitAxis error, argc=%d", argc);
			return 0;
		}

		static int Mirror(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto MirrorAxis = LuaObject::checkValue<int>(L, 2);
				auto MirrorAxisVal = (EAxis::Type)MirrorAxis;
				auto FlipAxis = LuaObject::checkValue<int>(L, 3);
				auto FlipAxisVal = (EAxis::Type)FlipAxis;
				self->Mirror(MirrorAxisVal, FlipAxisVal);
				return 0;
			}
			luaL_error(L, "call FTransform::Mirror error, argc=%d", argc);
			return 0;
		}

		static int GetLocation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = __newFVector();
				*ret = self->GetLocation();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetLocation error, argc=%d", argc);
			return 0;
		}

		static int Rotator(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = __newFRotator();
				*ret = self->Rotator();
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::Rotator error, argc=%d", argc);
			return 0;
		}

		static int GetDeterminant(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->GetDeterminant();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::GetDeterminant error, argc=%d", argc);
			return 0;
		}

		static int SetLocation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Origin = LuaObject::checkValue<FVector*>(L, 2);
				auto& OriginRef = *Origin;
				self->SetLocation(OriginRef);
				return 0;
			}
			luaL_error(L, "call FTransform::SetLocation error, argc=%d", argc);
			return 0;
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::ContainsNaN error, argc=%d", argc);
			return 0;
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::IsValid error, argc=%d", argc);
			return 0;
		}

		static int RotationEquals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->RotationEquals(OtherRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::RotationEquals error, argc=%d", argc);
			return 0;
		}

		static int TranslationEquals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->TranslationEquals(OtherRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::TranslationEquals error, argc=%d", argc);
			return 0;
		}

		static int Scale3DEquals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Scale3DEquals(OtherRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::Scale3DEquals error, argc=%d", argc);
			return 0;
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(OtherRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::Equals error, argc=%d", argc);
			return 0;
		}

		static int EqualsNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->EqualsNoScale(OtherRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::EqualsNoScale error, argc=%d", argc);
			return 0;
		}

		static int SetIdentity(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->SetIdentity();
				return 0;
			}
			luaL_error(L, "call FTransform::SetIdentity error, argc=%d", argc);
			return 0;
		}

		static int MultiplyScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Scale3DMultiplier = LuaObject::checkValue<FVector*>(L, 2);
				auto& Scale3DMultiplierRef = *Scale3DMultiplier;
				self->MultiplyScale3D(Scale3DMultiplierRef);
				return 0;
			}
			luaL_error(L, "call FTransform::MultiplyScale3D error, argc=%d", argc);
			return 0;
		}

		static int SetTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto NewTranslation = LuaObject::checkValue<FVector*>(L, 2);
				auto& NewTranslationRef = *NewTranslation;
				self->SetTranslation(NewTranslationRef);
				return 0;
			}
			luaL_error(L, "call FTransform::SetTranslation error, argc=%d", argc);
			return 0;
		}

		static int CopyTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				self->CopyTranslation(OtherRef);
				return 0;
			}
			luaL_error(L, "call FTransform::CopyTranslation error, argc=%d", argc);
			return 0;
		}

		static int AddToTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto DeltaTranslation = LuaObject::checkValue<FVector*>(L, 2);
				auto& DeltaTranslationRef = *DeltaTranslation;
				self->AddToTranslation(DeltaTranslationRef);
				return 0;
			}
			luaL_error(L, "call FTransform::AddToTranslation error, argc=%d", argc);
			return 0;
		}

		static int CopyRotation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				self->CopyRotation(OtherRef);
				return 0;
			}
			luaL_error(L, "call FTransform::CopyRotation error, argc=%d", argc);
			return 0;
		}

		static int SetScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto NewScale3D = LuaObject::checkValue<FVector*>(L, 2);
				auto& NewScale3DRef = *NewScale3D;
				self->SetScale3D(NewScale3DRef);
				return 0;
			}
			luaL_error(L, "call FTransform::SetScale3D error, argc=%d", argc);
			return 0;
		}

		static int CopyScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto& OtherRef = *Other;
				self->CopyScale3D(OtherRef);
				return 0;
			}
			luaL_error(L, "call FTransform::CopyScale3D error, argc=%d", argc);
			return 0;
		}

		static int SetTranslationAndScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FTransform);
				auto NewTranslation = LuaObject::checkValue<FVector*>(L, 2);
				auto& NewTranslationRef = *NewTranslation;
				auto NewScale3D = LuaObject::checkValue<FVector*>(L, 3);
				auto& NewScale3DRef = *NewScale3D;
				self->SetTranslationAndScale3D(NewTranslationRef, NewScale3DRef);
				return 0;
			}
			luaL_error(L, "call FTransform::SetTranslationAndScale3D error, argc=%d", argc);
			return 0;
		}

		static int NormalizeRotation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				self->NormalizeRotation();
				return 0;
			}
			luaL_error(L, "call FTransform::NormalizeRotation error, argc=%d", argc);
			return 0;
		}

		static int IsRotationNormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = self->IsRotationNormalized();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::IsRotationNormalized error, argc=%d", argc);
			return 0;
		}

		static int GetTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = __newFVector();
				*ret = self->GetTranslation();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetTranslation error, argc=%d", argc);
			return 0;
		}

		static int GetScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FTransform);
				auto ret = __newFVector();
				*ret = self->GetScale3D();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetScale3D error, argc=%d", argc);
			return 0;
		}

		static int CopyRotationPart(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto SrcBA = LuaObject::checkValue<FTransform*>(L, 2);
				auto& SrcBARef = *SrcBA;
				self->CopyRotationPart(SrcBARef);
				return 0;
			}
			luaL_error(L, "call FTransform::CopyRotationPart error, argc=%d", argc);
			return 0;
		}

		static int CopyTranslationAndScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FTransform);
				auto SrcBA = LuaObject::checkValue<FTransform*>(L, 2);
				auto& SrcBARef = *SrcBA;
				self->CopyTranslationAndScale3D(SrcBARef);
				return 0;
			}
			luaL_error(L, "call FTransform::CopyTranslationAndScale3D error, argc=%d", argc);
			return 0;
		}

		static int AnyHasNegativeScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto InScale3D = LuaObject::checkValue<FVector*>(L, 1);
				auto& InScale3DRef = *InScale3D;
				auto InOtherScale3D = LuaObject::checkValue<FVector*>(L, 2);
				auto& InOtherScale3DRef = *InOtherScale3D;
				auto ret = FTransform::AnyHasNegativeScale(InScale3DRef, InOtherScale3DRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::AnyHasNegativeScale error, argc=%d", argc);
			return 0;
		}

		static int GetSafeScaleReciprocal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto InScale = LuaObject::checkValue<FVector*>(L, 1);
				auto& InScaleRef = *InScale;
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = FTransform::GetSafeScaleReciprocal(InScaleRef, Tolerance);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::GetSafeScaleReciprocal error, argc=%d", argc);
			return 0;
		}

		static int AreRotationsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FTransform*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FTransform*>(L, 2);
				auto& BRef = *B;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = FTransform::AreRotationsEqual(ARef, BRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::AreRotationsEqual error, argc=%d", argc);
			return 0;
		}

		static int AreTranslationsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FTransform*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FTransform*>(L, 2);
				auto& BRef = *B;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = FTransform::AreTranslationsEqual(ARef, BRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::AreTranslationsEqual error, argc=%d", argc);
			return 0;
		}

		static int AreScale3DsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FTransform*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FTransform*>(L, 2);
				auto& BRef = *B;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = FTransform::AreScale3DsEqual(ARef, BRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FTransform::AreScale3DsEqual error, argc=%d", argc);
			return 0;
		}

		static int AddTranslations(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FTransform*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FTransform*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFVector();
				*ret = FTransform::AddTranslations(ARef, BRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::AddTranslations error, argc=%d", argc);
			return 0;
		}

		static int SubtractTranslations(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FTransform*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FTransform*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFVector();
				*ret = FTransform::SubtractTranslations(ARef, BRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FTransform::SubtractTranslations error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FTransform");
			LuaObject::addOperator(L, "__add", __add);
			LuaObject::addOperator(L, "__mul", __mul);
			LuaObject::addField(L, "Identity", get_Identity, nullptr, false);
			LuaObject::addMethod(L, "DiagnosticCheckNaN_Translate", DiagnosticCheckNaN_Translate, true);
			LuaObject::addMethod(L, "DiagnosticCheckNaN_Rotate", DiagnosticCheckNaN_Rotate, true);
			LuaObject::addMethod(L, "DiagnosticCheckNaN_Scale3D", DiagnosticCheckNaN_Scale3D, true);
			LuaObject::addMethod(L, "DiagnosticCheckNaN_All", DiagnosticCheckNaN_All, true);
			LuaObject::addMethod(L, "DiagnosticCheck_IsValid", DiagnosticCheck_IsValid, true);
			LuaObject::addMethod(L, "DebugPrint", DebugPrint, true);
			LuaObject::addMethod(L, "ToHumanReadableString", ToHumanReadableString, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "InitFromString", InitFromString, true);
			LuaObject::addMethod(L, "Inverse", Inverse, true);
			LuaObject::addMethod(L, "Blend", Blend, true);
			LuaObject::addMethod(L, "BlendWith", BlendWith, true);
			LuaObject::addMethod(L, "ScaleTranslation", ScaleTranslation, true);
			LuaObject::addMethod(L, "RemoveScaling", RemoveScaling, true);
			LuaObject::addMethod(L, "GetMaximumAxisScale", GetMaximumAxisScale, true);
			LuaObject::addMethod(L, "GetMinimumAxisScale", GetMinimumAxisScale, true);
			LuaObject::addMethod(L, "GetRelativeTransform", GetRelativeTransform, true);
			LuaObject::addMethod(L, "GetRelativeTransformReverse", GetRelativeTransformReverse, true);
			LuaObject::addMethod(L, "SetToRelativeTransform", SetToRelativeTransform, true);
			LuaObject::addMethod(L, "TransformPosition", TransformPosition, true);
			LuaObject::addMethod(L, "TransformPositionNoScale", TransformPositionNoScale, true);
			LuaObject::addMethod(L, "InverseTransformPosition", InverseTransformPosition, true);
			LuaObject::addMethod(L, "InverseTransformPositionNoScale", InverseTransformPositionNoScale, true);
			LuaObject::addMethod(L, "TransformVector", TransformVector, true);
			LuaObject::addMethod(L, "TransformVectorNoScale", TransformVectorNoScale, true);
			LuaObject::addMethod(L, "InverseTransformVector", InverseTransformVector, true);
			LuaObject::addMethod(L, "InverseTransformVectorNoScale", InverseTransformVectorNoScale, true);
			LuaObject::addMethod(L, "GetScaled", GetScaled, true);
			LuaObject::addMethod(L, "GetScaledAxis", GetScaledAxis, true);
			LuaObject::addMethod(L, "GetUnitAxis", GetUnitAxis, true);
			LuaObject::addMethod(L, "Mirror", Mirror, true);
			LuaObject::addMethod(L, "GetLocation", GetLocation, true);
			LuaObject::addMethod(L, "Rotator", Rotator, true);
			LuaObject::addMethod(L, "GetDeterminant", GetDeterminant, true);
			LuaObject::addMethod(L, "SetLocation", SetLocation, true);
			LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
			LuaObject::addMethod(L, "IsValid", IsValid, true);
			LuaObject::addMethod(L, "RotationEquals", RotationEquals, true);
			LuaObject::addMethod(L, "TranslationEquals", TranslationEquals, true);
			LuaObject::addMethod(L, "Scale3DEquals", Scale3DEquals, true);
			LuaObject::addMethod(L, "Equals", Equals, true);
			LuaObject::addMethod(L, "EqualsNoScale", EqualsNoScale, true);
			LuaObject::addMethod(L, "SetIdentity", SetIdentity, true);
			LuaObject::addMethod(L, "MultiplyScale3D", MultiplyScale3D, true);
			LuaObject::addMethod(L, "SetTranslation", SetTranslation, true);
			LuaObject::addMethod(L, "CopyTranslation", CopyTranslation, true);
			LuaObject::addMethod(L, "AddToTranslation", AddToTranslation, true);
			LuaObject::addMethod(L, "CopyRotation", CopyRotation, true);
			LuaObject::addMethod(L, "SetScale3D", SetScale3D, true);
			LuaObject::addMethod(L, "CopyScale3D", CopyScale3D, true);
			LuaObject::addMethod(L, "SetTranslationAndScale3D", SetTranslationAndScale3D, true);
			LuaObject::addMethod(L, "NormalizeRotation", NormalizeRotation, true);
			LuaObject::addMethod(L, "IsRotationNormalized", IsRotationNormalized, true);
			LuaObject::addMethod(L, "GetTranslation", GetTranslation, true);
			LuaObject::addMethod(L, "GetScale3D", GetScale3D, true);
			LuaObject::addMethod(L, "CopyRotationPart", CopyRotationPart, true);
			LuaObject::addMethod(L, "CopyTranslationAndScale3D", CopyTranslationAndScale3D, true);
			LuaObject::addMethod(L, "AnyHasNegativeScale", AnyHasNegativeScale, false);
			LuaObject::addMethod(L, "GetSafeScaleReciprocal", GetSafeScaleReciprocal, false);
			LuaObject::addMethod(L, "AreRotationsEqual", AreRotationsEqual, false);
			LuaObject::addMethod(L, "AreTranslationsEqual", AreTranslationsEqual, false);
			LuaObject::addMethod(L, "AreScale3DsEqual", AreScale3DsEqual, false);
			LuaObject::addMethod(L, "AddTranslations", AddTranslations, false);
			LuaObject::addMethod(L, "SubtractTranslations", SubtractTranslations, false);
			LuaObject::finishType(L, "FTransform", __ctor, __gc);
		}

	};

	struct FLinearColorWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FLinearColor();
				LuaObject::push<FLinearColor>(L, "FLinearColor", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto _a0Val = (EForceInit)_a0;
				auto self = new FLinearColor(_a0Val);
				LuaObject::push<FLinearColor>(L, "FLinearColor", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 5) {
				auto InR = LuaObject::checkValue<float>(L, 2);
				auto InG = LuaObject::checkValue<float>(L, 3);
				auto InB = LuaObject::checkValue<float>(L, 4);
				auto InA = LuaObject::checkValue<float>(L, 5);
				auto self = new FLinearColor(InR, InG, InB, InA);
				LuaObject::push<FLinearColor>(L, "FLinearColor", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FLinearColor);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __add(lua_State* L) {
			CheckSelf(FLinearColor);
			if (LuaObject::matchType(L, 2, "FLinearColor")) {
				auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& ColorBRef = *ColorB;
				auto ret = __newFLinearColor();
				*ret = (*self + ColorBRef);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FLinearColor operator__add error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __sub(lua_State* L) {
			CheckSelf(FLinearColor);
			if (LuaObject::matchType(L, 2, "FLinearColor")) {
				auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& ColorBRef = *ColorB;
				auto ret = __newFLinearColor();
				*ret = (*self - ColorBRef);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FLinearColor operator__sub error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __mul(lua_State* L) {
			CheckSelf(FLinearColor);
			if (LuaObject::matchType(L, 2, "FLinearColor")) {
				auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& ColorBRef = *ColorB;
				auto ret = __newFLinearColor();
				*ret = (*self * ColorBRef);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (lua_isnumber(L, 2)) {
				auto Scalar = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFLinearColor();
				*ret = (*self * Scalar);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FLinearColor operator__mul error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __div(lua_State* L) {
			CheckSelf(FLinearColor);
			if (LuaObject::matchType(L, 2, "FLinearColor")) {
				auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& ColorBRef = *ColorB;
				auto ret = __newFLinearColor();
				*ret = (*self / ColorBRef);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (lua_isnumber(L, 2)) {
				auto Scalar = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFLinearColor();
				*ret = (*self / Scalar);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FLinearColor operator__div error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FLinearColor);
			if (LuaObject::matchType(L, 2, "FLinearColor")) {
				auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& ColorBRef = *ColorB;
				auto ret = (*self == ColorBRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int get_R(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& R = self->R;
			LuaObject::push(L, R);
			return 1;
		}

		static int set_R(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& R = self->R;
			auto RIn = LuaObject::checkValue<float>(L, 2);
			R = RIn;
			LuaObject::push(L, RIn);
			return 1;
		}

		static int get_G(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& G = self->G;
			LuaObject::push(L, G);
			return 1;
		}

		static int set_G(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& G = self->G;
			auto GIn = LuaObject::checkValue<float>(L, 2);
			G = GIn;
			LuaObject::push(L, GIn);
			return 1;
		}

		static int get_B(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& B = self->B;
			LuaObject::push(L, B);
			return 1;
		}

		static int set_B(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& B = self->B;
			auto BIn = LuaObject::checkValue<float>(L, 2);
			B = BIn;
			LuaObject::push(L, BIn);
			return 1;
		}

		static int get_A(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& A = self->A;
			LuaObject::push(L, A);
			return 1;
		}

		static int set_A(lua_State* L) {
			CheckSelf(FLinearColor);
			auto& A = self->A;
			auto AIn = LuaObject::checkValue<float>(L, 2);
			A = AIn;
			LuaObject::push(L, AIn);
			return 1;
		}

		static int get_White(lua_State* L) {
			auto& White = FLinearColor::White;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &White);
			return 1;
		}

		static int get_Gray(lua_State* L) {
			auto& Gray = FLinearColor::Gray;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &Gray);
			return 1;
		}

		static int get_Black(lua_State* L) {
			auto& Black = FLinearColor::Black;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &Black);
			return 1;
		}

		static int get_Transparent(lua_State* L) {
			auto& Transparent = FLinearColor::Transparent;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &Transparent);
			return 1;
		}

		static int get_Red(lua_State* L) {
			auto& Red = FLinearColor::Red;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &Red);
			return 1;
		}

		static int get_Green(lua_State* L) {
			auto& Green = FLinearColor::Green;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &Green);
			return 1;
		}

		static int get_Blue(lua_State* L) {
			auto& Blue = FLinearColor::Blue;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &Blue);
			return 1;
		}

		static int get_Yellow(lua_State* L) {
			auto& Yellow = FLinearColor::Yellow;
			LuaObject::push<FLinearColor>(L, "FLinearColor", &Yellow);
			return 1;
		}

		static int ToRGBE(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = __newFColor();
				*ret = self->ToRGBE();
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::ToRGBE error, argc=%d", argc);
			return 0;
		}

		static int Component(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FLinearColor);
				auto Index = LuaObject::checkValue<int>(L, 2);
				auto ret = self->Component(Index);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::Component error, argc=%d", argc);
			return 0;
		}

		static int GetClamped(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FLinearColor);
				auto InMin = LuaObject::checkValue<float>(L, 2);
				auto InMax = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFLinearColor();
				*ret = self->GetClamped(InMin, InMax);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::GetClamped error, argc=%d", argc);
			return 0;
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FLinearColor);
				auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& ColorBRef = *ColorB;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(ColorBRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::Equals error, argc=%d", argc);
			return 0;
		}

		static int CopyWithNewOpacity(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FLinearColor);
				auto NewOpacicty = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFLinearColor();
				*ret = self->CopyWithNewOpacity(NewOpacicty);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::CopyWithNewOpacity error, argc=%d", argc);
			return 0;
		}

		static int LinearRGBToHSV(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = __newFLinearColor();
				*ret = self->LinearRGBToHSV();
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::LinearRGBToHSV error, argc=%d", argc);
			return 0;
		}

		static int HSVToLinearRGB(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = __newFLinearColor();
				*ret = self->HSVToLinearRGB();
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::HSVToLinearRGB error, argc=%d", argc);
			return 0;
		}

		static int Quantize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = __newFColor();
				*ret = self->Quantize();
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::Quantize error, argc=%d", argc);
			return 0;
		}

		static int QuantizeRound(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = __newFColor();
				*ret = self->QuantizeRound();
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::QuantizeRound error, argc=%d", argc);
			return 0;
		}

		static int ToFColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FLinearColor);
				auto bSRGB = LuaObject::checkValue<bool>(L, 2);
				auto ret = __newFColor();
				*ret = self->ToFColor(bSRGB);
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::ToFColor error, argc=%d", argc);
			return 0;
		}

		static int Desaturate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FLinearColor);
				auto Desaturation = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFLinearColor();
				*ret = self->Desaturate(Desaturation);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::Desaturate error, argc=%d", argc);
			return 0;
		}

		static int ComputeLuminance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = self->ComputeLuminance();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::ComputeLuminance error, argc=%d", argc);
			return 0;
		}

		static int GetMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = self->GetMax();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::GetMax error, argc=%d", argc);
			return 0;
		}

		static int IsAlmostBlack(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = self->IsAlmostBlack();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::IsAlmostBlack error, argc=%d", argc);
			return 0;
		}

		static int GetMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = self->GetMin();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::GetMin error, argc=%d", argc);
			return 0;
		}

		static int GetLuminance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = self->GetLuminance();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::GetLuminance error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FLinearColor);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::ToString error, argc=%d", argc);
			return 0;
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FLinearColor);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::InitFromString error, argc=%d", argc);
			return 0;
		}

		static int FromSRGBColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Color = LuaObject::checkValue<FColor*>(L, 1);
				auto& ColorRef = *Color;
				auto ret = __newFLinearColor();
				*ret = FLinearColor::FromSRGBColor(ColorRef);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::FromSRGBColor error, argc=%d", argc);
			return 0;
		}

		static int FromPow22Color(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Color = LuaObject::checkValue<FColor*>(L, 1);
				auto& ColorRef = *Color;
				auto ret = __newFLinearColor();
				*ret = FLinearColor::FromPow22Color(ColorRef);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::FromPow22Color error, argc=%d", argc);
			return 0;
		}

		static int FGetHSV(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto H = LuaObject::checkValue<int>(L, 1);
				auto HVal = (unsigned char)H;
				auto S = LuaObject::checkValue<int>(L, 2);
				auto SVal = (unsigned char)S;
				auto V = LuaObject::checkValue<int>(L, 3);
				auto VVal = (unsigned char)V;
				auto ret = __newFLinearColor();
#if (ENGINE_MINOR_VERSION>=22) && (ENGINE_MAJOR_VERSION>=4)
				*ret = FLinearColor::MakeFromHSV8(HVal, SVal, VVal);
#else
				*ret = FLinearColor::FGetHSV(HVal, SVal, VVal);
#endif
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::FGetHSV error, argc=%d", argc);
			return 0;
		}

		static int MakeRandomColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFLinearColor();
				*ret = FLinearColor::MakeRandomColor();
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::MakeRandomColor error, argc=%d", argc);
			return 0;
		}

		static int MakeFromColorTemperature(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Temp = LuaObject::checkValue<float>(L, 1);
				auto ret = __newFLinearColor();
				*ret = FLinearColor::MakeFromColorTemperature(Temp);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::MakeFromColorTemperature error, argc=%d", argc);
			return 0;
		}

		static int Dist(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FLinearColor::Dist(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FLinearColor::Dist error, argc=%d", argc);
			return 0;
		}

		static int LerpUsingHSV(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto From = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto& FromRef = *From;
				auto To = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto& ToRef = *To;
				auto Progress = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFLinearColor();
				*ret = FLinearColor::LerpUsingHSV(FromRef, ToRef, Progress);
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FLinearColor::LerpUsingHSV error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FLinearColor");
			LuaObject::addOperator(L, "__add", __add);
			LuaObject::addOperator(L, "__sub", __sub);
			LuaObject::addOperator(L, "__mul", __mul);
			LuaObject::addOperator(L, "__div", __div);
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addField(L, "R", get_R, set_R, true);
			LuaObject::addField(L, "G", get_G, set_G, true);
			LuaObject::addField(L, "B", get_B, set_B, true);
			LuaObject::addField(L, "A", get_A, set_A, true);
			LuaObject::addField(L, "White", get_White, nullptr, false);
			LuaObject::addField(L, "Gray", get_Gray, nullptr, false);
			LuaObject::addField(L, "Black", get_Black, nullptr, false);
			LuaObject::addField(L, "Transparent", get_Transparent, nullptr, false);
			LuaObject::addField(L, "Red", get_Red, nullptr, false);
			LuaObject::addField(L, "Green", get_Green, nullptr, false);
			LuaObject::addField(L, "Blue", get_Blue, nullptr, false);
			LuaObject::addField(L, "Yellow", get_Yellow, nullptr, false);
			LuaObject::addMethod(L, "ToRGBE", ToRGBE, true);
			LuaObject::addMethod(L, "Component", Component, true);
			LuaObject::addMethod(L, "GetClamped", GetClamped, true);
			LuaObject::addMethod(L, "Equals", Equals, true);
			LuaObject::addMethod(L, "CopyWithNewOpacity", CopyWithNewOpacity, true);
			LuaObject::addMethod(L, "LinearRGBToHSV", LinearRGBToHSV, true);
			LuaObject::addMethod(L, "HSVToLinearRGB", HSVToLinearRGB, true);
			LuaObject::addMethod(L, "Quantize", Quantize, true);
			LuaObject::addMethod(L, "QuantizeRound", QuantizeRound, true);
			LuaObject::addMethod(L, "ToFColor", ToFColor, true);
			LuaObject::addMethod(L, "Desaturate", Desaturate, true);
			LuaObject::addMethod(L, "ComputeLuminance", ComputeLuminance, true);
			LuaObject::addMethod(L, "GetMax", GetMax, true);
			LuaObject::addMethod(L, "IsAlmostBlack", IsAlmostBlack, true);
			LuaObject::addMethod(L, "GetMin", GetMin, true);
			LuaObject::addMethod(L, "GetLuminance", GetLuminance, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "InitFromString", InitFromString, true);
			LuaObject::addMethod(L, "FromSRGBColor", FromSRGBColor, false);
			LuaObject::addMethod(L, "FromPow22Color", FromPow22Color, false);
			LuaObject::addMethod(L, "FGetHSV", FGetHSV, false);
			LuaObject::addMethod(L, "MakeRandomColor", MakeRandomColor, false);
			LuaObject::addMethod(L, "MakeFromColorTemperature", MakeFromColorTemperature, false);
			LuaObject::addMethod(L, "Dist", Dist, false);
			LuaObject::addMethod(L, "LerpUsingHSV", LerpUsingHSV, false);
			LuaObject::finishType(L, "FLinearColor", __ctor, __gc);
		}

	};

	struct FColorWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FColor();
				LuaObject::push<FColor>(L, "FColor", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto _a0Val = (EForceInit)_a0;
				auto self = new FColor(_a0Val);
				LuaObject::push<FColor>(L, "FColor", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 5) {
				auto InR = LuaObject::checkValue<int>(L, 2);
				auto InRVal = (unsigned char)InR;
				auto InG = LuaObject::checkValue<int>(L, 3);
				auto InGVal = (unsigned char)InG;
				auto InB = LuaObject::checkValue<int>(L, 4);
				auto InBVal = (unsigned char)InB;
				auto InA = LuaObject::checkValue<int>(L, 5);
				auto InAVal = (unsigned char)InA;
				auto self = new FColor(InRVal, InGVal, InBVal, InAVal);
				LuaObject::push<FColor>(L, "FColor", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FColor);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FColor);
			if (LuaObject::matchType(L, 2, "FColor")) {
				auto C = LuaObject::checkValue<FColor*>(L, 2);
				auto& CRef = *C;
				auto ret = (*self == CRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int get_White(lua_State* L) {
			auto& White = FColor::White;
			LuaObject::push<FColor>(L, "FColor", &White);
			return 1;
		}

		static int get_Black(lua_State* L) {
			auto& Black = FColor::Black;
			LuaObject::push<FColor>(L, "FColor", &Black);
			return 1;
		}

		static int get_Transparent(lua_State* L) {
			auto& Transparent = FColor::Transparent;
			LuaObject::push<FColor>(L, "FColor", &Transparent);
			return 1;
		}

		static int get_Red(lua_State* L) {
			auto& Red = FColor::Red;
			LuaObject::push<FColor>(L, "FColor", &Red);
			return 1;
		}

		static int get_Green(lua_State* L) {
			auto& Green = FColor::Green;
			LuaObject::push<FColor>(L, "FColor", &Green);
			return 1;
		}

		static int get_Blue(lua_State* L) {
			auto& Blue = FColor::Blue;
			LuaObject::push<FColor>(L, "FColor", &Blue);
			return 1;
		}

		static int get_Yellow(lua_State* L) {
			auto& Yellow = FColor::Yellow;
			LuaObject::push<FColor>(L, "FColor", &Yellow);
			return 1;
		}

		static int get_Cyan(lua_State* L) {
			auto& Cyan = FColor::Cyan;
			LuaObject::push<FColor>(L, "FColor", &Cyan);
			return 1;
		}

		static int get_Magenta(lua_State* L) {
			auto& Magenta = FColor::Magenta;
			LuaObject::push<FColor>(L, "FColor", &Magenta);
			return 1;
		}

		static int get_Orange(lua_State* L) {
			auto& Orange = FColor::Orange;
			LuaObject::push<FColor>(L, "FColor", &Orange);
			return 1;
		}

		static int get_Purple(lua_State* L) {
			auto& Purple = FColor::Purple;
			LuaObject::push<FColor>(L, "FColor", &Purple);
			return 1;
		}

		static int get_Turquoise(lua_State* L) {
			auto& Turquoise = FColor::Turquoise;
			LuaObject::push<FColor>(L, "FColor", &Turquoise);
			return 1;
		}

		static int get_Silver(lua_State* L) {
			auto& Silver = FColor::Silver;
			LuaObject::push<FColor>(L, "FColor", &Silver);
			return 1;
		}

		static int get_Emerald(lua_State* L) {
			auto& Emerald = FColor::Emerald;
			LuaObject::push<FColor>(L, "FColor", &Emerald);
			return 1;
		}

		static int DWColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = self->DWColor();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::DWColor error, argc=%d", argc);
			return 0;
		}

		static int FromRGBE(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = __newFLinearColor();
				*ret = self->FromRGBE();
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor::FromRGBE error, argc=%d", argc);
			return 0;
		}

		static int WithAlpha(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FColor);
				auto Alpha = LuaObject::checkValue<int>(L, 2);
				auto AlphaVal = (unsigned char)Alpha;
				auto ret = __newFColor();
				*ret = self->WithAlpha(AlphaVal);
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor::WithAlpha error, argc=%d", argc);
			return 0;
		}

		static int ReinterpretAsLinear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = __newFLinearColor();
				*ret = self->ReinterpretAsLinear();
				LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor::ReinterpretAsLinear error, argc=%d", argc);
			return 0;
		}

		static int ToHex(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = self->ToHex();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::ToHex error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::ToString error, argc=%d", argc);
			return 0;
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FColor);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::InitFromString error, argc=%d", argc);
			return 0;
		}

		static int ToPackedARGB(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = self->ToPackedARGB();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::ToPackedARGB error, argc=%d", argc);
			return 0;
		}

		static int ToPackedABGR(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = self->ToPackedABGR();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::ToPackedABGR error, argc=%d", argc);
			return 0;
		}

		static int ToPackedRGBA(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = self->ToPackedRGBA();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::ToPackedRGBA error, argc=%d", argc);
			return 0;
		}

		static int ToPackedBGRA(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FColor);
				auto ret = self->ToPackedBGRA();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FColor::ToPackedBGRA error, argc=%d", argc);
			return 0;
		}

		static int FromHex(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto HexString = LuaObject::checkValue<FString>(L, 1);
				auto ret = __newFColor();
				*ret = FColor::FromHex(HexString);
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor::FromHex error, argc=%d", argc);
			return 0;
		}

		static int MakeRandomColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFColor();
				*ret = FColor::MakeRandomColor();
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor::MakeRandomColor error, argc=%d", argc);
			return 0;
		}

		static int MakeRedToGreenColorFromScalar(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Scalar = LuaObject::checkValue<float>(L, 1);
				auto ret = __newFColor();
				*ret = FColor::MakeRedToGreenColorFromScalar(Scalar);
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor::MakeRedToGreenColorFromScalar error, argc=%d", argc);
			return 0;
		}

		static int MakeFromColorTemperature(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Temp = LuaObject::checkValue<float>(L, 1);
				auto ret = __newFColor();
				*ret = FColor::MakeFromColorTemperature(Temp);
				LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FColor::MakeFromColorTemperature error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FColor");
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addField(L, "White", get_White, nullptr, false);
			LuaObject::addField(L, "Black", get_Black, nullptr, false);
			LuaObject::addField(L, "Transparent", get_Transparent, nullptr, false);
			LuaObject::addField(L, "Red", get_Red, nullptr, false);
			LuaObject::addField(L, "Green", get_Green, nullptr, false);
			LuaObject::addField(L, "Blue", get_Blue, nullptr, false);
			LuaObject::addField(L, "Yellow", get_Yellow, nullptr, false);
			LuaObject::addField(L, "Cyan", get_Cyan, nullptr, false);
			LuaObject::addField(L, "Magenta", get_Magenta, nullptr, false);
			LuaObject::addField(L, "Orange", get_Orange, nullptr, false);
			LuaObject::addField(L, "Purple", get_Purple, nullptr, false);
			LuaObject::addField(L, "Turquoise", get_Turquoise, nullptr, false);
			LuaObject::addField(L, "Silver", get_Silver, nullptr, false);
			LuaObject::addField(L, "Emerald", get_Emerald, nullptr, false);
			LuaObject::addMethod(L, "DWColor", DWColor, true);
			LuaObject::addMethod(L, "FromRGBE", FromRGBE, true);
			LuaObject::addMethod(L, "WithAlpha", WithAlpha, true);
			LuaObject::addMethod(L, "ReinterpretAsLinear", ReinterpretAsLinear, true);
			LuaObject::addMethod(L, "ToHex", ToHex, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "InitFromString", InitFromString, true);
			LuaObject::addMethod(L, "ToPackedARGB", ToPackedARGB, true);
			LuaObject::addMethod(L, "ToPackedABGR", ToPackedABGR, true);
			LuaObject::addMethod(L, "ToPackedRGBA", ToPackedRGBA, true);
			LuaObject::addMethod(L, "ToPackedBGRA", ToPackedBGRA, true);
			LuaObject::addMethod(L, "FromHex", FromHex, false);
			LuaObject::addMethod(L, "MakeRandomColor", MakeRandomColor, false);
			LuaObject::addMethod(L, "MakeRedToGreenColorFromScalar", MakeRedToGreenColorFromScalar, false);
			LuaObject::addMethod(L, "MakeFromColorTemperature", MakeFromColorTemperature, false);
			LuaObject::finishType(L, "FColor", __ctor, __gc);
		}

	};

	struct FVectorWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FVector();
				LuaObject::push<FVector>(L, "FVector", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InF = LuaObject::checkValue<float>(L, 2);
				auto self = new FVector(InF);
				LuaObject::push<FVector>(L, "FVector", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 3) {
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto VVal = *V;
				auto InZ = LuaObject::checkValue<float>(L, 3);
				auto self = new FVector(VVal, InZ);
				LuaObject::push<FVector>(L, "FVector", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 4) {
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				auto InZ = LuaObject::checkValue<float>(L, 4);
				auto self = new FVector(InX, InY, InZ);
				LuaObject::push<FVector>(L, "FVector", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FVector);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __add(lua_State* L) {
			CheckSelf(FVector);
			if (LuaObject::matchType(L, 2, "FVector")) {
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = (*self + VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (lua_isnumber(L, 2)) {
				auto Bias = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = (*self + Bias);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector operator__add error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __sub(lua_State* L) {
			CheckSelf(FVector);
			if (LuaObject::matchType(L, 2, "FVector")) {
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = (*self - VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (lua_isnumber(L, 2)) {
				auto Bias = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = (*self - Bias);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector operator__sub error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __mul(lua_State* L) {
			CheckSelf(FVector);
			if (lua_isnumber(L, 2)) {
				auto Scale = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = (*self * Scale);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (LuaObject::matchType(L, 2, "FVector")) {
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = (*self * VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector operator__mul error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __div(lua_State* L) {
			CheckSelf(FVector);
			if (lua_isnumber(L, 2)) {
				auto Scale = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = (*self / Scale);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (LuaObject::matchType(L, 2, "FVector")) {
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector();
				*ret = (*self / VRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector operator__div error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FVector);
			if (LuaObject::matchType(L, 2, "FVector")) {
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto ret = (*self == VRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int get_X(lua_State* L) {
			CheckSelf(FVector);
			auto& X = self->X;
			LuaObject::push(L, X);
			return 1;
		}

		static int set_X(lua_State* L) {
			CheckSelf(FVector);
			auto& X = self->X;
			auto XIn = LuaObject::checkValue<float>(L, 2);
			X = XIn;
			LuaObject::push(L, XIn);
			return 1;
		}

		static int get_Y(lua_State* L) {
			CheckSelf(FVector);
			auto& Y = self->Y;
			LuaObject::push(L, Y);
			return 1;
		}

		static int set_Y(lua_State* L) {
			CheckSelf(FVector);
			auto& Y = self->Y;
			auto YIn = LuaObject::checkValue<float>(L, 2);
			Y = YIn;
			LuaObject::push(L, YIn);
			return 1;
		}

		static int get_Z(lua_State* L) {
			CheckSelf(FVector);
			auto& Z = self->Z;
			LuaObject::push(L, Z);
			return 1;
		}

		static int set_Z(lua_State* L) {
			CheckSelf(FVector);
			auto& Z = self->Z;
			auto ZIn = LuaObject::checkValue<float>(L, 2);
			Z = ZIn;
			LuaObject::push(L, ZIn);
			return 1;
		}

		static int get_ZeroVector(lua_State* L) {
			auto& ZeroVector = FVector::ZeroVector;
			LuaObject::push<FVector>(L, "FVector", &ZeroVector);
			return 1;
		}

		static int get_OneVector(lua_State* L) {
			auto& OneVector = FVector::OneVector;
			LuaObject::push<FVector>(L, "FVector", &OneVector);
			return 1;
		}

		static int get_UpVector(lua_State* L) {
			auto& UpVector = FVector::UpVector;
			LuaObject::push<FVector>(L, "FVector", &UpVector);
			return 1;
		}

		static int get_ForwardVector(lua_State* L) {
			auto& ForwardVector = FVector::ForwardVector;
			LuaObject::push<FVector>(L, "FVector", &ForwardVector);
			return 1;
		}

		static int get_RightVector(lua_State* L) {
			auto& RightVector = FVector::RightVector;
			LuaObject::push<FVector>(L, "FVector", &RightVector);
			return 1;
		}

		static int DiagnosticCheckNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				self->DiagnosticCheckNaN();
				return 0;
			}
			if (argc == 2) {
				CheckSelf(FVector);
				auto Message = LuaObject::checkValue<const char*>(L, 2);
				auto MessageVal = FString(UTF8_TO_TCHAR(Message));
				self->DiagnosticCheckNaN(*MessageVal);
				return 0;
			}
			luaL_error(L, "call FVector::DiagnosticCheckNaN error, argc=%d", argc);
			return 0;
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(VRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Equals error, argc=%d", argc);
			return 0;
		}

		static int AllComponentsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->AllComponentsEqual(Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::AllComponentsEqual error, argc=%d", argc);
			return 0;
		}

		static int Component(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Index = LuaObject::checkValue<int>(L, 2);
				auto ret = self->Component(Index);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Component error, argc=%d", argc);
			return 0;
		}

		static int GetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto AxisVal = (EAxis::Type)Axis;
				auto ret = self->GetComponentForAxis(AxisVal);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::GetComponentForAxis error, argc=%d", argc);
			return 0;
		}

		static int SetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto AxisVal = (EAxis::Type)Axis;
				auto Component = LuaObject::checkValue<float>(L, 3);
				self->SetComponentForAxis(AxisVal, Component);
				return 0;
			}
			luaL_error(L, "call FVector::SetComponentForAxis error, argc=%d", argc);
			return 0;
		}

		static int Set(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				CheckSelf(FVector);
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				auto InZ = LuaObject::checkValue<float>(L, 4);
				self->Set(InX, InY, InZ);
				return 0;
			}
			luaL_error(L, "call FVector::Set error, argc=%d", argc);
			return 0;
		}

		static int GetMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->GetMax();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::GetMax error, argc=%d", argc);
			return 0;
		}

		static int GetAbsMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->GetAbsMax();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::GetAbsMax error, argc=%d", argc);
			return 0;
		}

		static int GetMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->GetMin();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::GetMin error, argc=%d", argc);
			return 0;
		}

		static int GetAbsMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->GetAbsMin();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::GetAbsMin error, argc=%d", argc);
			return 0;
		}

		static int ComponentMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Other = LuaObject::checkValue<FVector*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = __newFVector();
				*ret = self->ComponentMin(OtherRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::ComponentMin error, argc=%d", argc);
			return 0;
		}

		static int ComponentMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Other = LuaObject::checkValue<FVector*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = __newFVector();
				*ret = self->ComponentMax(OtherRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::ComponentMax error, argc=%d", argc);
			return 0;
		}

		static int GetAbs(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFVector();
				*ret = self->GetAbs();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetAbs error, argc=%d", argc);
			return 0;
		}

		static int Size(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->Size();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Size error, argc=%d", argc);
			return 0;
		}

		static int SizeSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->SizeSquared();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::SizeSquared error, argc=%d", argc);
			return 0;
		}

		static int Size2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->Size2D();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Size2D error, argc=%d", argc);
			return 0;
		}

		static int SizeSquared2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->SizeSquared2D();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::SizeSquared2D error, argc=%d", argc);
			return 0;
		}

		static int IsNearlyZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsNearlyZero(Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::IsNearlyZero error, argc=%d", argc);
			return 0;
		}

		static int IsZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->IsZero();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::IsZero error, argc=%d", argc);
			return 0;
		}

		static int Normalize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->Normalize(Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Normalize error, argc=%d", argc);
			return 0;
		}

		static int IsNormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->IsNormalized();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::IsNormalized error, argc=%d", argc);
			return 0;
		}

		static int ToDirectionAndLength(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto OutDir = LuaObject::checkValue<FVector*>(L, 2);
				auto& OutDirRef = *OutDir;
				auto OutLength = LuaObject::checkValue<float>(L, 3);
				self->ToDirectionAndLength(OutDirRef, OutLength);
				LuaObject::push<FVector>(L, "FVector", OutDir);
				LuaObject::push(L, OutLength);
				return 2;
			}
			luaL_error(L, "call FVector::ToDirectionAndLength error, argc=%d", argc);
			return 0;
		}

		static int GetSignVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFVector();
				*ret = self->GetSignVector();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetSignVector error, argc=%d", argc);
			return 0;
		}

		static int Projection(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFVector();
				*ret = self->Projection();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::Projection error, argc=%d", argc);
			return 0;
		}

		static int GetUnsafeNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFVector();
				*ret = self->GetUnsafeNormal();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetUnsafeNormal error, argc=%d", argc);
			return 0;
		}

		static int GridSnap(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto GridSz = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GridSnap(GridSz);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GridSnap error, argc=%d", argc);
			return 0;
		}

		static int BoundToCube(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Radius = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->BoundToCube(Radius);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::BoundToCube error, argc=%d", argc);
			return 0;
		}

		static int GetClampedToSize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto Min = LuaObject::checkValue<float>(L, 2);
				auto Max = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector();
				*ret = self->GetClampedToSize(Min, Max);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetClampedToSize error, argc=%d", argc);
			return 0;
		}

		static int GetClampedToSize2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto Min = LuaObject::checkValue<float>(L, 2);
				auto Max = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector();
				*ret = self->GetClampedToSize2D(Min, Max);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetClampedToSize2D error, argc=%d", argc);
			return 0;
		}

		static int GetClampedToMaxSize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto MaxSize = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetClampedToMaxSize(MaxSize);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetClampedToMaxSize error, argc=%d", argc);
			return 0;
		}

		static int GetClampedToMaxSize2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto MaxSize = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetClampedToMaxSize2D(MaxSize);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetClampedToMaxSize2D error, argc=%d", argc);
			return 0;
		}

		static int AddBounded(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto& VRef = *V;
				auto Radius = LuaObject::checkValue<float>(L, 3);
				self->AddBounded(VRef, Radius);
				return 0;
			}
			luaL_error(L, "call FVector::AddBounded error, argc=%d", argc);
			return 0;
		}

		static int Reciprocal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFVector();
				*ret = self->Reciprocal();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::Reciprocal error, argc=%d", argc);
			return 0;
		}

		static int IsUniform(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsUniform(Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::IsUniform error, argc=%d", argc);
			return 0;
		}

		static int MirrorByVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto MirrorNormal = LuaObject::checkValue<FVector*>(L, 2);
				auto& MirrorNormalRef = *MirrorNormal;
				auto ret = __newFVector();
				*ret = self->MirrorByVector(MirrorNormalRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::MirrorByVector error, argc=%d", argc);
			return 0;
		}

		static int RotateAngleAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto AngleDeg = LuaObject::checkValue<float>(L, 2);
				auto Axis = LuaObject::checkValue<FVector*>(L, 3);
				auto& AxisRef = *Axis;
				auto ret = __newFVector();
				*ret = self->RotateAngleAxis(AngleDeg, AxisRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::RotateAngleAxis error, argc=%d", argc);
			return 0;
		}

		static int GetSafeNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetSafeNormal(Tolerance);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetSafeNormal error, argc=%d", argc);
			return 0;
		}

		static int GetSafeNormal2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetSafeNormal2D(Tolerance);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::GetSafeNormal2D error, argc=%d", argc);
			return 0;
		}

		static int CosineAngle2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto B = LuaObject::checkValue<FVector*>(L, 2);
				auto BVal = *B;
				auto ret = self->CosineAngle2D(BVal);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::CosineAngle2D error, argc=%d", argc);
			return 0;
		}

		static int ProjectOnTo(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto A = LuaObject::checkValue<FVector*>(L, 2);
				auto& ARef = *A;
				auto ret = __newFVector();
				*ret = self->ProjectOnTo(ARef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::ProjectOnTo error, argc=%d", argc);
			return 0;
		}

		static int ProjectOnToNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto Normal = LuaObject::checkValue<FVector*>(L, 2);
				auto& NormalRef = *Normal;
				auto ret = __newFVector();
				*ret = self->ProjectOnToNormal(NormalRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::ProjectOnToNormal error, argc=%d", argc);
			return 0;
		}

		static int ToOrientationRotator(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFRotator();
				*ret = self->ToOrientationRotator();
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::ToOrientationRotator error, argc=%d", argc);
			return 0;
		}

		static int Rotation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFRotator();
				*ret = self->Rotation();
				LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::Rotation error, argc=%d", argc);
			return 0;
		}

		static int FindBestAxisVectors(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector);
				auto Axis1 = LuaObject::checkValue<FVector*>(L, 2);
				auto& Axis1Ref = *Axis1;
				auto Axis2 = LuaObject::checkValue<FVector*>(L, 3);
				auto& Axis2Ref = *Axis2;
				self->FindBestAxisVectors(Axis1Ref, Axis2Ref);
				LuaObject::push<FVector>(L, "FVector", Axis1);
				LuaObject::push<FVector>(L, "FVector", Axis2);
				return 2;
			}
			luaL_error(L, "call FVector::FindBestAxisVectors error, argc=%d", argc);
			return 0;
		}

		static int UnwindEuler(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				self->UnwindEuler();
				return 0;
			}
			luaL_error(L, "call FVector::UnwindEuler error, argc=%d", argc);
			return 0;
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::ContainsNaN error, argc=%d", argc);
			return 0;
		}

		static int IsUnit(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto LengthSquaredTolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsUnit(LengthSquaredTolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::IsUnit error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::ToString error, argc=%d", argc);
			return 0;
		}

		static int ToCompactString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->ToCompactString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::ToCompactString error, argc=%d", argc);
			return 0;
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::InitFromString error, argc=%d", argc);
			return 0;
		}

		static int UnitCartesianToSpherical(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = __newFVector2D();
				*ret = self->UnitCartesianToSpherical();
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::UnitCartesianToSpherical error, argc=%d", argc);
			return 0;
		}

		static int HeadingAngle(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector);
				auto ret = self->HeadingAngle();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::HeadingAngle error, argc=%d", argc);
			return 0;
		}

		static int CrossProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FVector*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FVector*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFVector();
				*ret = FVector::CrossProduct(ARef, BRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::CrossProduct error, argc=%d", argc);
			return 0;
		}

		static int DotProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FVector*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FVector*>(L, 2);
				auto& BRef = *B;
				auto ret = FVector::DotProduct(ARef, BRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::DotProduct error, argc=%d", argc);
			return 0;
		}

		static int CreateOrthonormalBasis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto XAxis = LuaObject::checkValue<FVector*>(L, 1);
				auto& XAxisRef = *XAxis;
				auto YAxis = LuaObject::checkValue<FVector*>(L, 2);
				auto& YAxisRef = *YAxis;
				auto ZAxis = LuaObject::checkValue<FVector*>(L, 3);
				auto& ZAxisRef = *ZAxis;
				FVector::CreateOrthonormalBasis(XAxisRef, YAxisRef, ZAxisRef);
				LuaObject::push<FVector>(L, "FVector", XAxis);
				LuaObject::push<FVector>(L, "FVector", YAxis);
				LuaObject::push<FVector>(L, "FVector", ZAxis);
				return 3;
			}
			luaL_error(L, "call FVector::CreateOrthonormalBasis error, argc=%d", argc);
			return 0;
		}

		static int PointsAreSame(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto P = LuaObject::checkValue<FVector*>(L, 1);
				auto& PRef = *P;
				auto Q = LuaObject::checkValue<FVector*>(L, 2);
				auto& QRef = *Q;
				auto ret = FVector::PointsAreSame(PRef, QRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::PointsAreSame error, argc=%d", argc);
			return 0;
		}

		static int PointsAreNear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto Point1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& Point1Ref = *Point1;
				auto Point2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& Point2Ref = *Point2;
				auto Dist = LuaObject::checkValue<float>(L, 3);
				auto ret = FVector::PointsAreNear(Point1Ref, Point2Ref, Dist);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::PointsAreNear error, argc=%d", argc);
			return 0;
		}

		static int PointPlaneDist(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto Point = LuaObject::checkValue<FVector*>(L, 1);
				auto& PointRef = *Point;
				auto PlaneBase = LuaObject::checkValue<FVector*>(L, 2);
				auto& PlaneBaseRef = *PlaneBase;
				auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 3);
				auto& PlaneNormalRef = *PlaneNormal;
				auto ret = FVector::PointPlaneDist(PointRef, PlaneBaseRef, PlaneNormalRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::PointPlaneDist error, argc=%d", argc);
			return 0;
		}

		static int PointPlaneProject(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto Point = LuaObject::checkValue<FVector*>(L, 1);
				auto& PointRef = *Point;
				auto PlaneBase = LuaObject::checkValue<FVector*>(L, 2);
				auto& PlaneBaseRef = *PlaneBase;
				auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 3);
				auto& PlaneNormalRef = *PlaneNormal;
				auto ret = __newFVector();
				*ret = FVector::PointPlaneProject(PointRef, PlaneBaseRef, PlaneNormalRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 4) {
				auto Point = LuaObject::checkValue<FVector*>(L, 1);
				auto& PointRef = *Point;
				auto A = LuaObject::checkValue<FVector*>(L, 2);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FVector*>(L, 3);
				auto& BRef = *B;
				auto C = LuaObject::checkValue<FVector*>(L, 4);
				auto& CRef = *C;
				auto ret = __newFVector();
				*ret = FVector::PointPlaneProject(PointRef, ARef, BRef, CRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::PointPlaneProject error, argc=%d", argc);
			return 0;
		}

		static int VectorPlaneProject(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V = LuaObject::checkValue<FVector*>(L, 1);
				auto& VRef = *V;
				auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 2);
				auto& PlaneNormalRef = *PlaneNormal;
				auto ret = __newFVector();
				*ret = FVector::VectorPlaneProject(VRef, PlaneNormalRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::VectorPlaneProject error, argc=%d", argc);
			return 0;
		}

		static int Dist(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector::Dist(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Dist error, argc=%d", argc);
			return 0;
		}

		static int Distance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector::Distance(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Distance error, argc=%d", argc);
			return 0;
		}

		static int DistXY(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector::DistXY(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::DistXY error, argc=%d", argc);
			return 0;
		}

		static int Dist2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector::Dist2D(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Dist2D error, argc=%d", argc);
			return 0;
		}

		static int DistSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector::DistSquared(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::DistSquared error, argc=%d", argc);
			return 0;
		}

		static int DistSquaredXY(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector::DistSquaredXY(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::DistSquaredXY error, argc=%d", argc);
			return 0;
		}

		static int DistSquared2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector::DistSquared2D(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::DistSquared2D error, argc=%d", argc);
			return 0;
		}

		static int BoxPushOut(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Normal = LuaObject::checkValue<FVector*>(L, 1);
				auto& NormalRef = *Normal;
				auto Size = LuaObject::checkValue<FVector*>(L, 2);
				auto& SizeRef = *Size;
				auto ret = FVector::BoxPushOut(NormalRef, SizeRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::BoxPushOut error, argc=%d", argc);
			return 0;
		}

		static int Parallel(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& Normal1Ref = *Normal1;
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& Normal2Ref = *Normal2;
				auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 3);
				auto ret = FVector::Parallel(Normal1Ref, Normal2Ref, ParallelCosineThreshold);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Parallel error, argc=%d", argc);
			return 0;
		}

		static int Coincident(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& Normal1Ref = *Normal1;
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& Normal2Ref = *Normal2;
				auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 3);
				auto ret = FVector::Coincident(Normal1Ref, Normal2Ref, ParallelCosineThreshold);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Coincident error, argc=%d", argc);
			return 0;
		}

		static int Orthogonal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& Normal1Ref = *Normal1;
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 2);
				auto& Normal2Ref = *Normal2;
				auto OrthogonalCosineThreshold = LuaObject::checkValue<float>(L, 3);
				auto ret = FVector::Orthogonal(Normal1Ref, Normal2Ref, OrthogonalCosineThreshold);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Orthogonal error, argc=%d", argc);
			return 0;
		}

		static int Coplanar(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 5) {
				auto Base1 = LuaObject::checkValue<FVector*>(L, 1);
				auto& Base1Ref = *Base1;
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
				auto& Normal1Ref = *Normal1;
				auto Base2 = LuaObject::checkValue<FVector*>(L, 3);
				auto& Base2Ref = *Base2;
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 4);
				auto& Normal2Ref = *Normal2;
				auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 5);
				auto ret = FVector::Coplanar(Base1Ref, Normal1Ref, Base2Ref, Normal2Ref, ParallelCosineThreshold);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Coplanar error, argc=%d", argc);
			return 0;
		}

		static int Triple(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto X = LuaObject::checkValue<FVector*>(L, 1);
				auto& XRef = *X;
				auto Y = LuaObject::checkValue<FVector*>(L, 2);
				auto& YRef = *Y;
				auto Z = LuaObject::checkValue<FVector*>(L, 3);
				auto& ZRef = *Z;
				auto ret = FVector::Triple(XRef, YRef, ZRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector::Triple error, argc=%d", argc);
			return 0;
		}

		static int RadiansToDegrees(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto RadVector = LuaObject::checkValue<FVector*>(L, 1);
				auto& RadVectorRef = *RadVector;
				auto ret = __newFVector();
				*ret = FVector::RadiansToDegrees(RadVectorRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::RadiansToDegrees error, argc=%d", argc);
			return 0;
		}

		static int DegreesToRadians(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto DegVector = LuaObject::checkValue<FVector*>(L, 1);
				auto& DegVectorRef = *DegVector;
				auto ret = __newFVector();
				*ret = FVector::DegreesToRadians(DegVectorRef);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector::DegreesToRadians error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FVector");
			LuaObject::addOperator(L, "__add", __add);
			LuaObject::addOperator(L, "__sub", __sub);
			LuaObject::addOperator(L, "__mul", __mul);
			LuaObject::addOperator(L, "__div", __div);
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addField(L, "X", get_X, set_X, true);
			LuaObject::addField(L, "Y", get_Y, set_Y, true);
			LuaObject::addField(L, "Z", get_Z, set_Z, true);
			LuaObject::addField(L, "ZeroVector", get_ZeroVector, nullptr, false);
			LuaObject::addField(L, "OneVector", get_OneVector, nullptr, false);
			LuaObject::addField(L, "UpVector", get_UpVector, nullptr, false);
			LuaObject::addField(L, "ForwardVector", get_ForwardVector, nullptr, false);
			LuaObject::addField(L, "RightVector", get_RightVector, nullptr, false);
			LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
			LuaObject::addMethod(L, "Equals", Equals, true);
			LuaObject::addMethod(L, "AllComponentsEqual", AllComponentsEqual, true);
			LuaObject::addMethod(L, "Component", Component, true);
			LuaObject::addMethod(L, "GetComponentForAxis", GetComponentForAxis, true);
			LuaObject::addMethod(L, "SetComponentForAxis", SetComponentForAxis, true);
			LuaObject::addMethod(L, "Set", Set, true);
			LuaObject::addMethod(L, "GetMax", GetMax, true);
			LuaObject::addMethod(L, "GetAbsMax", GetAbsMax, true);
			LuaObject::addMethod(L, "GetMin", GetMin, true);
			LuaObject::addMethod(L, "GetAbsMin", GetAbsMin, true);
			LuaObject::addMethod(L, "ComponentMin", ComponentMin, true);
			LuaObject::addMethod(L, "ComponentMax", ComponentMax, true);
			LuaObject::addMethod(L, "GetAbs", GetAbs, true);
			LuaObject::addMethod(L, "Size", Size, true);
			LuaObject::addMethod(L, "SizeSquared", SizeSquared, true);
			LuaObject::addMethod(L, "Size2D", Size2D, true);
			LuaObject::addMethod(L, "SizeSquared2D", SizeSquared2D, true);
			LuaObject::addMethod(L, "IsNearlyZero", IsNearlyZero, true);
			LuaObject::addMethod(L, "IsZero", IsZero, true);
			LuaObject::addMethod(L, "Normalize", Normalize, true);
			LuaObject::addMethod(L, "IsNormalized", IsNormalized, true);
			LuaObject::addMethod(L, "ToDirectionAndLength", ToDirectionAndLength, true);
			LuaObject::addMethod(L, "GetSignVector", GetSignVector, true);
			LuaObject::addMethod(L, "Projection", Projection, true);
			LuaObject::addMethod(L, "GetUnsafeNormal", GetUnsafeNormal, true);
			LuaObject::addMethod(L, "GridSnap", GridSnap, true);
			LuaObject::addMethod(L, "BoundToCube", BoundToCube, true);
			LuaObject::addMethod(L, "GetClampedToSize", GetClampedToSize, true);
			LuaObject::addMethod(L, "GetClampedToSize2D", GetClampedToSize2D, true);
			LuaObject::addMethod(L, "GetClampedToMaxSize", GetClampedToMaxSize, true);
			LuaObject::addMethod(L, "GetClampedToMaxSize2D", GetClampedToMaxSize2D, true);
			LuaObject::addMethod(L, "AddBounded", AddBounded, true);
			LuaObject::addMethod(L, "Reciprocal", Reciprocal, true);
			LuaObject::addMethod(L, "IsUniform", IsUniform, true);
			LuaObject::addMethod(L, "MirrorByVector", MirrorByVector, true);
			LuaObject::addMethod(L, "RotateAngleAxis", RotateAngleAxis, true);
			LuaObject::addMethod(L, "GetSafeNormal", GetSafeNormal, true);
			LuaObject::addMethod(L, "GetSafeNormal2D", GetSafeNormal2D, true);
			LuaObject::addMethod(L, "CosineAngle2D", CosineAngle2D, true);
			LuaObject::addMethod(L, "ProjectOnTo", ProjectOnTo, true);
			LuaObject::addMethod(L, "ProjectOnToNormal", ProjectOnToNormal, true);
			LuaObject::addMethod(L, "ToOrientationRotator", ToOrientationRotator, true);
			LuaObject::addMethod(L, "Rotation", Rotation, true);
			LuaObject::addMethod(L, "FindBestAxisVectors", FindBestAxisVectors, true);
			LuaObject::addMethod(L, "UnwindEuler", UnwindEuler, true);
			LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
			LuaObject::addMethod(L, "IsUnit", IsUnit, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "ToCompactString", ToCompactString, true);
			LuaObject::addMethod(L, "InitFromString", InitFromString, true);
			LuaObject::addMethod(L, "UnitCartesianToSpherical", UnitCartesianToSpherical, true);
			LuaObject::addMethod(L, "HeadingAngle", HeadingAngle, true);
			LuaObject::addMethod(L, "CrossProduct", CrossProduct, false);
			LuaObject::addMethod(L, "DotProduct", DotProduct, false);
			LuaObject::addMethod(L, "CreateOrthonormalBasis", CreateOrthonormalBasis, false);
			LuaObject::addMethod(L, "PointsAreSame", PointsAreSame, false);
			LuaObject::addMethod(L, "PointsAreNear", PointsAreNear, false);
			LuaObject::addMethod(L, "PointPlaneDist", PointPlaneDist, false);
			LuaObject::addMethod(L, "PointPlaneProject", PointPlaneProject, false);
			LuaObject::addMethod(L, "VectorPlaneProject", VectorPlaneProject, false);
			LuaObject::addMethod(L, "Dist", Dist, false);
			LuaObject::addMethod(L, "Distance", Distance, false);
			LuaObject::addMethod(L, "DistXY", DistXY, false);
			LuaObject::addMethod(L, "Dist2D", Dist2D, false);
			LuaObject::addMethod(L, "DistSquared", DistSquared, false);
			LuaObject::addMethod(L, "DistSquaredXY", DistSquaredXY, false);
			LuaObject::addMethod(L, "DistSquared2D", DistSquared2D, false);
			LuaObject::addMethod(L, "BoxPushOut", BoxPushOut, false);
			LuaObject::addMethod(L, "Parallel", Parallel, false);
			LuaObject::addMethod(L, "Coincident", Coincident, false);
			LuaObject::addMethod(L, "Orthogonal", Orthogonal, false);
			LuaObject::addMethod(L, "Coplanar", Coplanar, false);
			LuaObject::addMethod(L, "Triple", Triple, false);
			LuaObject::addMethod(L, "RadiansToDegrees", RadiansToDegrees, false);
			LuaObject::addMethod(L, "DegreesToRadians", DegreesToRadians, false);
			LuaObject::finishType(L, "FVector", __ctor, __gc);
		}

	};

	struct FVector2DWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FVector2D();
				LuaObject::push<FVector2D>(L, "FVector2D", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto _a0Val = (EForceInit)_a0;
				auto self = new FVector2D(_a0Val);
				LuaObject::push<FVector2D>(L, "FVector2D", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 3) {
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				auto self = new FVector2D(InX, InY);
				LuaObject::push<FVector2D>(L, "FVector2D", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FVector2D);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __add(lua_State* L) {
			CheckSelf(FVector2D);
			if (LuaObject::matchType(L, 2, "FVector2D")) {
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector2D();
				*ret = (*self + VRef);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (lua_isnumber(L, 2)) {
				auto A = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = (*self + A);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector2D operator__add error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __sub(lua_State* L) {
			CheckSelf(FVector2D);
			if (LuaObject::matchType(L, 2, "FVector2D")) {
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector2D();
				*ret = (*self - VRef);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (lua_isnumber(L, 2)) {
				auto A = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = (*self - A);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector2D operator__sub error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __mul(lua_State* L) {
			CheckSelf(FVector2D);
			if (lua_isnumber(L, 2)) {
				auto Scale = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = (*self * Scale);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (LuaObject::matchType(L, 2, "FVector2D")) {
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector2D();
				*ret = (*self * VRef);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector2D operator__mul error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __div(lua_State* L) {
			CheckSelf(FVector2D);
			if (lua_isnumber(L, 2)) {
				auto Scale = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = (*self / Scale);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (LuaObject::matchType(L, 2, "FVector2D")) {
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& VRef = *V;
				auto ret = __newFVector2D();
				*ret = (*self / VRef);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FVector2D operator__div error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FVector2D);
			if (LuaObject::matchType(L, 2, "FVector2D")) {
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& VRef = *V;
				auto ret = (*self == VRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int get_X(lua_State* L) {
			CheckSelf(FVector2D);
			auto& X = self->X;
			LuaObject::push(L, X);
			return 1;
		}

		static int set_X(lua_State* L) {
			CheckSelf(FVector2D);
			auto& X = self->X;
			auto XIn = LuaObject::checkValue<float>(L, 2);
			X = XIn;
			LuaObject::push(L, XIn);
			return 1;
		}

		static int get_Y(lua_State* L) {
			CheckSelf(FVector2D);
			auto& Y = self->Y;
			LuaObject::push(L, Y);
			return 1;
		}

		static int set_Y(lua_State* L) {
			CheckSelf(FVector2D);
			auto& Y = self->Y;
			auto YIn = LuaObject::checkValue<float>(L, 2);
			Y = YIn;
			LuaObject::push(L, YIn);
			return 1;
		}

		static int get_ZeroVector(lua_State* L) {
			auto& ZeroVector = FVector2D::ZeroVector;
			LuaObject::push<FVector2D>(L, "FVector2D", &ZeroVector);
			return 1;
		}

		static int get_UnitVector(lua_State* L) {
			auto& UnitVector = FVector2D::UnitVector;
			LuaObject::push<FVector2D>(L, "FVector2D", &UnitVector);
			return 1;
		}

		static int Component(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector2D);
				auto Index = LuaObject::checkValue<int>(L, 2);
				auto ret = self->Component(Index);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::Component error, argc=%d", argc);
			return 0;
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector2D);
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& VRef = *V;
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(VRef, Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::Equals error, argc=%d", argc);
			return 0;
		}

		static int Set(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector2D);
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				self->Set(InX, InY);
				return 0;
			}
			luaL_error(L, "call FVector2D::Set error, argc=%d", argc);
			return 0;
		}

		static int GetMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->GetMax();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::GetMax error, argc=%d", argc);
			return 0;
		}

		static int GetAbsMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->GetAbsMax();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::GetAbsMax error, argc=%d", argc);
			return 0;
		}

		static int GetMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->GetMin();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::GetMin error, argc=%d", argc);
			return 0;
		}

		static int Size(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->Size();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::Size error, argc=%d", argc);
			return 0;
		}

		static int SizeSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->SizeSquared();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::SizeSquared error, argc=%d", argc);
			return 0;
		}

		static int GetRotated(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector2D);
				auto AngleDeg = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = self->GetRotated(AngleDeg);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D::GetRotated error, argc=%d", argc);
			return 0;
		}

		static int GetSafeNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector2D);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = self->GetSafeNormal(Tolerance);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D::GetSafeNormal error, argc=%d", argc);
			return 0;
		}

		static int Normalize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector2D);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				self->Normalize(Tolerance);
				return 0;
			}
			luaL_error(L, "call FVector2D::Normalize error, argc=%d", argc);
			return 0;
		}

		static int IsNearlyZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector2D);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsNearlyZero(Tolerance);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::IsNearlyZero error, argc=%d", argc);
			return 0;
		}

		static int ToDirectionAndLength(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector2D);
				auto OutDir = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& OutDirRef = *OutDir;
				auto OutLength = LuaObject::checkValue<float>(L, 3);
				self->ToDirectionAndLength(OutDirRef, OutLength);
				LuaObject::push<FVector2D>(L, "FVector2D", OutDir);
				LuaObject::push(L, OutLength);
				return 2;
			}
			luaL_error(L, "call FVector2D::ToDirectionAndLength error, argc=%d", argc);
			return 0;
		}

		static int IsZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->IsZero();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::IsZero error, argc=%d", argc);
			return 0;
		}

		static int RoundToVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = __newFVector2D();
				*ret = self->RoundToVector();
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D::RoundToVector error, argc=%d", argc);
			return 0;
		}

		static int ClampAxes(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FVector2D);
				auto MinAxisVal = LuaObject::checkValue<float>(L, 2);
				auto MaxAxisVal = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector2D();
				*ret = self->ClampAxes(MinAxisVal, MaxAxisVal);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D::ClampAxes error, argc=%d", argc);
			return 0;
		}

		static int GetSignVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = __newFVector2D();
				*ret = self->GetSignVector();
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D::GetSignVector error, argc=%d", argc);
			return 0;
		}

		static int GetAbs(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = __newFVector2D();
				*ret = self->GetAbs();
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D::GetAbs error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::ToString error, argc=%d", argc);
			return 0;
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FVector2D);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::InitFromString error, argc=%d", argc);
			return 0;
		}

		static int DiagnosticCheckNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				self->DiagnosticCheckNaN();
				return 0;
			}
			luaL_error(L, "call FVector2D::DiagnosticCheckNaN error, argc=%d", argc);
			return 0;
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::ContainsNaN error, argc=%d", argc);
			return 0;
		}

		static int SphericalToUnitCartesian(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FVector2D);
				auto ret = __newFVector();
				*ret = self->SphericalToUnitCartesian();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FVector2D::SphericalToUnitCartesian error, argc=%d", argc);
			return 0;
		}

		static int DotProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FVector2D*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& BRef = *B;
				auto ret = FVector2D::DotProduct(ARef, BRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::DotProduct error, argc=%d", argc);
			return 0;
		}

		static int DistSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector2D*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector2D::DistSquared(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::DistSquared error, argc=%d", argc);
			return 0;
		}

		static int Distance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto V1 = LuaObject::checkValue<FVector2D*>(L, 1);
				auto& V1Ref = *V1;
				auto V2 = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& V2Ref = *V2;
				auto ret = FVector2D::Distance(V1Ref, V2Ref);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::Distance error, argc=%d", argc);
			return 0;
		}

		static int CrossProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FVector2D*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& BRef = *B;
				auto ret = FVector2D::CrossProduct(ARef, BRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FVector2D::CrossProduct error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FVector2D");
			LuaObject::addOperator(L, "__add", __add);
			LuaObject::addOperator(L, "__sub", __sub);
			LuaObject::addOperator(L, "__mul", __mul);
			LuaObject::addOperator(L, "__div", __div);
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addField(L, "X", get_X, set_X, true);
			LuaObject::addField(L, "Y", get_Y, set_Y, true);
			LuaObject::addField(L, "ZeroVector", get_ZeroVector, nullptr, false);
			LuaObject::addField(L, "UnitVector", get_UnitVector, nullptr, false);
			LuaObject::addMethod(L, "Component", Component, true);
			LuaObject::addMethod(L, "Equals", Equals, true);
			LuaObject::addMethod(L, "Set", Set, true);
			LuaObject::addMethod(L, "GetMax", GetMax, true);
			LuaObject::addMethod(L, "GetAbsMax", GetAbsMax, true);
			LuaObject::addMethod(L, "GetMin", GetMin, true);
			LuaObject::addMethod(L, "Size", Size, true);
			LuaObject::addMethod(L, "SizeSquared", SizeSquared, true);
			LuaObject::addMethod(L, "GetRotated", GetRotated, true);
			LuaObject::addMethod(L, "GetSafeNormal", GetSafeNormal, true);
			LuaObject::addMethod(L, "Normalize", Normalize, true);
			LuaObject::addMethod(L, "IsNearlyZero", IsNearlyZero, true);
			LuaObject::addMethod(L, "ToDirectionAndLength", ToDirectionAndLength, true);
			LuaObject::addMethod(L, "IsZero", IsZero, true);
			LuaObject::addMethod(L, "RoundToVector", RoundToVector, true);
			LuaObject::addMethod(L, "ClampAxes", ClampAxes, true);
			LuaObject::addMethod(L, "GetSignVector", GetSignVector, true);
			LuaObject::addMethod(L, "GetAbs", GetAbs, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "InitFromString", InitFromString, true);
			LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
			LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
			LuaObject::addMethod(L, "SphericalToUnitCartesian", SphericalToUnitCartesian, true);
			LuaObject::addMethod(L, "DotProduct", DotProduct, false);
			LuaObject::addMethod(L, "DistSquared", DistSquared, false);
			LuaObject::addMethod(L, "Distance", Distance, false);
			LuaObject::addMethod(L, "CrossProduct", CrossProduct, false);
			LuaObject::finishType(L, "FVector2D", __ctor, __gc);
		}

	};

	struct FRandomStreamWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FRandomStream();
				LuaObject::push<FRandomStream>(L, "FRandomStream", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InSeed = LuaObject::checkValue<int>(L, 2);
				auto self = new FRandomStream(InSeed);
				LuaObject::push<FRandomStream>(L, "FRandomStream", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRandomStream() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FRandomStream);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int Initialize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRandomStream);
				auto InSeed = LuaObject::checkValue<int>(L, 2);
				self->Initialize(InSeed);
				return 0;
			}
			luaL_error(L, "call FRandomStream::Initialize error, argc=%d", argc);
			return 0;
		}

		static int Reset(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				self->Reset();
				return 0;
			}
			luaL_error(L, "call FRandomStream::Reset error, argc=%d", argc);
			return 0;
		}

		static int GetInitialSeed(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				auto ret = self->GetInitialSeed();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::GetInitialSeed error, argc=%d", argc);
			return 0;
		}

		static int GenerateNewSeed(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				self->GenerateNewSeed();
				return 0;
			}
			luaL_error(L, "call FRandomStream::GenerateNewSeed error, argc=%d", argc);
			return 0;
		}

		static int GetFraction(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				auto ret = self->GetFraction();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::GetFraction error, argc=%d", argc);
			return 0;
		}

		static int GetUnsignedInt(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				auto ret = self->GetUnsignedInt();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::GetUnsignedInt error, argc=%d", argc);
			return 0;
		}

		static int GetUnitVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				auto ret = __newFVector();
				*ret = self->GetUnitVector();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRandomStream::GetUnitVector error, argc=%d", argc);
			return 0;
		}

		static int GetCurrentSeed(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				auto ret = self->GetCurrentSeed();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::GetCurrentSeed error, argc=%d", argc);
			return 0;
		}

		static int FRand(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				auto ret = self->FRand();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::FRand error, argc=%d", argc);
			return 0;
		}

		static int RandHelper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FRandomStream);
				auto A = LuaObject::checkValue<int>(L, 2);
				auto ret = self->RandHelper(A);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::RandHelper error, argc=%d", argc);
			return 0;
		}

		static int RandRange(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FRandomStream);
				auto Min = LuaObject::checkValue<int>(L, 2);
				auto Max = LuaObject::checkValue<int>(L, 3);
				auto ret = self->RandRange(Min, Max);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::RandRange error, argc=%d", argc);
			return 0;
		}

		static int FRandRange(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FRandomStream);
				auto InMin = LuaObject::checkValue<float>(L, 2);
				auto InMax = LuaObject::checkValue<float>(L, 3);
				auto ret = self->FRandRange(InMin, InMax);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FRandomStream::FRandRange error, argc=%d", argc);
			return 0;
		}

		static int VRand(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FRandomStream);
				auto ret = __newFVector();
				*ret = self->VRand();
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRandomStream::VRand error, argc=%d", argc);
			return 0;
		}

		static int VRandCone(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FRandomStream);
				auto Dir = LuaObject::checkValue<FVector*>(L, 2);
				auto& DirRef = *Dir;
				auto ConeHalfAngleRad = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector();
				*ret = self->VRandCone(DirRef, ConeHalfAngleRad);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 4) {
				CheckSelf(FRandomStream);
				auto Dir = LuaObject::checkValue<FVector*>(L, 2);
				auto& DirRef = *Dir;
				auto HorizontalConeHalfAngleRad = LuaObject::checkValue<float>(L, 3);
				auto VerticalConeHalfAngleRad = LuaObject::checkValue<float>(L, 4);
				auto ret = __newFVector();
				*ret = self->VRandCone(DirRef, HorizontalConeHalfAngleRad, VerticalConeHalfAngleRad);
				LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FRandomStream::VRandCone error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FRandomStream");
			LuaObject::addMethod(L, "Initialize", Initialize, true);
			LuaObject::addMethod(L, "Reset", Reset, true);
			LuaObject::addMethod(L, "GetInitialSeed", GetInitialSeed, true);
			LuaObject::addMethod(L, "GenerateNewSeed", GenerateNewSeed, true);
			LuaObject::addMethod(L, "GetFraction", GetFraction, true);
			LuaObject::addMethod(L, "GetUnsignedInt", GetUnsignedInt, true);
			LuaObject::addMethod(L, "GetUnitVector", GetUnitVector, true);
			LuaObject::addMethod(L, "GetCurrentSeed", GetCurrentSeed, true);
			LuaObject::addMethod(L, "FRand", FRand, true);
			LuaObject::addMethod(L, "RandHelper", RandHelper, true);
			LuaObject::addMethod(L, "RandRange", RandRange, true);
			LuaObject::addMethod(L, "FRandRange", FRandRange, true);
			LuaObject::addMethod(L, "VRand", VRand, true);
			LuaObject::addMethod(L, "VRandCone", VRandCone, true);
			LuaObject::finishType(L, "FRandomStream", __ctor, __gc);
		}

	};

	struct FGuidWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FGuid();
				LuaObject::push<FGuid>(L, "FGuid", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 5) {
				auto InA = LuaObject::checkValue<int>(L, 2);
				auto InAVal = (unsigned int)InA;
				auto InB = LuaObject::checkValue<int>(L, 3);
				auto InBVal = (unsigned int)InB;
				auto InC = LuaObject::checkValue<int>(L, 4);
				auto InCVal = (unsigned int)InC;
				auto InD = LuaObject::checkValue<int>(L, 5);
				auto InDVal = (unsigned int)InD;
				auto self = new FGuid(InAVal, InBVal, InCVal, InDVal);
				LuaObject::push<FGuid>(L, "FGuid", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FGuid() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FGuid);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int get_A(lua_State* L) {
			CheckSelf(FGuid);
			auto& A = self->A;
			LuaObject::push(L, A);
			return 1;
		}

		static int set_A(lua_State* L) {
			CheckSelf(FGuid);
			auto& A = self->A;
			auto AIn = LuaObject::checkValue<uint32>(L, 2);
			A = AIn;
			LuaObject::push(L, AIn);
			return 1;
		}

		static int get_B(lua_State* L) {
			CheckSelf(FGuid);
			auto& B = self->B;
			LuaObject::push(L, B);
			return 1;
		}

		static int set_B(lua_State* L) {
			CheckSelf(FGuid);
			auto& B = self->B;
			auto BIn = LuaObject::checkValue<uint32>(L, 2);
			B = BIn;
			LuaObject::push(L, BIn);
			return 1;
		}

		static int get_C(lua_State* L) {
			CheckSelf(FGuid);
			auto& C = self->C;
			LuaObject::push(L, C);
			return 1;
		}

		static int set_C(lua_State* L) {
			CheckSelf(FGuid);
			auto& C = self->C;
			auto CIn = LuaObject::checkValue<uint32>(L, 2);
			C = CIn;
			LuaObject::push(L, CIn);
			return 1;
		}

		static int get_D(lua_State* L) {
			CheckSelf(FGuid);
			auto& D = self->D;
			LuaObject::push(L, D);
			return 1;
		}

		static int set_D(lua_State* L) {
			CheckSelf(FGuid);
			auto& D = self->D;
			auto DIn = LuaObject::checkValue<uint32>(L, 2);
			D = DIn;
			LuaObject::push(L, DIn);
			return 1;
		}

		static int Invalidate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FGuid);
				self->Invalidate();
				return 0;
			}
			luaL_error(L, "call FGuid::Invalidate error, argc=%d", argc);
			return 0;
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FGuid);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FGuid::IsValid error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FGuid);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			if (argc == 2) {
				CheckSelf(FGuid);
				auto Format = LuaObject::checkValue<int>(L, 2);
				auto FormatVal = (EGuidFormats)Format;
				auto ret = self->ToString(FormatVal);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FGuid::ToString error, argc=%d", argc);
			return 0;
		}

		static int NewGuid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFGuid();
				*ret = FGuid::NewGuid();
				LuaObject::push<FGuid>(L, "FGuid", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FGuid::NewGuid error, argc=%d", argc);
			return 0;
		}

		static int Parse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto GuidString = LuaObject::checkValue<FString>(L, 1);
				auto OutGuid = LuaObject::checkValue<FGuid*>(L, 2);
				auto& OutGuidRef = *OutGuid;
				auto ret = FGuid::Parse(GuidString, OutGuidRef);
				LuaObject::push(L, ret);
				LuaObject::push<FGuid>(L, "FGuid", OutGuid);
				return 2;
			}
			luaL_error(L, "call FGuid::Parse error, argc=%d", argc);
			return 0;
		}

		static int ParseExact(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto GuidString = LuaObject::checkValue<FString>(L, 1);
				auto Format = LuaObject::checkValue<int>(L, 2);
				auto FormatVal = (EGuidFormats)Format;
				auto OutGuid = LuaObject::checkValue<FGuid*>(L, 3);
				auto& OutGuidRef = *OutGuid;
				auto ret = FGuid::ParseExact(GuidString, FormatVal, OutGuidRef);
				LuaObject::push(L, ret);
				LuaObject::push<FGuid>(L, "FGuid", OutGuid);
				return 2;
			}
			luaL_error(L, "call FGuid::ParseExact error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FGuid");
			LuaObject::addField(L, "A", get_A, set_A, true);
			LuaObject::addField(L, "B", get_B, set_B, true);
			LuaObject::addField(L, "C", get_C, set_C, true);
			LuaObject::addField(L, "D", get_D, set_D, true);
			LuaObject::addMethod(L, "Invalidate", Invalidate, true);
			LuaObject::addMethod(L, "IsValid", IsValid, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "NewGuid", NewGuid, false);
			LuaObject::addMethod(L, "Parse", Parse, false);
			LuaObject::addMethod(L, "ParseExact", ParseExact, false);
			LuaObject::finishType(L, "FGuid", __ctor, __gc);
		}

	};

	struct FBox2DWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FBox2D();
				LuaObject::push<FBox2D>(L, "FBox2D", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto _a0Val = (EForceInit)_a0;
				auto self = new FBox2D(_a0Val);
				LuaObject::push<FBox2D>(L, "FBox2D", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 3) {
				auto InMin = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& InMinRef = *InMin;
				auto InMax = LuaObject::checkValue<FVector2D*>(L, 3);
				auto& InMaxRef = *InMax;
				auto self = new FBox2D(InMinRef, InMaxRef);
				LuaObject::push<FBox2D>(L, "FBox2D", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FBox2D() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FBox2D);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FBox2D);
			if (LuaObject::matchType(L, 2, "FBox2D")) {
				auto Other = LuaObject::checkValue<FBox2D*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = (*self == OtherRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int __add(lua_State* L) {
			CheckSelf(FBox2D);
			if (LuaObject::matchType(L, 2, "FBox2D")) {
				auto Other = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = __newFBox2D();
				*ret = (*self + OtherRef);
				LuaObject::push<FBox2D>(L, "FBox2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (LuaObject::matchType(L, 2, "FBox2D")) {
				auto Other = LuaObject::checkValue<FBox2D*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = __newFBox2D();
				*ret = (*self + OtherRef);
				LuaObject::push<FBox2D>(L, "FBox2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "FBox2D operator__add error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int get_Min(lua_State* L) {
			CheckSelf(FBox2D);
			auto& Min = self->Min;
			LuaObject::pushAndLink<FVector2D>(L, udptr, "FVector2D", &Min);
			return 1;
		}

		static int set_Min(lua_State* L) {
			CheckSelf(FBox2D);
			auto& Min = self->Min;
			auto MinIn = LuaObject::checkValue<FVector2D*>(L, 2);
			Min = *MinIn;
			LuaObject::push<FVector2D>(L, "FVector2D", MinIn);
			return 1;
		}

		static int get_Max(lua_State* L) {
			CheckSelf(FBox2D);
			auto& Max = self->Max;
			LuaObject::pushAndLink<FVector2D>(L, udptr, "FVector2D", &Max);
			return 1;
		}

		static int set_Max(lua_State* L) {
			CheckSelf(FBox2D);
			auto& Max = self->Max;
			auto MaxIn = LuaObject::checkValue<FVector2D*>(L, 2);
			Max = *MaxIn;
			LuaObject::push<FVector2D>(L, "FVector2D", MaxIn);
			return 1;
		}

		static int get_bIsValid(lua_State* L) {
			CheckSelf(FBox2D);
			auto& bIsValid = self->bIsValid;
			LuaObject::push(L, bIsValid);
			return 1;
		}

		static int set_bIsValid(lua_State* L) {
			CheckSelf(FBox2D);
			auto& bIsValid = self->bIsValid;
			auto bIsValidIn = LuaObject::checkValue<bool>(L, 2);
			bIsValid = bIsValidIn;
			LuaObject::push(L, bIsValidIn);
			return 1;
		}

		static int ComputeSquaredDistanceToPoint(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FBox2D);
				auto Point = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& PointRef = *Point;
				auto ret = self->ComputeSquaredDistanceToPoint(PointRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FBox2D::ComputeSquaredDistanceToPoint error, argc=%d", argc);
			return 0;
		}

		static int ExpandBy(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FBox2D);
				auto W = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFBox2D();
				*ret = self->ExpandBy(W);
				LuaObject::push<FBox2D>(L, "FBox2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FBox2D::ExpandBy error, argc=%d", argc);
			return 0;
		}

		static int GetArea(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FBox2D);
				auto ret = self->GetArea();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FBox2D::GetArea error, argc=%d", argc);
			return 0;
		}

		static int GetCenter(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FBox2D);
				auto ret = __newFVector2D();
				*ret = self->GetCenter();
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FBox2D::GetCenter error, argc=%d", argc);
			return 0;
		}

		static int GetCenterAndExtents(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				CheckSelf(FBox2D);
				auto center = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& centerRef = *center;
				auto Extents = LuaObject::checkValue<FVector2D*>(L, 3);
				auto& ExtentsRef = *Extents;
				self->GetCenterAndExtents(centerRef, ExtentsRef);
				LuaObject::push<FVector2D>(L, "FVector2D", center);
				LuaObject::push<FVector2D>(L, "FVector2D", Extents);
				return 2;
			}
			luaL_error(L, "call FBox2D::GetCenterAndExtents error, argc=%d", argc);
			return 0;
		}

		static int GetClosestPointTo(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FBox2D);
				auto Point = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& PointRef = *Point;
				auto ret = __newFVector2D();
				*ret = self->GetClosestPointTo(PointRef);
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FBox2D::GetClosestPointTo error, argc=%d", argc);
			return 0;
		}

		static int GetExtent(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FBox2D);
				auto ret = __newFVector2D();
				*ret = self->GetExtent();
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FBox2D::GetExtent error, argc=%d", argc);
			return 0;
		}

		static int GetSize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FBox2D);
				auto ret = __newFVector2D();
				*ret = self->GetSize();
				LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FBox2D::GetSize error, argc=%d", argc);
			return 0;
		}

		static int Init(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FBox2D);
				self->Init();
				return 0;
			}
			luaL_error(L, "call FBox2D::Init error, argc=%d", argc);
			return 0;
		}

		static int Intersect(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FBox2D);
				auto other = LuaObject::checkValue<FBox2D*>(L, 2);
				auto& otherRef = *other;
				auto ret = self->Intersect(otherRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FBox2D::Intersect error, argc=%d", argc);
			return 0;
		}

		static int IsInside(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FBox2D);
				auto TestPoint = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& TestPointRef = *TestPoint;
				auto ret = self->IsInside(TestPointRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FBox2D::IsInside error, argc=%d", argc);
			return 0;
		}

		static int ShiftBy(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				CheckSelf(FBox2D);
				auto Offset = LuaObject::checkValue<FVector2D*>(L, 2);
				auto& OffsetRef = *Offset;
				auto ret = __newFBox2D();
				*ret = self->ShiftBy(OffsetRef);
				LuaObject::push<FBox2D>(L, "FBox2D", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FBox2D::ShiftBy error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FBox2D);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FBox2D::ToString error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FBox2D");
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addOperator(L, "__add", __add);
			LuaObject::addField(L, "Min", get_Min, set_Min, true);
			LuaObject::addField(L, "Max", get_Max, set_Max, true);
			LuaObject::addField(L, "bIsValid", get_bIsValid, set_bIsValid, true);
			LuaObject::addMethod(L, "ComputeSquaredDistanceToPoint", ComputeSquaredDistanceToPoint, true);
			LuaObject::addMethod(L, "ExpandBy", ExpandBy, true);
			LuaObject::addMethod(L, "GetArea", GetArea, true);
			LuaObject::addMethod(L, "GetCenter", GetCenter, true);
			LuaObject::addMethod(L, "GetCenterAndExtents", GetCenterAndExtents, true);
			LuaObject::addMethod(L, "GetClosestPointTo", GetClosestPointTo, true);
			LuaObject::addMethod(L, "GetExtent", GetExtent, true);
			LuaObject::addMethod(L, "GetSize", GetSize, true);
			LuaObject::addMethod(L, "Init", Init, true);
			LuaObject::addMethod(L, "Intersect", Intersect, true);
			LuaObject::addMethod(L, "IsInside", IsInside, true);
			LuaObject::addMethod(L, "ShiftBy", ShiftBy, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::finishType(L, "FBox2D", __ctor, __gc);
		}

	};

	struct FFloatRangeBoundWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FFloatRangeBound();
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InValue = LuaObject::checkValue<int>(L, 2);
				auto InValueVal = (long long)InValue;
				auto self = new FFloatRangeBound(InValueVal);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FFloatRangeBound);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int Exclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<float>(L, 1);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::Exclusive(Value);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::Exclusive error, argc=%d", argc);
			return 0;
		}

		static int Inclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<float>(L, 1);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::Inclusive(Value);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::Inclusive error, argc=%d", argc);
			return 0;
		}

		static int Open(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::Open();
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::Open error, argc=%d", argc);
			return 0;
		}

		static int FlipInclusion(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Bound = LuaObject::checkValue<FFloatRangeBound*>(L, 1);
				auto& BoundRef = *Bound;
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::FlipInclusion(BoundRef);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::FlipInclusion error, argc=%d", argc);
			return 0;
		}

		static int MaxLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MaxLower(ARef, BRef);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::MaxLower error, argc=%d", argc);
			return 0;
		}

		static int MaxUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MaxUpper(ARef, BRef);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::MaxUpper error, argc=%d", argc);
			return 0;
		}

		static int MinLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MinLower(ARef, BRef);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::MinLower error, argc=%d", argc);
			return 0;
		}

		static int MinUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MinUpper(ARef, BRef);
				LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRangeBound::MinUpper error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FFloatRangeBound");
			LuaObject::addMethod(L, "Exclusive", Exclusive, false);
			LuaObject::addMethod(L, "Inclusive", Inclusive, false);
			LuaObject::addMethod(L, "Open", Open, false);
			LuaObject::addMethod(L, "FlipInclusion", FlipInclusion, false);
			LuaObject::addMethod(L, "MaxLower", MaxLower, false);
			LuaObject::addMethod(L, "MaxUpper", MaxUpper, false);
			LuaObject::addMethod(L, "MinLower", MinLower, false);
			LuaObject::addMethod(L, "MinUpper", MinUpper, false);
			LuaObject::finishType(L, "FFloatRangeBound", __ctor, __gc);
		}

	};

	struct FFloatRangeWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FFloatRange();
				LuaObject::push<FFloatRange>(L, "FFloatRange", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto A = LuaObject::checkValue<float>(L, 2);
				auto self = new FFloatRange(A);
				LuaObject::push<FFloatRange>(L, "FFloatRange", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 3) {
				auto A = LuaObject::checkValue<float>(L, 2);
				auto B = LuaObject::checkValue<float>(L, 3);
				auto self = new FFloatRange(A, B);
				LuaObject::push<FFloatRange>(L, "FFloatRange", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRange() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FFloatRange);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int Empty(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFFloatRange();
				*ret = FFloatRange::Empty();
				LuaObject::push<FFloatRange>(L, "FFloatRange", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRange::Empty error, argc=%d", argc);
			return 0;
		}

		static int All(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFFloatRange();
				*ret = FFloatRange::All();
				LuaObject::push<FFloatRange>(L, "FFloatRange", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRange::All error, argc=%d", argc);
			return 0;
		}

		static int AtLeast(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<float>(L, 1);
				auto ret = __newFFloatRange();
				*ret = FFloatRange::AtLeast(Value);
				LuaObject::push<FFloatRange>(L, "FFloatRange", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRange::AtLeast error, argc=%d", argc);
			return 0;
		}

		static int AtMost(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<float>(L, 1);
				auto ret = __newFFloatRange();
				*ret = FFloatRange::AtMost(Value);
				LuaObject::push<FFloatRange>(L, "FFloatRange", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatRange::AtMost error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FFloatRange");
			LuaObject::addMethod(L, "Empty", Empty, false);
			LuaObject::addMethod(L, "All", All, false);
			LuaObject::addMethod(L, "AtLeast", AtLeast, false);
			LuaObject::addMethod(L, "AtMost", AtMost, false);
			LuaObject::finishType(L, "FFloatRange", __ctor, __gc);
		}

	};

	struct FInt32RangeBoundWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FInt32RangeBound();
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InValue = LuaObject::checkValue<int>(L, 2);
				auto InValueVal = (long long)InValue;
				auto self = new FInt32RangeBound(InValueVal);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FInt32RangeBound);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int Exclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<int>(L, 1);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::Exclusive(Value);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::Exclusive error, argc=%d", argc);
			return 0;
		}

		static int Inclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<int>(L, 1);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::Inclusive(Value);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::Inclusive error, argc=%d", argc);
			return 0;
		}

		static int Open(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::Open();
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::Open error, argc=%d", argc);
			return 0;
		}

		static int FlipInclusion(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Bound = LuaObject::checkValue<FInt32RangeBound*>(L, 1);
				auto& BoundRef = *Bound;
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::FlipInclusion(BoundRef);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::FlipInclusion error, argc=%d", argc);
			return 0;
		}

		static int MaxLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MaxLower(ARef, BRef);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::MaxLower error, argc=%d", argc);
			return 0;
		}

		static int MaxUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MaxUpper(ARef, BRef);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::MaxUpper error, argc=%d", argc);
			return 0;
		}

		static int MinLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MinLower(ARef, BRef);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::MinLower error, argc=%d", argc);
			return 0;
		}

		static int MinUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 1);
				auto& ARef = *A;
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto& BRef = *B;
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MinUpper(ARef, BRef);
				LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32RangeBound::MinUpper error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FInt32RangeBound");
			LuaObject::addMethod(L, "Exclusive", Exclusive, false);
			LuaObject::addMethod(L, "Inclusive", Inclusive, false);
			LuaObject::addMethod(L, "Open", Open, false);
			LuaObject::addMethod(L, "FlipInclusion", FlipInclusion, false);
			LuaObject::addMethod(L, "MaxLower", MaxLower, false);
			LuaObject::addMethod(L, "MaxUpper", MaxUpper, false);
			LuaObject::addMethod(L, "MinLower", MinLower, false);
			LuaObject::addMethod(L, "MinUpper", MinUpper, false);
			LuaObject::finishType(L, "FInt32RangeBound", __ctor, __gc);
		}

	};

	struct FInt32RangeWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FInt32Range();
				LuaObject::push<FInt32Range>(L, "FInt32Range", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto A = LuaObject::checkValue<int>(L, 2);
				auto self = new FInt32Range(A);
				LuaObject::push<FInt32Range>(L, "FInt32Range", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 3) {
				auto A = LuaObject::checkValue<int>(L, 2);
				auto B = LuaObject::checkValue<int>(L, 3);
				auto self = new FInt32Range(A, B);
				LuaObject::push<FInt32Range>(L, "FInt32Range", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32Range() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FInt32Range);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int Empty(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFInt32Range();
				*ret = FInt32Range::Empty();
				LuaObject::push<FInt32Range>(L, "FInt32Range", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32Range::Empty error, argc=%d", argc);
			return 0;
		}

		static int All(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 0) {
				auto ret = __newFInt32Range();
				*ret = FInt32Range::All();
				LuaObject::push<FInt32Range>(L, "FInt32Range", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32Range::All error, argc=%d", argc);
			return 0;
		}

		static int AtLeast(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<int>(L, 1);
				auto ret = __newFInt32Range();
				*ret = FInt32Range::AtLeast(Value);
				LuaObject::push<FInt32Range>(L, "FInt32Range", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32Range::AtLeast error, argc=%d", argc);
			return 0;
		}

		static int AtMost(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto Value = LuaObject::checkValue<int>(L, 1);
				auto ret = __newFInt32Range();
				*ret = FInt32Range::AtMost(Value);
				LuaObject::push<FInt32Range>(L, "FInt32Range", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32Range::AtMost error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FInt32Range");
			LuaObject::addMethod(L, "Empty", Empty, false);
			LuaObject::addMethod(L, "All", All, false);
			LuaObject::addMethod(L, "AtLeast", AtLeast, false);
			LuaObject::addMethod(L, "AtMost", AtMost, false);
			LuaObject::finishType(L, "FInt32Range", __ctor, __gc);
		}

	};

	struct FFloatIntervalWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FFloatInterval();
				LuaObject::push<FFloatInterval>(L, "FFloatInterval", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 3) {
				auto InMin = LuaObject::checkValue<float>(L, 2);
				auto InMax = LuaObject::checkValue<float>(L, 3);
				auto self = new FFloatInterval(InMin, InMax);
				LuaObject::push<FFloatInterval>(L, "FFloatInterval", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FFloatInterval() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FFloatInterval);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FFloatInterval");
			LuaObject::finishType(L, "FFloatInterval", __ctor, __gc);
		}

	};

	struct FInt32IntervalWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FInt32Interval();
				LuaObject::push<FInt32Interval>(L, "FInt32Interval", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 3) {
				auto InMin = LuaObject::checkValue<int>(L, 2);
				auto InMax = LuaObject::checkValue<int>(L, 3);
				auto self = new FInt32Interval(InMin, InMax);
				LuaObject::push<FInt32Interval>(L, "FInt32Interval", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FInt32Interval() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FInt32Interval);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FInt32Interval");
			LuaObject::finishType(L, "FInt32Interval", __ctor, __gc);
		}

	};

	struct FPrimaryAssetTypeWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FPrimaryAssetType();
				LuaObject::push<FPrimaryAssetType>(L, "FPrimaryAssetType", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InName = LuaObject::checkValue<int>(L, 2);
				auto InNameVal = (EName)InName;
				auto self = new FPrimaryAssetType(InNameVal);
				LuaObject::push<FPrimaryAssetType>(L, "FPrimaryAssetType", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FPrimaryAssetType() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FPrimaryAssetType);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FPrimaryAssetType);
			if (LuaObject::matchType(L, 2, "FPrimaryAssetType")) {
				auto Other = LuaObject::checkValue<FPrimaryAssetType*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = (*self == OtherRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FPrimaryAssetType);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FPrimaryAssetType::IsValid error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FPrimaryAssetType);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FPrimaryAssetType::ToString error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FPrimaryAssetType");
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addMethod(L, "IsValid", IsValid, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::finishType(L, "FPrimaryAssetType", __ctor, __gc);
		}

	};

	struct FPrimaryAssetIdWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FPrimaryAssetId();
				LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InString = LuaObject::checkValue<FString>(L, 2);
				auto self = new FPrimaryAssetId(InString);
				LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FPrimaryAssetId() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FPrimaryAssetId);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FPrimaryAssetId);
			if (LuaObject::matchType(L, 2, "FPrimaryAssetId")) {
				auto Other = LuaObject::checkValue<FPrimaryAssetId*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = (*self == OtherRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int get_PrimaryAssetType(lua_State* L) {
			CheckSelf(FPrimaryAssetId);
			auto& PrimaryAssetType = self->PrimaryAssetType;
			LuaObject::pushAndLink<FPrimaryAssetType>(L, udptr, "FPrimaryAssetType", &PrimaryAssetType);
			return 1;
		}

		static int set_PrimaryAssetType(lua_State* L) {
			CheckSelf(FPrimaryAssetId);
			auto& PrimaryAssetType = self->PrimaryAssetType;
			auto PrimaryAssetTypeIn = LuaObject::checkValue<FPrimaryAssetType*>(L, 2);
			PrimaryAssetType = *PrimaryAssetTypeIn;
			LuaObject::push<FPrimaryAssetType>(L, "FPrimaryAssetType", PrimaryAssetTypeIn);
			return 1;
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FPrimaryAssetId);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FPrimaryAssetId::IsValid error, argc=%d", argc);
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FPrimaryAssetId);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FPrimaryAssetId::ToString error, argc=%d", argc);
			return 0;
		}

		static int FromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto String = LuaObject::checkValue<FString>(L, 1);
				auto ret = __newFPrimaryAssetId();
				*ret = FPrimaryAssetId::FromString(String);
				LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", ret, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FPrimaryAssetId::FromString error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FPrimaryAssetId");
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addField(L, "PrimaryAssetType", get_PrimaryAssetType, set_PrimaryAssetType, true);
			LuaObject::addMethod(L, "IsValid", IsValid, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "FromString", FromString, false);
			LuaObject::finishType(L, "FPrimaryAssetId", __ctor, __gc);
		}

	};

	struct FDateTimeWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = new FDateTime();
				LuaObject::push<FDateTime>(L, "FDateTime", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc == 2) {
				auto InTicks = LuaObject::checkValue<int64>(L, 2);
				auto self = new FDateTime(InTicks);
				LuaObject::push<FDateTime>(L, "FDateTime", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			if (argc > 2) {
				auto year = LuaObject::checkValueOpt<int>(L, 2, 0);
				auto month = LuaObject::checkValueOpt<int>(L, 3, 0);
				auto day = LuaObject::checkValueOpt<int>(L, 4, 0);
				auto hour = LuaObject::checkValueOpt<int>(L, 5, 0);
				auto minute = LuaObject::checkValueOpt<int>(L, 6, 0);
				auto second = LuaObject::checkValueOpt<int>(L, 7, 0);
				auto millisecond = LuaObject::checkValueOpt<int>(L, 8, 0);
				auto self = new FDateTime(year, month, day, hour, minute, second, millisecond);
				LuaObject::push<FDateTime>(L, "FDateTime", self, UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FDateTime() error, argc=%d", argc);
			return 0;
		}

		static int __gc(lua_State* L) {
			CheckSelfSafe(FDateTime);
			LuaObject::releaseLink(L, udptr);
			if (udptr->flag & UD_AUTOGC) delete self;
			return 0;
		}

		static int __eq(lua_State* L) {
			CheckSelf(FDateTime);
			if (LuaObject::matchType(L, 2, "FDateTime")) {
				auto Other = LuaObject::checkValue<FDateTime*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = (*self == OtherRef);
				LuaObject::push(L, ret);
				return 1;
			}
			LuaObject::push(L, false);
			return 1;
		}

		static int __lt(lua_State* L) {
			CheckSelf(FDateTime);
			if (LuaObject::matchType(L, 2, "FDateTime")) {
				auto Other = LuaObject::checkValue<FDateTime*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = (*self < OtherRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "FDateTime operator__lt error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int __le(lua_State* L) {
			CheckSelf(FDateTime);
			if (LuaObject::matchType(L, 2, "FDateTime")) {
				auto Other = LuaObject::checkValue<FDateTime*>(L, 2);
				auto& OtherRef = *Other;
				auto ret = (*self <= OtherRef);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "FDateTime operator__le error, arg=%d", lua_typename(L, 2));
			return 0;
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::ToString error, argc=%d", argc);
			return 0;
		}

		static int GetDate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				int OutYear = 0, OutMonth = 0, OutDay = 0;
				self->GetDate(OutYear, OutMonth, OutDay);
				LuaObject::push(L, OutYear);
				LuaObject::push(L, OutMonth);
				LuaObject::push(L, OutDay);
				return 3;
			}
			luaL_error(L, "call FDateTime::GetDate error, argc=%d", argc);
			return 0;
		}

		static int GetDay(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetDay();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetDay error, argc=%d", argc);
			return 0;
		}

		static int GetDayOfWeek(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetDayOfWeek();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetDayOfWeek error, argc=%d", argc);
			return 0;
		}

		static int GetDayOfYear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetDayOfWeek();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetDayOfWeek error, argc=%d", argc);
			return 0;
		}

		static int GetHour(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetHour();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetHour error, argc=%d", argc);
			return 0;
		}

		static int GetHour12(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetHour12();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetHour12 error, argc=%d", argc);
			return 0;
		}

		static int GetJulianDay(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetJulianDay();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetJulianDay error, argc=%d", argc);
			return 0;
		}

		static int GetModifiedJulianDay(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetModifiedJulianDay();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetModifiedJulianDay error, argc=%d", argc);
			return 0;
		}

		static int GetMillisecond(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetMillisecond();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetMillisecond error, argc=%d", argc);
			return 0;
		}

		static int GetMinute(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetMinute();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetMinute error, argc=%d", argc);
			return 0;
		}

		static int GetMonth(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetMonth();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetMonth error, argc=%d", argc);
			return 0;
		}

		static int GetMonthOfYear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetMonthOfYear();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetMonthOfYear error, argc=%d", argc);
			return 0;
		}

		static int GetSecond(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetSecond();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetSecond error, argc=%d", argc);
			return 0;
		}

		static int GetTicks(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetTicks();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetTicks error, argc=%d", argc);
			return 0;
		}

		static int GetYear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->GetYear();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::GetYear error, argc=%d", argc);
			return 0;
		}

		static int IsAfternoon(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->IsAfternoon();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::IsAfternoon error, argc=%d", argc);
			return 0;
		}

		static int IsMorning(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->IsMorning();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::IsMorning error, argc=%d", argc);
			return 0;
		}

		static int ToHttpDate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->ToHttpDate();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::ToHttpDate error, argc=%d", argc);
			return 0;
		}

		static int ToUnixTimestamp(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				CheckSelf(FDateTime);
				auto ret = self->ToUnixTimestamp();
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::ToUnixTimestamp error, argc=%d", argc);
			return 0;
		}

		static int DaysInMonth(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto InYear = LuaObject::checkValue<int32>(L, 1);
				auto InMonth = LuaObject::checkValue<int32>(L, 2);
				auto ret = FDateTime::DaysInMonth(InYear, InMonth);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::DaysInMonth error, argc=%d", argc);
			return 0;
		}

		static int DaysInYear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto InYear = LuaObject::checkValue<int32>(L, 1);
				auto ret = FDateTime::DaysInYear(InYear);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::DaysInYear error, argc=%d", argc);
			return 0;
		}

		static int FromJulianDay(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto InJulianDay = LuaObject::checkValue<double>(L, 1);
				auto ret = FDateTime::FromJulianDay(InJulianDay);
				LuaObject::push(L, "FDateTime", new FDateTime(ret), UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FDateTime::FromJulianDay error, argc=%d", argc);
			return 0;
		}

		static int FromUnixTimestamp(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto InUnixTime = LuaObject::checkValue<int64>(L, 1);
				auto ret = FDateTime::FromUnixTimestamp(InUnixTime);
				LuaObject::push(L, "FDateTime", new FDateTime(ret), UD_AUTOGC | UD_VALUETYPE);
				return 1;
			}
			luaL_error(L, "call FDateTime::FromUnixTimestamp error, argc=%d", argc);
			return 0;
		}

		static int IsLeapYear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto InYear = LuaObject::checkValue<int32>(L, 1);
				auto ret = FDateTime::IsLeapYear(InYear);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::IsLeapYear error, argc=%d", argc);
			return 0;
		}

		static int MaxValue(lua_State* L) {
			auto argc = lua_gettop(L);
			auto ret = FDateTime::MaxValue();
			LuaObject::push(L, "FDateTime", new FDateTime(ret), UD_AUTOGC | UD_VALUETYPE);
			return 1;
		}

		static int MinValue(lua_State* L) {
			auto argc = lua_gettop(L);
			auto ret = FDateTime::MinValue();
			LuaObject::push(L, "FDateTime", new FDateTime(ret), UD_AUTOGC | UD_VALUETYPE);
			return 1;
		}

		static int Now(lua_State* L) {
			auto argc = lua_gettop(L);
			auto ret = FDateTime::Now();
			LuaObject::push(L, "FDateTime", new FDateTime(ret), UD_AUTOGC | UD_VALUETYPE);
			return 1;
		}

		static int Parse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto InDateTimeString = LuaObject::checkValue<FString>(L, 1);
				FDateTime outDateTime;
				auto ret = FDateTime::Parse(InDateTimeString, outDateTime);
				LuaObject::push(L, ret);
				if (ret) {
					LuaObject::push(L, "FDateTime", new FDateTime(outDateTime), UD_AUTOGC | UD_VALUETYPE);
					return 2;
				}
				return 1;
			}
			luaL_error(L, "call FDateTime::Parse error, argc=%d", argc);
			return 0;
		}

		static int ParseHttpDate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto InHttpDate = LuaObject::checkValue<FString>(L, 1);
				FDateTime outDateTime;
				auto ret = FDateTime::ParseHttpDate(InHttpDate, outDateTime);
				LuaObject::push(L, ret);
				if (ret) {
					LuaObject::push(L, "FDateTime", new FDateTime(outDateTime), UD_AUTOGC | UD_VALUETYPE);
					return 2;
				}
				return 1;
			}
			luaL_error(L, "call FDateTime::ParseHttpDate error, argc=%d", argc);
			return 0;
		}

		static int Today(lua_State* L) {
			auto argc = lua_gettop(L);
			auto ret = FDateTime::Today();
			LuaObject::push(L, "FDateTime", new FDateTime(ret), UD_AUTOGC | UD_VALUETYPE);
			return 1;
		}

		static int UtcNow(lua_State* L) {
			auto argc = lua_gettop(L);
			auto ret = FDateTime::UtcNow();
			LuaObject::push(L, "FDateTime", new FDateTime(ret), UD_AUTOGC | UD_VALUETYPE);
			return 1;
		}

		static int Validate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 7) {
				auto InYear = LuaObject::checkValue<int32>(L, 1);
				auto InMonth = LuaObject::checkValue<int32>(L, 2);
				auto InDay = LuaObject::checkValue<int32>(L, 3);
				auto InHour = LuaObject::checkValue<int32>(L, 4);
				auto InMinute = LuaObject::checkValue<int32>(L, 5);
				auto InSecond = LuaObject::checkValue<int32>(L, 6);
				auto InMillisecond = LuaObject::checkValue<int32>(L, 7);
				auto ret = FDateTime::Validate(InYear, InMonth, InDay, InHour, InMinute, InSecond, InMillisecond);
				LuaObject::push(L, ret);
				return 1;
			}
			luaL_error(L, "call FDateTime::ToString error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L) {
			AutoStack autoStack(L);
			LuaObject::newType(L, "FDateTime");
			LuaObject::addOperator(L, "__eq", __eq);
			LuaObject::addOperator(L, "__lt", __lt);
			LuaObject::addOperator(L, "__le", __le);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "GetDate", GetDate, true);
			LuaObject::addMethod(L, "GetDay", GetDay, true);
			LuaObject::addMethod(L, "GetDayOfWeek", GetDayOfWeek, true);
			LuaObject::addMethod(L, "GetDayOfYear", GetDayOfYear, true);
			LuaObject::addMethod(L, "GetHour", GetHour, true);
			LuaObject::addMethod(L, "GetHour12", GetHour12, true);
			LuaObject::addMethod(L, "GetJulianDay", GetJulianDay, true);
			LuaObject::addMethod(L, "GetModifiedJulianDay", GetModifiedJulianDay, true);
			LuaObject::addMethod(L, "GetMillisecond", GetMillisecond, true);
			LuaObject::addMethod(L, "GetMinute", GetMinute, true);
			LuaObject::addMethod(L, "GetMonth", GetMonth, true);
			LuaObject::addMethod(L, "GetMonthOfYear", GetMonthOfYear, true);
			LuaObject::addMethod(L, "GetSecond", GetSecond, true);
			LuaObject::addMethod(L, "GetTicks", GetTicks, true);
			LuaObject::addMethod(L, "GetYear", GetYear, true);
			LuaObject::addMethod(L, "IsAfternoon", IsAfternoon, true);
			LuaObject::addMethod(L, "IsMorning", IsMorning, true);
			LuaObject::addMethod(L, "ToHttpDate", ToHttpDate, true);
			LuaObject::addMethod(L, "ToUnixTimestamp", ToUnixTimestamp, true);
			LuaObject::addMethod(L, "DaysInMonth", DaysInMonth, false);
			LuaObject::addMethod(L, "DaysInYear", DaysInYear, false);
			LuaObject::addMethod(L, "FromJulianDay", FromJulianDay, false);
			LuaObject::addMethod(L, "FromUnixTimestamp", FromUnixTimestamp, false);
			LuaObject::addMethod(L, "IsLeapYear", IsLeapYear, false);
			LuaObject::addMethod(L, "MaxValue", MaxValue, false);
			LuaObject::addMethod(L, "MinValue", MinValue, false);
			LuaObject::addMethod(L, "Now", Now, false);
			LuaObject::addMethod(L, "Parse", Parse, false);
			LuaObject::addMethod(L, "ParseHttpDate", ParseHttpDate, false);
			LuaObject::addMethod(L, "Today", Today, false);
			LuaObject::addMethod(L, "UtcNow", UtcNow, false);
			LuaObject::addMethod(L, "Validate", Validate, false);
			LuaObject::finishType(L, "FDateTime", __ctor, __gc);
		}

	};

	int LuaWrapper::pushValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms) {
		auto vptr = _pushStructMap.Find(uss);
		if (vptr != nullptr) {
			(*vptr)(L, p, parms);
			return 1;
		} else {
			return 0;
		}
	}

	int LuaWrapper::checkValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms, int i) {
		auto vptr = _checkStructMap.Find(uss);
		if (vptr != nullptr) {
			(*vptr)(L, p, parms, i);
			return 1;
		} else {
			return 0;
		}
	}

	void LuaWrapper::init(lua_State* L) {
		AutoStack autoStack(L);
		FRotatorStruct = TBaseStructure<FRotator>::Get();
		_pushStructMap.Add(FRotatorStruct, __pushFRotator);
		_checkStructMap.Add(FRotatorStruct, __checkFRotator);
		FRotatorWrapper::bind(L);

		FTransformStruct = TBaseStructure<FTransform>::Get();
		_pushStructMap.Add(FTransformStruct, __pushFTransform);
		_checkStructMap.Add(FTransformStruct, __checkFTransform);
		FTransformWrapper::bind(L);

		FLinearColorStruct = TBaseStructure<FLinearColor>::Get();
		_pushStructMap.Add(FLinearColorStruct, __pushFLinearColor);
		_checkStructMap.Add(FLinearColorStruct, __checkFLinearColor);
		FLinearColorWrapper::bind(L);

		FColorStruct = TBaseStructure<FColor>::Get();
		_pushStructMap.Add(FColorStruct, __pushFColor);
		_checkStructMap.Add(FColorStruct, __checkFColor);
		FColorWrapper::bind(L);

		FVectorStruct = TBaseStructure<FVector>::Get();
		_pushStructMap.Add(FVectorStruct, __pushFVector);
		_checkStructMap.Add(FVectorStruct, __checkFVector);
		FVectorWrapper::bind(L);

		FVector2DStruct = TBaseStructure<FVector2D>::Get();
		_pushStructMap.Add(FVector2DStruct, __pushFVector2D);
		_checkStructMap.Add(FVector2DStruct, __checkFVector2D);
		FVector2DWrapper::bind(L);

		FRandomStreamStruct = TBaseStructure<FRandomStream>::Get();
		_pushStructMap.Add(FRandomStreamStruct, __pushFRandomStream);
		_checkStructMap.Add(FRandomStreamStruct, __checkFRandomStream);
		FRandomStreamWrapper::bind(L);

		FGuidStruct = TBaseStructure<FGuid>::Get();
		_pushStructMap.Add(FGuidStruct, __pushFGuid);
		_checkStructMap.Add(FGuidStruct, __checkFGuid);
		FGuidWrapper::bind(L);

		FBox2DStruct = TBaseStructure<FBox2D>::Get();
		_pushStructMap.Add(FBox2DStruct, __pushFBox2D);
		_checkStructMap.Add(FBox2DStruct, __checkFBox2D);
		FBox2DWrapper::bind(L);

		FFloatRangeBoundStruct = TBaseStructure<FFloatRangeBound>::Get();
		_pushStructMap.Add(FFloatRangeBoundStruct, __pushFFloatRangeBound);
		_checkStructMap.Add(FFloatRangeBoundStruct, __checkFFloatRangeBound);
		FFloatRangeBoundWrapper::bind(L);

		FFloatRangeStruct = TBaseStructure<FFloatRange>::Get();
		_pushStructMap.Add(FFloatRangeStruct, __pushFFloatRange);
		_checkStructMap.Add(FFloatRangeStruct, __checkFFloatRange);
		FFloatRangeWrapper::bind(L);

		FInt32RangeBoundStruct = TBaseStructure<FInt32RangeBound>::Get();
		_pushStructMap.Add(FInt32RangeBoundStruct, __pushFInt32RangeBound);
		_checkStructMap.Add(FInt32RangeBoundStruct, __checkFInt32RangeBound);
		FInt32RangeBoundWrapper::bind(L);

		FInt32RangeStruct = TBaseStructure<FInt32Range>::Get();
		_pushStructMap.Add(FInt32RangeStruct, __pushFInt32Range);
		_checkStructMap.Add(FInt32RangeStruct, __checkFInt32Range);
		FInt32RangeWrapper::bind(L);

		FFloatIntervalStruct = TBaseStructure<FFloatInterval>::Get();
		_pushStructMap.Add(FFloatIntervalStruct, __pushFFloatInterval);
		_checkStructMap.Add(FFloatIntervalStruct, __checkFFloatInterval);
		FFloatIntervalWrapper::bind(L);

		FInt32IntervalStruct = TBaseStructure<FInt32Interval>::Get();
		_pushStructMap.Add(FInt32IntervalStruct, __pushFInt32Interval);
		_checkStructMap.Add(FInt32IntervalStruct, __checkFInt32Interval);
		FInt32IntervalWrapper::bind(L);

		FPrimaryAssetTypeStruct = TBaseStructure<FPrimaryAssetType>::Get();
		_pushStructMap.Add(FPrimaryAssetTypeStruct, __pushFPrimaryAssetType);
		_checkStructMap.Add(FPrimaryAssetTypeStruct, __checkFPrimaryAssetType);
		FPrimaryAssetTypeWrapper::bind(L);

		FPrimaryAssetIdStruct = TBaseStructure<FPrimaryAssetId>::Get();
		_pushStructMap.Add(FPrimaryAssetIdStruct, __pushFPrimaryAssetId);
		_checkStructMap.Add(FPrimaryAssetIdStruct, __checkFPrimaryAssetId);
		FPrimaryAssetIdWrapper::bind(L);

#if (ENGINE_MINOR_VERSION>=21) && (ENGINE_MAJOR_VERSION>=4)
		FDateTimeStruct = TBaseStructure<FDateTime>::Get();
		_pushStructMap.Add(FDateTimeStruct, __pushFDateTime);
		_checkStructMap.Add(FDateTimeStruct, __checkFDateTime);
		FDateTimeWrapper::bind(L);
#endif
	}

}
