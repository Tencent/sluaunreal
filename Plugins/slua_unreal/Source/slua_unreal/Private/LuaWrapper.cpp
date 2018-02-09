#include "LuaWrapper.h"

namespace slua {

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

	static inline FRotator* __newFRotator() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FRotator"));
#endif
		return new FRotator();
	}

	static inline FTransform* __newFTransform() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FTransform"));
#endif
		return new FTransform();
	}

	static inline FLinearColor* __newFLinearColor() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FLinearColor"));
#endif
		return new FLinearColor();
	}

	static inline FColor* __newFColor() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FColor"));
#endif
		return new FColor();
	}

	static inline FVector* __newFVector() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FVector"));
#endif
		return new FVector();
	}

	static inline FVector2D* __newFVector2D() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FVector2D"));
#endif
		return new FVector2D();
	}

	static inline FRandomStream* __newFRandomStream() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FRandomStream"));
#endif
		return new FRandomStream();
	}

	static inline FGuid* __newFGuid() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FGuid"));
#endif
		return new FGuid();
	}

	static inline FBox2D* __newFBox2D() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FBox2D"));
#endif
		return new FBox2D();
	}

	static inline FFloatRangeBound* __newFFloatRangeBound() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FFloatRangeBound"));
#endif
		return new FFloatRangeBound();
	}

	static inline FFloatRange* __newFFloatRange() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FFloatRange"));
#endif
		return new FFloatRange();
	}

	static inline FInt32RangeBound* __newFInt32RangeBound() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FInt32RangeBound"));
#endif
		return new FInt32RangeBound();
	}

	static inline FInt32Range* __newFInt32Range() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FInt32Range"));
#endif
		return new FInt32Range();
	}

	static inline FFloatInterval* __newFFloatInterval() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FFloatInterval"));
#endif
		return new FFloatInterval();
	}

	static inline FInt32Interval* __newFInt32Interval() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FInt32Interval"));
#endif
		return new FInt32Interval();
	}

	static inline FPrimaryAssetType* __newFPrimaryAssetType() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FPrimaryAssetType"));
#endif
		return new FPrimaryAssetType();
	}

	static inline FPrimaryAssetId* __newFPrimaryAssetId() {
#if defined(LUA_WRAPPER_DEBUG)
		Log::Log(TEXT("new FPrimaryAssetId"));
#endif
		return new FPrimaryAssetId();
	}

	struct FRotatorWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FRotator"));
#endif
				auto self = new FRotator();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FRotator"));
#endif
				auto InF = LuaObject::checkValue<float>(L, 2);
				auto self = new FRotator((float)InF);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 4) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FRotator"));
#endif
				auto InPitch = LuaObject::checkValue<float>(L, 2);
				auto InYaw = LuaObject::checkValue<float>(L, 3);
				auto InRoll = LuaObject::checkValue<float>(L, 4);
				auto self = new FRotator((float)InPitch, (float)InYaw, (float)InRoll);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FRotator() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FRotator"));
#endif
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			delete self;
			return 0;
		}

		static int get_Pitch(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			LuaObject::push(L, self->Pitch);
			return 1;
		}

		static int set_Pitch(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->Pitch = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_Yaw(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			LuaObject::push(L, self->Yaw);
			return 1;
		}

		static int set_Yaw(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->Yaw = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_Roll(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			LuaObject::push(L, self->Roll);
			return 1;
		}

		static int set_Roll(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->Roll = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_ZeroRotator(lua_State* L) {
			LuaObject::pushStatic(L, &FRotator::ZeroRotator);
			return 1;
		}

		static int DiagnosticCheckNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				self->DiagnosticCheckNaN();
				return 0;
			} else if (argc == 2) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto Message = LuaObject::checkValue<const char*>(L, 2);
				self->DiagnosticCheckNaN(UTF8_TO_TCHAR(Message));
				return 0;
			} else {
				luaL_error(L, "call FRotator::DiagnosticCheckNaN error, argc=%d", argc);
				return 0;
			}
		}

		static int IsNearlyZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsNearlyZero((float)Tolerance);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::IsNearlyZero error, argc=%d", argc);
				return 0;
			}
		}

		static int IsZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = self->IsZero();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::IsZero error, argc=%d", argc);
				return 0;
			}
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto R = LuaObject::checkValue<FRotator*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(*R, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, R);
				return 2;
			} else {
				luaL_error(L, "call FRotator::Equals error, argc=%d", argc);
				return 0;
			}
		}

		static int Add(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto DeltaPitch = LuaObject::checkValue<float>(L, 2);
				auto DeltaYaw = LuaObject::checkValue<float>(L, 3);
				auto DeltaRoll = LuaObject::checkValue<float>(L, 4);
				auto ret = __newFRotator();
				*ret = self->Add((float)DeltaPitch, (float)DeltaYaw, (float)DeltaRoll);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::Add error, argc=%d", argc);
				return 0;
			}
		}

		static int GetInverse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = __newFRotator();
				*ret = self->GetInverse();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::GetInverse error, argc=%d", argc);
				return 0;
			}
		}

		static int GridSnap(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto RotGrid = LuaObject::checkValue<FRotator*>(L, 2);
				auto ret = __newFRotator();
				*ret = self->GridSnap(*RotGrid);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, RotGrid);
				return 2;
			} else {
				luaL_error(L, "call FRotator::GridSnap error, argc=%d", argc);
				return 0;
			}
		}

		static int Vector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = __newFVector();
				*ret = self->Vector();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::Vector error, argc=%d", argc);
				return 0;
			}
		}

		static int Euler(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = __newFVector();
				*ret = self->Euler();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::Euler error, argc=%d", argc);
				return 0;
			}
		}

		static int RotateVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->RotateVector(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FRotator::RotateVector error, argc=%d", argc);
				return 0;
			}
		}

		static int UnrotateVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->UnrotateVector(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FRotator::UnrotateVector error, argc=%d", argc);
				return 0;
			}
		}

		static int Clamp(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = __newFRotator();
				*ret = self->Clamp();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::Clamp error, argc=%d", argc);
				return 0;
			}
		}

		static int GetNormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = __newFRotator();
				*ret = self->GetNormalized();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::GetNormalized error, argc=%d", argc);
				return 0;
			}
		}

		static int GetDenormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = __newFRotator();
				*ret = self->GetDenormalized();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::GetDenormalized error, argc=%d", argc);
				return 0;
			}
		}

		static int GetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto ret = self->GetComponentForAxis((EAxis::Type)Axis);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::GetComponentForAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int SetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto Component = LuaObject::checkValue<float>(L, 3);
				self->SetComponentForAxis((EAxis::Type)Axis, (float)Component);
				return 0;
			} else {
				luaL_error(L, "call FRotator::SetComponentForAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int Normalize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				self->Normalize();
				return 0;
			} else {
				luaL_error(L, "call FRotator::Normalize error, argc=%d", argc);
				return 0;
			}
		}

		static int GetWindingAndRemainder(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto Winding = LuaObject::checkValue<FRotator*>(L, 2);
				auto Remainder = LuaObject::checkValue<FRotator*>(L, 3);
				self->GetWindingAndRemainder(*Winding, *Remainder);
				LuaObject::pushValue(L, Winding);
				LuaObject::pushValue(L, Remainder);
				return 2;
			} else {
				luaL_error(L, "call FRotator::GetWindingAndRemainder error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int ToCompactString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = self->ToCompactString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::ToCompactString error, argc=%d", argc);
				return 0;
			}
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				LuaObject::push(L, InSourceString);
				return 2;
			} else {
				luaL_error(L, "call FRotator::InitFromString error, argc=%d", argc);
				return 0;
			}
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRotator*>(L, 1);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::ContainsNaN error, argc=%d", argc);
				return 0;
			}
		}

		static int ClampAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Angle = LuaObject::checkValue<float>(L, 2);
				auto ret = FRotator::ClampAxis((float)Angle);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::ClampAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int NormalizeAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Angle = LuaObject::checkValue<float>(L, 2);
				auto ret = FRotator::NormalizeAxis((float)Angle);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::NormalizeAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int CompressAxisToByte(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Angle = LuaObject::checkValue<float>(L, 2);
				auto ret = FRotator::CompressAxisToByte((float)Angle);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::CompressAxisToByte error, argc=%d", argc);
				return 0;
			}
		}

		static int DecompressAxisFromByte(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Angle = LuaObject::checkValue<int>(L, 2);
				auto ret = FRotator::DecompressAxisFromByte((unsigned short)Angle);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::DecompressAxisFromByte error, argc=%d", argc);
				return 0;
			}
		}

		static int CompressAxisToShort(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Angle = LuaObject::checkValue<float>(L, 2);
				auto ret = FRotator::CompressAxisToShort((float)Angle);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::CompressAxisToShort error, argc=%d", argc);
				return 0;
			}
		}

		static int DecompressAxisFromShort(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Angle = LuaObject::checkValue<int>(L, 2);
				auto ret = FRotator::DecompressAxisFromShort((unsigned short)Angle);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRotator::DecompressAxisFromShort error, argc=%d", argc);
				return 0;
			}
		}

		static int MakeFromEuler(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Euler = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFRotator();
				*ret = FRotator::MakeFromEuler(*Euler);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Euler);
				return 2;
			} else {
				luaL_error(L, "call FRotator::MakeFromEuler error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FRotator>("FRotator");
			LuaObject::newType(L, "FRotator");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FTransform"));
#endif
				auto self = new FTransform();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FTransform"));
#endif
				auto InTranslation = LuaObject::checkValue<FVector*>(L, 2);
				auto self = new FTransform(*InTranslation);
				LuaObject::pushValue(L, InTranslation);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 4) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FTransform"));
#endif
				auto InRotation = LuaObject::checkValue<FRotator*>(L, 2);
				auto InTranslation = LuaObject::checkValue<FVector*>(L, 3);
				auto InScale3D = LuaObject::checkValue<FVector*>(L, 4);
				auto self = new FTransform(*InRotation, *InTranslation, *InScale3D);
				LuaObject::pushValue(L, InRotation);
				LuaObject::pushValue(L, InTranslation);
				LuaObject::pushValue(L, InScale3D);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 5) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FTransform"));
#endif
				auto InX = LuaObject::checkValue<FVector*>(L, 2);
				auto InY = LuaObject::checkValue<FVector*>(L, 3);
				auto InZ = LuaObject::checkValue<FVector*>(L, 4);
				auto InTranslation = LuaObject::checkValue<FVector*>(L, 5);
				auto self = new FTransform(*InX, *InY, *InZ, *InTranslation);
				LuaObject::pushValue(L, InX);
				LuaObject::pushValue(L, InY);
				LuaObject::pushValue(L, InZ);
				LuaObject::pushValue(L, InTranslation);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FTransform() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FTransform"));
#endif
			auto self = LuaObject::checkValue<FTransform*>(L, 1);
			delete self;
			return 0;
		}

		static int get_Identity(lua_State* L) {
			LuaObject::pushStatic(L, &FTransform::Identity);
			return 1;
		}

		static int DiagnosticCheckNaN_Translate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->DiagnosticCheckNaN_Translate();
				return 0;
			} else {
				luaL_error(L, "call FTransform::DiagnosticCheckNaN_Translate error, argc=%d", argc);
				return 0;
			}
		}

		static int DiagnosticCheckNaN_Rotate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->DiagnosticCheckNaN_Rotate();
				return 0;
			} else {
				luaL_error(L, "call FTransform::DiagnosticCheckNaN_Rotate error, argc=%d", argc);
				return 0;
			}
		}

		static int DiagnosticCheckNaN_Scale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->DiagnosticCheckNaN_Scale3D();
				return 0;
			} else {
				luaL_error(L, "call FTransform::DiagnosticCheckNaN_Scale3D error, argc=%d", argc);
				return 0;
			}
		}

		static int DiagnosticCheckNaN_All(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->DiagnosticCheckNaN_All();
				return 0;
			} else {
				luaL_error(L, "call FTransform::DiagnosticCheckNaN_All error, argc=%d", argc);
				return 0;
			}
		}

		static int DiagnosticCheck_IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->DiagnosticCheck_IsValid();
				return 0;
			} else {
				luaL_error(L, "call FTransform::DiagnosticCheck_IsValid error, argc=%d", argc);
				return 0;
			}
		}

		static int DebugPrint(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->DebugPrint();
				return 0;
			} else {
				luaL_error(L, "call FTransform::DebugPrint error, argc=%d", argc);
				return 0;
			}
		}

		static int ToHumanReadableString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->ToHumanReadableString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::ToHumanReadableString error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				LuaObject::push(L, InSourceString);
				return 2;
			} else {
				luaL_error(L, "call FTransform::InitFromString error, argc=%d", argc);
				return 0;
			}
		}

		static int Inverse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = __newFTransform();
				*ret = self->Inverse();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::Inverse error, argc=%d", argc);
				return 0;
			}
		}

		static int Blend(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Atom1 = LuaObject::checkValue<FTransform*>(L, 2);
				auto Atom2 = LuaObject::checkValue<FTransform*>(L, 3);
				auto Alpha = LuaObject::checkValue<float>(L, 4);
				self->Blend(*Atom1, *Atom2, (float)Alpha);
				LuaObject::pushValue(L, Atom1);
				LuaObject::pushValue(L, Atom2);
				return 2;
			} else {
				luaL_error(L, "call FTransform::Blend error, argc=%d", argc);
				return 0;
			}
		}

		static int BlendWith(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto OtherAtom = LuaObject::checkValue<FTransform*>(L, 2);
				auto Alpha = LuaObject::checkValue<float>(L, 3);
				self->BlendWith(*OtherAtom, (float)Alpha);
				LuaObject::pushValue(L, OtherAtom);
				return 1;
			} else {
				luaL_error(L, "call FTransform::BlendWith error, argc=%d", argc);
				return 0;
			}
		}

		static int ScaleTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto InScale3D = LuaObject::checkValue<FVector*>(L, 2);
				self->ScaleTranslation(*InScale3D);
				LuaObject::pushValue(L, InScale3D);
				return 1;
			} else {
				luaL_error(L, "call FTransform::ScaleTranslation error, argc=%d", argc);
				return 0;
			}
		}

		static int RemoveScaling(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				self->RemoveScaling((float)Tolerance);
				return 0;
			} else {
				luaL_error(L, "call FTransform::RemoveScaling error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMaximumAxisScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->GetMaximumAxisScale();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetMaximumAxisScale error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMinimumAxisScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->GetMinimumAxisScale();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetMinimumAxisScale error, argc=%d", argc);
				return 0;
			}
		}

		static int GetRelativeTransform(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto ret = __newFTransform();
				*ret = self->GetRelativeTransform(*Other);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FTransform::GetRelativeTransform error, argc=%d", argc);
				return 0;
			}
		}

		static int GetRelativeTransformReverse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto ret = __newFTransform();
				*ret = self->GetRelativeTransformReverse(*Other);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FTransform::GetRelativeTransformReverse error, argc=%d", argc);
				return 0;
			}
		}

		static int SetToRelativeTransform(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ParentTransform = LuaObject::checkValue<FTransform*>(L, 2);
				self->SetToRelativeTransform(*ParentTransform);
				LuaObject::pushValue(L, ParentTransform);
				return 1;
			} else {
				luaL_error(L, "call FTransform::SetToRelativeTransform error, argc=%d", argc);
				return 0;
			}
		}

		static int TransformPosition(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->TransformPosition(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::TransformPosition error, argc=%d", argc);
				return 0;
			}
		}

		static int TransformPositionNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->TransformPositionNoScale(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::TransformPositionNoScale error, argc=%d", argc);
				return 0;
			}
		}

		static int InverseTransformPosition(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->InverseTransformPosition(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::InverseTransformPosition error, argc=%d", argc);
				return 0;
			}
		}

		static int InverseTransformPositionNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->InverseTransformPositionNoScale(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::InverseTransformPositionNoScale error, argc=%d", argc);
				return 0;
			}
		}

		static int TransformVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->TransformVector(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::TransformVector error, argc=%d", argc);
				return 0;
			}
		}

		static int TransformVectorNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->TransformVectorNoScale(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::TransformVectorNoScale error, argc=%d", argc);
				return 0;
			}
		}

		static int InverseTransformVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->InverseTransformVector(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::InverseTransformVector error, argc=%d", argc);
				return 0;
			}
		}

		static int InverseTransformVectorNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->InverseTransformVectorNoScale(*V);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FTransform::InverseTransformVectorNoScale error, argc=%d", argc);
				return 0;
			}
		}

		static int GetScaled(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Scale = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFTransform();
				*ret = self->GetScaled((float)Scale);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetScaled error, argc=%d", argc);
				return 0;
			}
		}

		static int GetScaledAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto InAxis = LuaObject::checkValue<int>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetScaledAxis((EAxis::Type)InAxis);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetScaledAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int GetUnitAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto InAxis = LuaObject::checkValue<int>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetUnitAxis((EAxis::Type)InAxis);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetUnitAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int Mirror(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto MirrorAxis = LuaObject::checkValue<int>(L, 2);
				auto FlipAxis = LuaObject::checkValue<int>(L, 3);
				self->Mirror((EAxis::Type)MirrorAxis, (EAxis::Type)FlipAxis);
				return 0;
			} else {
				luaL_error(L, "call FTransform::Mirror error, argc=%d", argc);
				return 0;
			}
		}

		static int GetLocation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = __newFVector();
				*ret = self->GetLocation();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetLocation error, argc=%d", argc);
				return 0;
			}
		}

		static int Rotator(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = __newFRotator();
				*ret = self->Rotator();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::Rotator error, argc=%d", argc);
				return 0;
			}
		}

		static int GetDeterminant(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->GetDeterminant();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetDeterminant error, argc=%d", argc);
				return 0;
			}
		}

		static int SetLocation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Origin = LuaObject::checkValue<FVector*>(L, 2);
				self->SetLocation(*Origin);
				LuaObject::pushValue(L, Origin);
				return 1;
			} else {
				luaL_error(L, "call FTransform::SetLocation error, argc=%d", argc);
				return 0;
			}
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::ContainsNaN error, argc=%d", argc);
				return 0;
			}
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::IsValid error, argc=%d", argc);
				return 0;
			}
		}

		static int RotationEquals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->RotationEquals(*Other, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FTransform::RotationEquals error, argc=%d", argc);
				return 0;
			}
		}

		static int TranslationEquals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->TranslationEquals(*Other, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FTransform::TranslationEquals error, argc=%d", argc);
				return 0;
			}
		}

		static int Scale3DEquals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Scale3DEquals(*Other, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FTransform::Scale3DEquals error, argc=%d", argc);
				return 0;
			}
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(*Other, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FTransform::Equals error, argc=%d", argc);
				return 0;
			}
		}

		static int EqualsNoScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->EqualsNoScale(*Other, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FTransform::EqualsNoScale error, argc=%d", argc);
				return 0;
			}
		}

		static int SetIdentity(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->SetIdentity();
				return 0;
			} else {
				luaL_error(L, "call FTransform::SetIdentity error, argc=%d", argc);
				return 0;
			}
		}

		static int MultiplyScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Scale3DMultiplier = LuaObject::checkValue<FVector*>(L, 2);
				self->MultiplyScale3D(*Scale3DMultiplier);
				LuaObject::pushValue(L, Scale3DMultiplier);
				return 1;
			} else {
				luaL_error(L, "call FTransform::MultiplyScale3D error, argc=%d", argc);
				return 0;
			}
		}

		static int SetTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto NewTranslation = LuaObject::checkValue<FVector*>(L, 2);
				self->SetTranslation(*NewTranslation);
				LuaObject::pushValue(L, NewTranslation);
				return 1;
			} else {
				luaL_error(L, "call FTransform::SetTranslation error, argc=%d", argc);
				return 0;
			}
		}

		static int CopyTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				self->CopyTranslation(*Other);
				LuaObject::pushValue(L, Other);
				return 1;
			} else {
				luaL_error(L, "call FTransform::CopyTranslation error, argc=%d", argc);
				return 0;
			}
		}

		static int AddToTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto DeltaTranslation = LuaObject::checkValue<FVector*>(L, 2);
				self->AddToTranslation(*DeltaTranslation);
				LuaObject::pushValue(L, DeltaTranslation);
				return 1;
			} else {
				luaL_error(L, "call FTransform::AddToTranslation error, argc=%d", argc);
				return 0;
			}
		}

		static int CopyRotation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				self->CopyRotation(*Other);
				LuaObject::pushValue(L, Other);
				return 1;
			} else {
				luaL_error(L, "call FTransform::CopyRotation error, argc=%d", argc);
				return 0;
			}
		}

		static int SetScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto NewScale3D = LuaObject::checkValue<FVector*>(L, 2);
				self->SetScale3D(*NewScale3D);
				LuaObject::pushValue(L, NewScale3D);
				return 1;
			} else {
				luaL_error(L, "call FTransform::SetScale3D error, argc=%d", argc);
				return 0;
			}
		}

		static int CopyScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto Other = LuaObject::checkValue<FTransform*>(L, 2);
				self->CopyScale3D(*Other);
				LuaObject::pushValue(L, Other);
				return 1;
			} else {
				luaL_error(L, "call FTransform::CopyScale3D error, argc=%d", argc);
				return 0;
			}
		}

		static int SetTranslationAndScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto NewTranslation = LuaObject::checkValue<FVector*>(L, 2);
				auto NewScale3D = LuaObject::checkValue<FVector*>(L, 3);
				self->SetTranslationAndScale3D(*NewTranslation, *NewScale3D);
				LuaObject::pushValue(L, NewTranslation);
				LuaObject::pushValue(L, NewScale3D);
				return 2;
			} else {
				luaL_error(L, "call FTransform::SetTranslationAndScale3D error, argc=%d", argc);
				return 0;
			}
		}

		static int NormalizeRotation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				self->NormalizeRotation();
				return 0;
			} else {
				luaL_error(L, "call FTransform::NormalizeRotation error, argc=%d", argc);
				return 0;
			}
		}

		static int IsRotationNormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = self->IsRotationNormalized();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::IsRotationNormalized error, argc=%d", argc);
				return 0;
			}
		}

		static int GetTranslation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = __newFVector();
				*ret = self->GetTranslation();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetTranslation error, argc=%d", argc);
				return 0;
			}
		}

		static int GetScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto ret = __newFVector();
				*ret = self->GetScale3D();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FTransform::GetScale3D error, argc=%d", argc);
				return 0;
			}
		}

		static int CopyRotationPart(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto SrcBA = LuaObject::checkValue<FTransform*>(L, 2);
				self->CopyRotationPart(*SrcBA);
				LuaObject::pushValue(L, SrcBA);
				return 1;
			} else {
				luaL_error(L, "call FTransform::CopyRotationPart error, argc=%d", argc);
				return 0;
			}
		}

		static int CopyTranslationAndScale3D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FTransform*>(L, 1);
				auto SrcBA = LuaObject::checkValue<FTransform*>(L, 2);
				self->CopyTranslationAndScale3D(*SrcBA);
				LuaObject::pushValue(L, SrcBA);
				return 1;
			} else {
				luaL_error(L, "call FTransform::CopyTranslationAndScale3D error, argc=%d", argc);
				return 0;
			}
		}

		static int AnyHasNegativeScale(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto InScale3D = LuaObject::checkValue<FVector*>(L, 2);
				auto InOtherScale3D = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FTransform::AnyHasNegativeScale(*InScale3D, *InOtherScale3D);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, InScale3D);
				LuaObject::pushValue(L, InOtherScale3D);
				return 3;
			} else {
				luaL_error(L, "call FTransform::AnyHasNegativeScale error, argc=%d", argc);
				return 0;
			}
		}

		static int GetSafeScaleReciprocal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto InScale = LuaObject::checkValue<FVector*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector();
				*ret = FTransform::GetSafeScaleReciprocal(*InScale, (float)Tolerance);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, InScale);
				return 2;
			} else {
				luaL_error(L, "call FTransform::GetSafeScaleReciprocal error, argc=%d", argc);
				return 0;
			}
		}

		static int AreRotationsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto A = LuaObject::checkValue<FTransform*>(L, 2);
				auto B = LuaObject::checkValue<FTransform*>(L, 3);
				auto Tolerance = LuaObject::checkValue<float>(L, 4);
				auto ret = FTransform::AreRotationsEqual(*A, *B, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FTransform::AreRotationsEqual error, argc=%d", argc);
				return 0;
			}
		}

		static int AreTranslationsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto A = LuaObject::checkValue<FTransform*>(L, 2);
				auto B = LuaObject::checkValue<FTransform*>(L, 3);
				auto Tolerance = LuaObject::checkValue<float>(L, 4);
				auto ret = FTransform::AreTranslationsEqual(*A, *B, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FTransform::AreTranslationsEqual error, argc=%d", argc);
				return 0;
			}
		}

		static int AreScale3DsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto A = LuaObject::checkValue<FTransform*>(L, 2);
				auto B = LuaObject::checkValue<FTransform*>(L, 3);
				auto Tolerance = LuaObject::checkValue<float>(L, 4);
				auto ret = FTransform::AreScale3DsEqual(*A, *B, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FTransform::AreScale3DsEqual error, argc=%d", argc);
				return 0;
			}
		}

		static int AddTranslations(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FTransform*>(L, 2);
				auto B = LuaObject::checkValue<FTransform*>(L, 3);
				auto ret = __newFVector();
				*ret = FTransform::AddTranslations(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FTransform::AddTranslations error, argc=%d", argc);
				return 0;
			}
		}

		static int SubtractTranslations(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FTransform*>(L, 2);
				auto B = LuaObject::checkValue<FTransform*>(L, 3);
				auto ret = __newFVector();
				*ret = FTransform::SubtractTranslations(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FTransform::SubtractTranslations error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FTransform>("FTransform");
			LuaObject::newType(L, "FTransform");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FLinearColor"));
#endif
				auto self = new FLinearColor();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FLinearColor"));
#endif
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto self = new FLinearColor((EForceInit)_a0);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 5) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FLinearColor"));
#endif
				auto InR = LuaObject::checkValue<float>(L, 2);
				auto InG = LuaObject::checkValue<float>(L, 3);
				auto InB = LuaObject::checkValue<float>(L, 4);
				auto InA = LuaObject::checkValue<float>(L, 5);
				auto self = new FLinearColor((float)InR, (float)InG, (float)InB, (float)InA);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FLinearColor"));
#endif
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			delete self;
			return 0;
		}

		static int get_R(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			LuaObject::push(L, self->R);
			return 1;
		}

		static int set_R(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->R = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_G(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			LuaObject::push(L, self->G);
			return 1;
		}

		static int set_G(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->G = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_B(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			LuaObject::push(L, self->B);
			return 1;
		}

		static int set_B(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->B = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_A(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			LuaObject::push(L, self->A);
			return 1;
		}

		static int set_A(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->A = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_White(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::White);
			return 1;
		}

		static int get_Gray(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::Gray);
			return 1;
		}

		static int get_Black(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::Black);
			return 1;
		}

		static int get_Transparent(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::Transparent);
			return 1;
		}

		static int get_Red(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::Red);
			return 1;
		}

		static int get_Green(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::Green);
			return 1;
		}

		static int get_Blue(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::Blue);
			return 1;
		}

		static int get_Yellow(lua_State* L) {
			LuaObject::pushStatic(L, &FLinearColor::Yellow);
			return 1;
		}

		static int ToRGBE(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = __newFColor();
				*ret = self->ToRGBE();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::ToRGBE error, argc=%d", argc);
				return 0;
			}
		}

		static int Component(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto Index = LuaObject::checkValue<int>(L, 2);
				auto ret = self->Component((int)Index);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::Component error, argc=%d", argc);
				return 0;
			}
		}

		static int GetClamped(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto InMin = LuaObject::checkValue<float>(L, 2);
				auto InMax = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFLinearColor();
				*ret = self->GetClamped((float)InMin, (float)InMax);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::GetClamped error, argc=%d", argc);
				return 0;
			}
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(*ColorB, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, ColorB);
				return 2;
			} else {
				luaL_error(L, "call FLinearColor::Equals error, argc=%d", argc);
				return 0;
			}
		}

		static int CopyWithNewOpacity(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto NewOpacicty = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFLinearColor();
				*ret = self->CopyWithNewOpacity((float)NewOpacicty);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::CopyWithNewOpacity error, argc=%d", argc);
				return 0;
			}
		}

		static int LinearRGBToHSV(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = __newFLinearColor();
				*ret = self->LinearRGBToHSV();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::LinearRGBToHSV error, argc=%d", argc);
				return 0;
			}
		}

		static int HSVToLinearRGB(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = __newFLinearColor();
				*ret = self->HSVToLinearRGB();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::HSVToLinearRGB error, argc=%d", argc);
				return 0;
			}
		}

		static int Quantize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = __newFColor();
				*ret = self->Quantize();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::Quantize error, argc=%d", argc);
				return 0;
			}
		}

		static int QuantizeRound(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = __newFColor();
				*ret = self->QuantizeRound();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::QuantizeRound error, argc=%d", argc);
				return 0;
			}
		}

		static int ToFColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto bSRGB = LuaObject::checkValue<bool>(L, 2);
				auto ret = __newFColor();
				*ret = self->ToFColor((const bool)bSRGB);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::ToFColor error, argc=%d", argc);
				return 0;
			}
		}

		static int Desaturate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto Desaturation = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFLinearColor();
				*ret = self->Desaturate((float)Desaturation);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::Desaturate error, argc=%d", argc);
				return 0;
			}
		}

		static int ComputeLuminance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = self->ComputeLuminance();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::ComputeLuminance error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = self->GetMax();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::GetMax error, argc=%d", argc);
				return 0;
			}
		}

		static int IsAlmostBlack(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = self->IsAlmostBlack();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::IsAlmostBlack error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = self->GetMin();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::GetMin error, argc=%d", argc);
				return 0;
			}
		}

		static int GetLuminance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = self->GetLuminance();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::GetLuminance error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				LuaObject::push(L, InSourceString);
				return 2;
			} else {
				luaL_error(L, "call FLinearColor::InitFromString error, argc=%d", argc);
				return 0;
			}
		}

		static int FromSRGBColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Color = LuaObject::checkValue<FColor*>(L, 2);
				auto ret = __newFLinearColor();
				*ret = FLinearColor::FromSRGBColor(*Color);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Color);
				return 2;
			} else {
				luaL_error(L, "call FLinearColor::FromSRGBColor error, argc=%d", argc);
				return 0;
			}
		}

		static int FromPow22Color(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Color = LuaObject::checkValue<FColor*>(L, 2);
				auto ret = __newFLinearColor();
				*ret = FLinearColor::FromPow22Color(*Color);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Color);
				return 2;
			} else {
				luaL_error(L, "call FLinearColor::FromPow22Color error, argc=%d", argc);
				return 0;
			}
		}

		static int FGetHSV(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto H = LuaObject::checkValue<int>(L, 2);
				auto S = LuaObject::checkValue<int>(L, 3);
				auto V = LuaObject::checkValue<int>(L, 4);
				auto ret = __newFLinearColor();
				*ret = FLinearColor::FGetHSV((unsigned char)H, (unsigned char)S, (unsigned char)V);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::FGetHSV error, argc=%d", argc);
				return 0;
			}
		}

		static int MakeRandomColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFLinearColor();
				*ret = FLinearColor::MakeRandomColor();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::MakeRandomColor error, argc=%d", argc);
				return 0;
			}
		}

		static int MakeFromColorTemperature(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Temp = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFLinearColor();
				*ret = FLinearColor::MakeFromColorTemperature((float)Temp);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FLinearColor::MakeFromColorTemperature error, argc=%d", argc);
				return 0;
			}
		}

		static int Dist(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto V2 = LuaObject::checkValue<FLinearColor*>(L, 3);
				auto ret = FLinearColor::Dist(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FLinearColor::Dist error, argc=%d", argc);
				return 0;
			}
		}

		static int LerpUsingHSV(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto From = LuaObject::checkValue<FLinearColor*>(L, 2);
				auto To = LuaObject::checkValue<FLinearColor*>(L, 3);
				auto Progress = LuaObject::checkValue<float>(L, 4);
				auto ret = __newFLinearColor();
				*ret = FLinearColor::LerpUsingHSV(*From, *To, (const float)Progress);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, From);
				LuaObject::pushValue(L, To);
				return 3;
			} else {
				luaL_error(L, "call FLinearColor::LerpUsingHSV error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FLinearColor>("FLinearColor");
			LuaObject::newType(L, "FLinearColor");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FColor"));
#endif
				auto self = new FColor();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FColor"));
#endif
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto self = new FColor((EForceInit)_a0);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 5) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FColor"));
#endif
				auto InR = LuaObject::checkValue<int>(L, 2);
				auto InG = LuaObject::checkValue<int>(L, 3);
				auto InB = LuaObject::checkValue<int>(L, 4);
				auto InA = LuaObject::checkValue<int>(L, 5);
				auto self = new FColor((unsigned char)InR, (unsigned char)InG, (unsigned char)InB, (unsigned char)InA);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FColor() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FColor"));
#endif
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			delete self;
			return 0;
		}

		static int get_White(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::White);
			return 1;
		}

		static int get_Black(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Black);
			return 1;
		}

		static int get_Transparent(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Transparent);
			return 1;
		}

		static int get_Red(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Red);
			return 1;
		}

		static int get_Green(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Green);
			return 1;
		}

		static int get_Blue(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Blue);
			return 1;
		}

		static int get_Yellow(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Yellow);
			return 1;
		}

		static int get_Cyan(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Cyan);
			return 1;
		}

		static int get_Magenta(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Magenta);
			return 1;
		}

		static int get_Orange(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Orange);
			return 1;
		}

		static int get_Purple(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Purple);
			return 1;
		}

		static int get_Turquoise(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Turquoise);
			return 1;
		}

		static int get_Silver(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Silver);
			return 1;
		}

		static int get_Emerald(lua_State* L) {
			LuaObject::pushStatic(L, &FColor::Emerald);
			return 1;
		}

		static int DWColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = self->DWColor();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::DWColor error, argc=%d", argc);
				return 0;
			}
		}

		static int FromRGBE(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = __newFLinearColor();
				*ret = self->FromRGBE();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::FromRGBE error, argc=%d", argc);
				return 0;
			}
		}

		static int WithAlpha(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto Alpha = LuaObject::checkValue<int>(L, 2);
				auto ret = __newFColor();
				*ret = self->WithAlpha((unsigned char)Alpha);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::WithAlpha error, argc=%d", argc);
				return 0;
			}
		}

		static int ReinterpretAsLinear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = __newFLinearColor();
				*ret = self->ReinterpretAsLinear();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::ReinterpretAsLinear error, argc=%d", argc);
				return 0;
			}
		}

		static int ToHex(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = self->ToHex();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::ToHex error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				LuaObject::push(L, InSourceString);
				return 2;
			} else {
				luaL_error(L, "call FColor::InitFromString error, argc=%d", argc);
				return 0;
			}
		}

		static int ToPackedARGB(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = self->ToPackedARGB();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::ToPackedARGB error, argc=%d", argc);
				return 0;
			}
		}

		static int ToPackedABGR(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = self->ToPackedABGR();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::ToPackedABGR error, argc=%d", argc);
				return 0;
			}
		}

		static int ToPackedRGBA(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = self->ToPackedRGBA();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::ToPackedRGBA error, argc=%d", argc);
				return 0;
			}
		}

		static int ToPackedBGRA(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FColor*>(L, 1);
				auto ret = self->ToPackedBGRA();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::ToPackedBGRA error, argc=%d", argc);
				return 0;
			}
		}

		static int FromHex(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto HexString = LuaObject::checkValue<FString>(L, 2);
				auto ret = __newFColor();
				*ret = FColor::FromHex(HexString);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, HexString);
				return 2;
			} else {
				luaL_error(L, "call FColor::FromHex error, argc=%d", argc);
				return 0;
			}
		}

		static int MakeRandomColor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFColor();
				*ret = FColor::MakeRandomColor();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::MakeRandomColor error, argc=%d", argc);
				return 0;
			}
		}

		static int MakeRedToGreenColorFromScalar(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Scalar = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFColor();
				*ret = FColor::MakeRedToGreenColorFromScalar((float)Scalar);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::MakeRedToGreenColorFromScalar error, argc=%d", argc);
				return 0;
			}
		}

		static int MakeFromColorTemperature(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Temp = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFColor();
				*ret = FColor::MakeFromColorTemperature((float)Temp);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FColor::MakeFromColorTemperature error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FColor>("FColor");
			LuaObject::newType(L, "FColor");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FVector"));
#endif
				auto self = new FVector();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FVector"));
#endif
				auto InF = LuaObject::checkValue<float>(L, 2);
				auto self = new FVector((float)InF);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 3) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FVector"));
#endif
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto InZ = LuaObject::checkValue<float>(L, 3);
				auto self = new FVector(*V, (float)InZ);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 4) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FVector"));
#endif
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				auto InZ = LuaObject::checkValue<float>(L, 4);
				auto self = new FVector((float)InX, (float)InY, (float)InZ);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FVector() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FVector"));
#endif
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			delete self;
			return 0;
		}

		static int get_X(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			LuaObject::push(L, self->X);
			return 1;
		}

		static int set_X(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->X = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_Y(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			LuaObject::push(L, self->Y);
			return 1;
		}

		static int set_Y(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->Y = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_Z(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			LuaObject::push(L, self->Z);
			return 1;
		}

		static int set_Z(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->Z = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_ZeroVector(lua_State* L) {
			LuaObject::pushStatic(L, &FVector::ZeroVector);
			return 1;
		}

		static int get_OneVector(lua_State* L) {
			LuaObject::pushStatic(L, &FVector::OneVector);
			return 1;
		}

		static int get_UpVector(lua_State* L) {
			LuaObject::pushStatic(L, &FVector::UpVector);
			return 1;
		}

		static int get_ForwardVector(lua_State* L) {
			LuaObject::pushStatic(L, &FVector::ForwardVector);
			return 1;
		}

		static int get_RightVector(lua_State* L) {
			LuaObject::pushStatic(L, &FVector::RightVector);
			return 1;
		}

		static int DiagnosticCheckNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				self->DiagnosticCheckNaN();
				return 0;
			} else if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Message = LuaObject::checkValue<const char*>(L, 2);
				self->DiagnosticCheckNaN(UTF8_TO_TCHAR(Message));
				return 0;
			} else {
				luaL_error(L, "call FVector::DiagnosticCheckNaN error, argc=%d", argc);
				return 0;
			}
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(*V, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FVector::Equals error, argc=%d", argc);
				return 0;
			}
		}

		static int AllComponentsEqual(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->AllComponentsEqual((float)Tolerance);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::AllComponentsEqual error, argc=%d", argc);
				return 0;
			}
		}

		static int Component(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Index = LuaObject::checkValue<int>(L, 2);
				auto ret = self->Component((int)Index);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::Component error, argc=%d", argc);
				return 0;
			}
		}

		static int GetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto ret = self->GetComponentForAxis((EAxis::Type)Axis);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetComponentForAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int SetComponentForAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Axis = LuaObject::checkValue<int>(L, 2);
				auto Component = LuaObject::checkValue<float>(L, 3);
				self->SetComponentForAxis((EAxis::Type)Axis, (float)Component);
				return 0;
			} else {
				luaL_error(L, "call FVector::SetComponentForAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int Set(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				auto InZ = LuaObject::checkValue<float>(L, 4);
				self->Set((float)InX, (float)InY, (float)InZ);
				return 0;
			} else {
				luaL_error(L, "call FVector::Set error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->GetMax();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetMax error, argc=%d", argc);
				return 0;
			}
		}

		static int GetAbsMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->GetAbsMax();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetAbsMax error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->GetMin();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetMin error, argc=%d", argc);
				return 0;
			}
		}

		static int GetAbsMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->GetAbsMin();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetAbsMin error, argc=%d", argc);
				return 0;
			}
		}

		static int ComponentMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Other = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->ComponentMin(*Other);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FVector::ComponentMin error, argc=%d", argc);
				return 0;
			}
		}

		static int ComponentMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Other = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->ComponentMax(*Other);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Other);
				return 2;
			} else {
				luaL_error(L, "call FVector::ComponentMax error, argc=%d", argc);
				return 0;
			}
		}

		static int GetAbs(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFVector();
				*ret = self->GetAbs();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetAbs error, argc=%d", argc);
				return 0;
			}
		}

		static int Size(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->Size();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::Size error, argc=%d", argc);
				return 0;
			}
		}

		static int SizeSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->SizeSquared();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::SizeSquared error, argc=%d", argc);
				return 0;
			}
		}

		static int Size2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->Size2D();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::Size2D error, argc=%d", argc);
				return 0;
			}
		}

		static int SizeSquared2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->SizeSquared2D();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::SizeSquared2D error, argc=%d", argc);
				return 0;
			}
		}

		static int IsNearlyZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsNearlyZero((float)Tolerance);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::IsNearlyZero error, argc=%d", argc);
				return 0;
			}
		}

		static int IsZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->IsZero();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::IsZero error, argc=%d", argc);
				return 0;
			}
		}

		static int Normalize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->Normalize((float)Tolerance);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::Normalize error, argc=%d", argc);
				return 0;
			}
		}

		static int IsNormalized(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->IsNormalized();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::IsNormalized error, argc=%d", argc);
				return 0;
			}
		}

		static int ToDirectionAndLength(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto OutDir = LuaObject::checkValue<FVector*>(L, 2);
				auto OutLength = LuaObject::checkValue<float>(L, 3);
				self->ToDirectionAndLength(*OutDir, (float)OutLength);
				LuaObject::pushValue(L, OutDir);
				LuaObject::push(L, OutLength);
				return 2;
			} else {
				luaL_error(L, "call FVector::ToDirectionAndLength error, argc=%d", argc);
				return 0;
			}
		}

		static int GetSignVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFVector();
				*ret = self->GetSignVector();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetSignVector error, argc=%d", argc);
				return 0;
			}
		}

		static int Projection(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFVector();
				*ret = self->Projection();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::Projection error, argc=%d", argc);
				return 0;
			}
		}

		static int GetUnsafeNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFVector();
				*ret = self->GetUnsafeNormal();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetUnsafeNormal error, argc=%d", argc);
				return 0;
			}
		}

		static int GridSnap(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto GridSz = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GridSnap((const float)GridSz);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, GridSz);
				return 2;
			} else {
				luaL_error(L, "call FVector::GridSnap error, argc=%d", argc);
				return 0;
			}
		}

		static int BoundToCube(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Radius = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->BoundToCube((float)Radius);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::BoundToCube error, argc=%d", argc);
				return 0;
			}
		}

		static int GetClampedToSize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Min = LuaObject::checkValue<float>(L, 2);
				auto Max = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector();
				*ret = self->GetClampedToSize((float)Min, (float)Max);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetClampedToSize error, argc=%d", argc);
				return 0;
			}
		}

		static int GetClampedToSize2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Min = LuaObject::checkValue<float>(L, 2);
				auto Max = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector();
				*ret = self->GetClampedToSize2D((float)Min, (float)Max);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetClampedToSize2D error, argc=%d", argc);
				return 0;
			}
		}

		static int GetClampedToMaxSize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto MaxSize = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetClampedToMaxSize((float)MaxSize);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetClampedToMaxSize error, argc=%d", argc);
				return 0;
			}
		}

		static int GetClampedToMaxSize2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto MaxSize = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetClampedToMaxSize2D((float)MaxSize);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetClampedToMaxSize2D error, argc=%d", argc);
				return 0;
			}
		}

		static int AddBounded(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto Radius = LuaObject::checkValue<float>(L, 3);
				self->AddBounded(*V, (float)Radius);
				LuaObject::pushValue(L, V);
				return 1;
			} else {
				luaL_error(L, "call FVector::AddBounded error, argc=%d", argc);
				return 0;
			}
		}

		static int Reciprocal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFVector();
				*ret = self->Reciprocal();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::Reciprocal error, argc=%d", argc);
				return 0;
			}
		}

		static int IsUniform(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsUniform((float)Tolerance);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::IsUniform error, argc=%d", argc);
				return 0;
			}
		}

		static int MirrorByVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto MirrorNormal = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->MirrorByVector(*MirrorNormal);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, MirrorNormal);
				return 2;
			} else {
				luaL_error(L, "call FVector::MirrorByVector error, argc=%d", argc);
				return 0;
			}
		}

		static int RotateAngleAxis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto AngleDeg = LuaObject::checkValue<float>(L, 2);
				auto Axis = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = __newFVector();
				*ret = self->RotateAngleAxis((const float)AngleDeg, *Axis);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Axis);
				return 2;
			} else {
				luaL_error(L, "call FVector::RotateAngleAxis error, argc=%d", argc);
				return 0;
			}
		}

		static int GetSafeNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetSafeNormal((float)Tolerance);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetSafeNormal error, argc=%d", argc);
				return 0;
			}
		}

		static int GetSafeNormal2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector();
				*ret = self->GetSafeNormal2D((float)Tolerance);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::GetSafeNormal2D error, argc=%d", argc);
				return 0;
			}
		}

		static int CosineAngle2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto B = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = self->CosineAngle2D(*B);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::CosineAngle2D error, argc=%d", argc);
				return 0;
			}
		}

		static int ProjectOnTo(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto A = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->ProjectOnTo(*A);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				return 2;
			} else {
				luaL_error(L, "call FVector::ProjectOnTo error, argc=%d", argc);
				return 0;
			}
		}

		static int ProjectOnToNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Normal = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = self->ProjectOnToNormal(*Normal);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Normal);
				return 2;
			} else {
				luaL_error(L, "call FVector::ProjectOnToNormal error, argc=%d", argc);
				return 0;
			}
		}

		static int ToOrientationRotator(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFRotator();
				*ret = self->ToOrientationRotator();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::ToOrientationRotator error, argc=%d", argc);
				return 0;
			}
		}

		static int Rotation(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFRotator();
				*ret = self->Rotation();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::Rotation error, argc=%d", argc);
				return 0;
			}
		}

		static int FindBestAxisVectors(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto Axis1 = LuaObject::checkValue<FVector*>(L, 2);
				auto Axis2 = LuaObject::checkValue<FVector*>(L, 3);
				self->FindBestAxisVectors(*Axis1, *Axis2);
				LuaObject::pushValue(L, Axis1);
				LuaObject::pushValue(L, Axis2);
				return 2;
			} else {
				luaL_error(L, "call FVector::FindBestAxisVectors error, argc=%d", argc);
				return 0;
			}
		}

		static int UnwindEuler(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				self->UnwindEuler();
				return 0;
			} else {
				luaL_error(L, "call FVector::UnwindEuler error, argc=%d", argc);
				return 0;
			}
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::ContainsNaN error, argc=%d", argc);
				return 0;
			}
		}

		static int IsUnit(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto LengthSquaredTolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsUnit((float)LengthSquaredTolerance);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::IsUnit error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int ToCompactString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->ToCompactString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::ToCompactString error, argc=%d", argc);
				return 0;
			}
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				LuaObject::push(L, InSourceString);
				return 2;
			} else {
				luaL_error(L, "call FVector::InitFromString error, argc=%d", argc);
				return 0;
			}
		}

		static int UnitCartesianToSpherical(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = __newFVector2D();
				*ret = self->UnitCartesianToSpherical();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::UnitCartesianToSpherical error, argc=%d", argc);
				return 0;
			}
		}

		static int HeadingAngle(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector*>(L, 1);
				auto ret = self->HeadingAngle();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector::HeadingAngle error, argc=%d", argc);
				return 0;
			}
		}

		static int CrossProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FVector*>(L, 2);
				auto B = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = __newFVector();
				*ret = FVector::CrossProduct(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FVector::CrossProduct error, argc=%d", argc);
				return 0;
			}
		}

		static int DotProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FVector*>(L, 2);
				auto B = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::DotProduct(*A, *B);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FVector::DotProduct error, argc=%d", argc);
				return 0;
			}
		}

		static int CreateOrthonormalBasis(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto XAxis = LuaObject::checkValue<FVector*>(L, 2);
				auto YAxis = LuaObject::checkValue<FVector*>(L, 3);
				auto ZAxis = LuaObject::checkValue<FVector*>(L, 4);
				FVector::CreateOrthonormalBasis(*XAxis, *YAxis, *ZAxis);
				LuaObject::pushValue(L, XAxis);
				LuaObject::pushValue(L, YAxis);
				LuaObject::pushValue(L, ZAxis);
				return 3;
			} else {
				luaL_error(L, "call FVector::CreateOrthonormalBasis error, argc=%d", argc);
				return 0;
			}
		}

		static int PointsAreSame(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto P = LuaObject::checkValue<FVector*>(L, 2);
				auto Q = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::PointsAreSame(*P, *Q);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, P);
				LuaObject::pushValue(L, Q);
				return 3;
			} else {
				luaL_error(L, "call FVector::PointsAreSame error, argc=%d", argc);
				return 0;
			}
		}

		static int PointsAreNear(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto Point1 = LuaObject::checkValue<FVector*>(L, 2);
				auto Point2 = LuaObject::checkValue<FVector*>(L, 3);
				auto Dist = LuaObject::checkValue<float>(L, 4);
				auto ret = FVector::PointsAreNear(*Point1, *Point2, (float)Dist);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Point1);
				LuaObject::pushValue(L, Point2);
				return 3;
			} else {
				luaL_error(L, "call FVector::PointsAreNear error, argc=%d", argc);
				return 0;
			}
		}

		static int PointPlaneDist(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto Point = LuaObject::checkValue<FVector*>(L, 2);
				auto PlaneBase = LuaObject::checkValue<FVector*>(L, 3);
				auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 4);
				auto ret = FVector::PointPlaneDist(*Point, *PlaneBase, *PlaneNormal);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Point);
				LuaObject::pushValue(L, PlaneBase);
				LuaObject::pushValue(L, PlaneNormal);
				return 4;
			} else {
				luaL_error(L, "call FVector::PointPlaneDist error, argc=%d", argc);
				return 0;
			}
		}

		static int PointPlaneProject(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto Point = LuaObject::checkValue<FVector*>(L, 2);
				auto PlaneBase = LuaObject::checkValue<FVector*>(L, 3);
				auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 4);
				auto ret = __newFVector();
				*ret = FVector::PointPlaneProject(*Point, *PlaneBase, *PlaneNormal);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Point);
				LuaObject::pushValue(L, PlaneBase);
				LuaObject::pushValue(L, PlaneNormal);
				return 4;
			} else if (argc == 5) {
				auto Point = LuaObject::checkValue<FVector*>(L, 2);
				auto A = LuaObject::checkValue<FVector*>(L, 3);
				auto B = LuaObject::checkValue<FVector*>(L, 4);
				auto C = LuaObject::checkValue<FVector*>(L, 5);
				auto ret = __newFVector();
				*ret = FVector::PointPlaneProject(*Point, *A, *B, *C);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Point);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				LuaObject::pushValue(L, C);
				return 5;
			} else {
				luaL_error(L, "call FVector::PointPlaneProject error, argc=%d", argc);
				return 0;
			}
		}

		static int VectorPlaneProject(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V = LuaObject::checkValue<FVector*>(L, 2);
				auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = __newFVector();
				*ret = FVector::VectorPlaneProject(*V, *PlaneNormal);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, V);
				LuaObject::pushValue(L, PlaneNormal);
				return 3;
			} else {
				luaL_error(L, "call FVector::VectorPlaneProject error, argc=%d", argc);
				return 0;
			}
		}

		static int Dist(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::Dist(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector::Dist error, argc=%d", argc);
				return 0;
			}
		}

		static int Distance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::Distance(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector::Distance error, argc=%d", argc);
				return 0;
			}
		}

		static int DistXY(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::DistXY(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector::DistXY error, argc=%d", argc);
				return 0;
			}
		}

		static int Dist2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::Dist2D(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector::Dist2D error, argc=%d", argc);
				return 0;
			}
		}

		static int DistSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::DistSquared(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector::DistSquared error, argc=%d", argc);
				return 0;
			}
		}

		static int DistSquaredXY(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::DistSquaredXY(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector::DistSquaredXY error, argc=%d", argc);
				return 0;
			}
		}

		static int DistSquared2D(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::DistSquared2D(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector::DistSquared2D error, argc=%d", argc);
				return 0;
			}
		}

		static int BoxPushOut(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto Normal = LuaObject::checkValue<FVector*>(L, 2);
				auto Size = LuaObject::checkValue<FVector*>(L, 3);
				auto ret = FVector::BoxPushOut(*Normal, *Size);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Normal);
				LuaObject::pushValue(L, Size);
				return 3;
			} else {
				luaL_error(L, "call FVector::BoxPushOut error, argc=%d", argc);
				return 0;
			}
		}

		static int Parallel(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 4);
				auto ret = FVector::Parallel(*Normal1, *Normal2, (float)ParallelCosineThreshold);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Normal1);
				LuaObject::pushValue(L, Normal2);
				return 3;
			} else {
				luaL_error(L, "call FVector::Parallel error, argc=%d", argc);
				return 0;
			}
		}

		static int Coincident(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 3);
				auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 4);
				auto ret = FVector::Coincident(*Normal1, *Normal2, (float)ParallelCosineThreshold);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Normal1);
				LuaObject::pushValue(L, Normal2);
				return 3;
			} else {
				luaL_error(L, "call FVector::Coincident error, argc=%d", argc);
				return 0;
			}
		}

		static int Orthogonal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 3);
				auto OrthogonalCosineThreshold = LuaObject::checkValue<float>(L, 4);
				auto ret = FVector::Orthogonal(*Normal1, *Normal2, (float)OrthogonalCosineThreshold);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Normal1);
				LuaObject::pushValue(L, Normal2);
				return 3;
			} else {
				luaL_error(L, "call FVector::Orthogonal error, argc=%d", argc);
				return 0;
			}
		}

		static int Coplanar(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 6) {
				auto Base1 = LuaObject::checkValue<FVector*>(L, 2);
				auto Normal1 = LuaObject::checkValue<FVector*>(L, 3);
				auto Base2 = LuaObject::checkValue<FVector*>(L, 4);
				auto Normal2 = LuaObject::checkValue<FVector*>(L, 5);
				auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 6);
				auto ret = FVector::Coplanar(*Base1, *Normal1, *Base2, *Normal2, (float)ParallelCosineThreshold);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Base1);
				LuaObject::pushValue(L, Normal1);
				LuaObject::pushValue(L, Base2);
				LuaObject::pushValue(L, Normal2);
				return 5;
			} else {
				luaL_error(L, "call FVector::Coplanar error, argc=%d", argc);
				return 0;
			}
		}

		static int Triple(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto X = LuaObject::checkValue<FVector*>(L, 2);
				auto Y = LuaObject::checkValue<FVector*>(L, 3);
				auto Z = LuaObject::checkValue<FVector*>(L, 4);
				auto ret = FVector::Triple(*X, *Y, *Z);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, X);
				LuaObject::pushValue(L, Y);
				LuaObject::pushValue(L, Z);
				return 4;
			} else {
				luaL_error(L, "call FVector::Triple error, argc=%d", argc);
				return 0;
			}
		}

		static int RadiansToDegrees(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto RadVector = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = FVector::RadiansToDegrees(*RadVector);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, RadVector);
				return 2;
			} else {
				luaL_error(L, "call FVector::RadiansToDegrees error, argc=%d", argc);
				return 0;
			}
		}

		static int DegreesToRadians(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto DegVector = LuaObject::checkValue<FVector*>(L, 2);
				auto ret = __newFVector();
				*ret = FVector::DegreesToRadians(*DegVector);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, DegVector);
				return 2;
			} else {
				luaL_error(L, "call FVector::DegreesToRadians error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FVector>("FVector");
			LuaObject::newType(L, "FVector");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FVector2D"));
#endif
				auto self = new FVector2D();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FVector2D"));
#endif
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto self = new FVector2D((EForceInit)_a0);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 3) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FVector2D"));
#endif
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				auto self = new FVector2D((float)InX, (float)InY);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FVector2D() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FVector2D"));
#endif
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			delete self;
			return 0;
		}

		static int get_X(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			LuaObject::push(L, self->X);
			return 1;
		}

		static int set_X(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->X = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_Y(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			LuaObject::push(L, self->Y);
			return 1;
		}

		static int set_Y(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto a1 = LuaObject::checkValue<float>(L, 2);
			self->Y = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_ZeroVector(lua_State* L) {
			LuaObject::pushStatic(L, &FVector2D::ZeroVector);
			return 1;
		}

		static int get_UnitVector(lua_State* L) {
			LuaObject::pushStatic(L, &FVector2D::UnitVector);
			return 1;
		}

		static int Component(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto Index = LuaObject::checkValue<int>(L, 2);
				auto ret = self->Component((int)Index);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::Component error, argc=%d", argc);
				return 0;
			}
		}

		static int Equals(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto V = LuaObject::checkValue<FVector2D*>(L, 2);
				auto Tolerance = LuaObject::checkValue<float>(L, 3);
				auto ret = self->Equals(*V, (float)Tolerance);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V);
				return 2;
			} else {
				luaL_error(L, "call FVector2D::Equals error, argc=%d", argc);
				return 0;
			}
		}

		static int Set(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto InX = LuaObject::checkValue<float>(L, 2);
				auto InY = LuaObject::checkValue<float>(L, 3);
				self->Set((float)InX, (float)InY);
				return 0;
			} else {
				luaL_error(L, "call FVector2D::Set error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->GetMax();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::GetMax error, argc=%d", argc);
				return 0;
			}
		}

		static int GetAbsMax(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->GetAbsMax();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::GetAbsMax error, argc=%d", argc);
				return 0;
			}
		}

		static int GetMin(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->GetMin();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::GetMin error, argc=%d", argc);
				return 0;
			}
		}

		static int Size(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->Size();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::Size error, argc=%d", argc);
				return 0;
			}
		}

		static int SizeSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->SizeSquared();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::SizeSquared error, argc=%d", argc);
				return 0;
			}
		}

		static int GetRotated(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto AngleDeg = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = self->GetRotated((float)AngleDeg);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::GetRotated error, argc=%d", argc);
				return 0;
			}
		}

		static int GetSafeNormal(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFVector2D();
				*ret = self->GetSafeNormal((float)Tolerance);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::GetSafeNormal error, argc=%d", argc);
				return 0;
			}
		}

		static int Normalize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				self->Normalize((float)Tolerance);
				return 0;
			} else {
				luaL_error(L, "call FVector2D::Normalize error, argc=%d", argc);
				return 0;
			}
		}

		static int IsNearlyZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto Tolerance = LuaObject::checkValue<float>(L, 2);
				auto ret = self->IsNearlyZero((float)Tolerance);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::IsNearlyZero error, argc=%d", argc);
				return 0;
			}
		}

		static int ToDirectionAndLength(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto OutDir = LuaObject::checkValue<FVector2D*>(L, 2);
				auto OutLength = LuaObject::checkValue<float>(L, 3);
				self->ToDirectionAndLength(*OutDir, (float)OutLength);
				LuaObject::pushValue(L, OutDir);
				LuaObject::push(L, OutLength);
				return 2;
			} else {
				luaL_error(L, "call FVector2D::ToDirectionAndLength error, argc=%d", argc);
				return 0;
			}
		}

		static int IsZero(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->IsZero();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::IsZero error, argc=%d", argc);
				return 0;
			}
		}

		static int RoundToVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = __newFVector2D();
				*ret = self->RoundToVector();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::RoundToVector error, argc=%d", argc);
				return 0;
			}
		}

		static int ClampAxes(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto MinAxisVal = LuaObject::checkValue<float>(L, 2);
				auto MaxAxisVal = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector2D();
				*ret = self->ClampAxes((float)MinAxisVal, (float)MaxAxisVal);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::ClampAxes error, argc=%d", argc);
				return 0;
			}
		}

		static int GetSignVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = __newFVector2D();
				*ret = self->GetSignVector();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::GetSignVector error, argc=%d", argc);
				return 0;
			}
		}

		static int GetAbs(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = __newFVector2D();
				*ret = self->GetAbs();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::GetAbs error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int InitFromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto InSourceString = LuaObject::checkValue<FString>(L, 2);
				auto ret = self->InitFromString(InSourceString);
				LuaObject::push(L, ret);
				LuaObject::push(L, InSourceString);
				return 2;
			} else {
				luaL_error(L, "call FVector2D::InitFromString error, argc=%d", argc);
				return 0;
			}
		}

		static int DiagnosticCheckNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				self->DiagnosticCheckNaN();
				return 0;
			} else {
				luaL_error(L, "call FVector2D::DiagnosticCheckNaN error, argc=%d", argc);
				return 0;
			}
		}

		static int ContainsNaN(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = self->ContainsNaN();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::ContainsNaN error, argc=%d", argc);
				return 0;
			}
		}

		static int SphericalToUnitCartesian(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FVector2D*>(L, 1);
				auto ret = __newFVector();
				*ret = self->SphericalToUnitCartesian();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FVector2D::SphericalToUnitCartesian error, argc=%d", argc);
				return 0;
			}
		}

		static int DotProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FVector2D*>(L, 2);
				auto B = LuaObject::checkValue<FVector2D*>(L, 3);
				auto ret = FVector2D::DotProduct(*A, *B);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FVector2D::DotProduct error, argc=%d", argc);
				return 0;
			}
		}

		static int DistSquared(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector2D*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector2D*>(L, 3);
				auto ret = FVector2D::DistSquared(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector2D::DistSquared error, argc=%d", argc);
				return 0;
			}
		}

		static int Distance(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto V1 = LuaObject::checkValue<FVector2D*>(L, 2);
				auto V2 = LuaObject::checkValue<FVector2D*>(L, 3);
				auto ret = FVector2D::Distance(*V1, *V2);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, V1);
				LuaObject::pushValue(L, V2);
				return 3;
			} else {
				luaL_error(L, "call FVector2D::Distance error, argc=%d", argc);
				return 0;
			}
		}

		static int CrossProduct(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FVector2D*>(L, 2);
				auto B = LuaObject::checkValue<FVector2D*>(L, 3);
				auto ret = FVector2D::CrossProduct(*A, *B);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FVector2D::CrossProduct error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FVector2D>("FVector2D");
			LuaObject::newType(L, "FVector2D");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FRandomStream"));
#endif
				auto self = new FRandomStream();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FRandomStream"));
#endif
				auto InSeed = LuaObject::checkValue<int>(L, 2);
				auto self = new FRandomStream((int)InSeed);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FRandomStream"));
#endif
			auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
			delete self;
			return 0;
		}

		static int Initialize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto InSeed = LuaObject::checkValue<int>(L, 2);
				self->Initialize((int)InSeed);
				return 0;
			} else {
				luaL_error(L, "call FRandomStream::Initialize error, argc=%d", argc);
				return 0;
			}
		}

		static int Reset(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				self->Reset();
				return 0;
			} else {
				luaL_error(L, "call FRandomStream::Reset error, argc=%d", argc);
				return 0;
			}
		}

		static int GetInitialSeed(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto ret = self->GetInitialSeed();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::GetInitialSeed error, argc=%d", argc);
				return 0;
			}
		}

		static int GenerateNewSeed(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				self->GenerateNewSeed();
				return 0;
			} else {
				luaL_error(L, "call FRandomStream::GenerateNewSeed error, argc=%d", argc);
				return 0;
			}
		}

		static int GetFraction(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto ret = self->GetFraction();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::GetFraction error, argc=%d", argc);
				return 0;
			}
		}

		static int GetUnsignedInt(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto ret = self->GetUnsignedInt();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::GetUnsignedInt error, argc=%d", argc);
				return 0;
			}
		}

		static int GetUnitVector(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto ret = __newFVector();
				*ret = self->GetUnitVector();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::GetUnitVector error, argc=%d", argc);
				return 0;
			}
		}

		static int GetCurrentSeed(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto ret = self->GetCurrentSeed();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::GetCurrentSeed error, argc=%d", argc);
				return 0;
			}
		}

		static int FRand(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto ret = self->FRand();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::FRand error, argc=%d", argc);
				return 0;
			}
		}

		static int RandHelper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto A = LuaObject::checkValue<int>(L, 2);
				auto ret = self->RandHelper((int)A);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::RandHelper error, argc=%d", argc);
				return 0;
			}
		}

		static int RandRange(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto Min = LuaObject::checkValue<int>(L, 2);
				auto Max = LuaObject::checkValue<int>(L, 3);
				auto ret = self->RandRange((int)Min, (int)Max);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::RandRange error, argc=%d", argc);
				return 0;
			}
		}

		static int FRandRange(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto InMin = LuaObject::checkValue<float>(L, 2);
				auto InMax = LuaObject::checkValue<float>(L, 3);
				auto ret = self->FRandRange((float)InMin, (float)InMax);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::FRandRange error, argc=%d", argc);
				return 0;
			}
		}

		static int VRand(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto ret = __newFVector();
				*ret = self->VRand();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FRandomStream::VRand error, argc=%d", argc);
				return 0;
			}
		}

		static int VRandCone(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto Dir = LuaObject::checkValue<FVector*>(L, 2);
				auto ConeHalfAngleRad = LuaObject::checkValue<float>(L, 3);
				auto ret = __newFVector();
				*ret = self->VRandCone(*Dir, (float)ConeHalfAngleRad);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Dir);
				return 2;
			} else if (argc == 4) {
				auto self = LuaObject::checkValue<FRandomStream*>(L, 1);
				auto Dir = LuaObject::checkValue<FVector*>(L, 2);
				auto HorizontalConeHalfAngleRad = LuaObject::checkValue<float>(L, 3);
				auto VerticalConeHalfAngleRad = LuaObject::checkValue<float>(L, 4);
				auto ret = __newFVector();
				*ret = self->VRandCone(*Dir, (float)HorizontalConeHalfAngleRad, (float)VerticalConeHalfAngleRad);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Dir);
				return 2;
			} else {
				luaL_error(L, "call FRandomStream::VRandCone error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FRandomStream>("FRandomStream");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FGuid"));
#endif
				auto self = new FGuid();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 5) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FGuid"));
#endif
				auto InA = LuaObject::checkValue<int>(L, 2);
				auto InB = LuaObject::checkValue<int>(L, 3);
				auto InC = LuaObject::checkValue<int>(L, 4);
				auto InD = LuaObject::checkValue<int>(L, 5);
				auto self = new FGuid((unsigned int)InA, (unsigned int)InB, (unsigned int)InC, (unsigned int)InD);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FGuid() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FGuid"));
#endif
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			delete self;
			return 0;
		}

		static int get_A(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			LuaObject::push(L, self->A);
			return 1;
		}

		static int set_A(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			auto a1 = LuaObject::checkValue<uint32>(L, 2);
			self->A = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_B(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			LuaObject::push(L, self->B);
			return 1;
		}

		static int set_B(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			auto a1 = LuaObject::checkValue<uint32>(L, 2);
			self->B = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_C(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			LuaObject::push(L, self->C);
			return 1;
		}

		static int set_C(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			auto a1 = LuaObject::checkValue<uint32>(L, 2);
			self->C = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int get_D(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			LuaObject::push(L, self->D);
			return 1;
		}

		static int set_D(lua_State* L) {
			auto self = LuaObject::checkValue<FGuid*>(L, 1);
			auto a1 = LuaObject::checkValue<uint32>(L, 2);
			self->D = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int Invalidate(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FGuid*>(L, 1);
				self->Invalidate();
				return 0;
			} else {
				luaL_error(L, "call FGuid::Invalidate error, argc=%d", argc);
				return 0;
			}
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FGuid*>(L, 1);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FGuid::IsValid error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FGuid*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else if (argc == 2) {
				auto self = LuaObject::checkValue<FGuid*>(L, 1);
				auto Format = LuaObject::checkValue<int>(L, 2);
				auto ret = self->ToString((EGuidFormats)Format);
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FGuid::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int NewGuid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFGuid();
				*ret = FGuid::NewGuid();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FGuid::NewGuid error, argc=%d", argc);
				return 0;
			}
		}

		static int Parse(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto GuidString = LuaObject::checkValue<FString>(L, 2);
				auto OutGuid = LuaObject::checkValue<FGuid*>(L, 3);
				auto ret = FGuid::Parse(GuidString, *OutGuid);
				LuaObject::push(L, ret);
				LuaObject::push(L, GuidString);
				LuaObject::pushValue(L, OutGuid);
				return 3;
			} else {
				luaL_error(L, "call FGuid::Parse error, argc=%d", argc);
				return 0;
			}
		}

		static int ParseExact(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto GuidString = LuaObject::checkValue<FString>(L, 2);
				auto Format = LuaObject::checkValue<int>(L, 3);
				auto OutGuid = LuaObject::checkValue<FGuid*>(L, 4);
				auto ret = FGuid::ParseExact(GuidString, (EGuidFormats)Format, *OutGuid);
				LuaObject::push(L, ret);
				LuaObject::push(L, GuidString);
				LuaObject::pushValue(L, OutGuid);
				return 3;
			} else {
				luaL_error(L, "call FGuid::ParseExact error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FGuid>("FGuid");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FBox2D"));
#endif
				auto self = new FBox2D();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FBox2D"));
#endif
				auto _a0 = LuaObject::checkValue<int>(L, 2);
				auto self = new FBox2D((int)_a0);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 3) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FBox2D"));
#endif
				auto InMin = LuaObject::checkValue<FVector2D*>(L, 2);
				auto InMax = LuaObject::checkValue<FVector2D*>(L, 3);
				auto self = new FBox2D(*InMin, *InMax);
				LuaObject::pushValue(L, InMin);
				LuaObject::pushValue(L, InMax);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FBox2D() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FBox2D"));
#endif
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			delete self;
			return 0;
		}

		static int get_Min(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			LuaObject::pushValue(L, &self->Min);
			return 1;
		}

		static int set_Min(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto a1 = LuaObject::checkValue<FVector2D*>(L, 2);
			self->Min = *a1;
			LuaObject::pushValue(L, a1);
			return 1;
		}

		static int get_Max(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			LuaObject::pushValue(L, &self->Max);
			return 1;
		}

		static int set_Max(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto a1 = LuaObject::checkValue<FVector2D*>(L, 2);
			self->Max = *a1;
			LuaObject::pushValue(L, a1);
			return 1;
		}

		static int get_bIsValid(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			LuaObject::push(L, self->bIsValid);
			return 1;
		}

		static int set_bIsValid(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto a1 = LuaObject::checkValue<bool>(L, 2);
			self->bIsValid = a1;
			LuaObject::push(L, a1);
			return 1;
		}

		static int ComputeSquaredDistanceToPoint(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto Point = LuaObject::checkValue<FVector2D*>(L, 2);
				auto ret = self->ComputeSquaredDistanceToPoint(*Point);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, Point);
				return 2;
			} else {
				luaL_error(L, "call FBox2D::ComputeSquaredDistanceToPoint error, argc=%d", argc);
				return 0;
			}
		}

		static int ExpandBy(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto W = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFBox2D();
				*ret = self->ExpandBy((const float)W);
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FBox2D::ExpandBy error, argc=%d", argc);
				return 0;
			}
		}

		static int GetArea(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto ret = self->GetArea();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FBox2D::GetArea error, argc=%d", argc);
				return 0;
			}
		}

		static int GetCenter(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto ret = __newFVector2D();
				*ret = self->GetCenter();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FBox2D::GetCenter error, argc=%d", argc);
				return 0;
			}
		}

		static int GetCenterAndExtents(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto center = LuaObject::checkValue<FVector2D*>(L, 2);
				auto Extents = LuaObject::checkValue<FVector2D*>(L, 3);
				self->GetCenterAndExtents(*center, *Extents);
				LuaObject::pushValue(L, center);
				LuaObject::pushValue(L, Extents);
				return 2;
			} else {
				luaL_error(L, "call FBox2D::GetCenterAndExtents error, argc=%d", argc);
				return 0;
			}
		}

		static int GetClosestPointTo(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto Point = LuaObject::checkValue<FVector2D*>(L, 2);
				auto ret = __newFVector2D();
				*ret = self->GetClosestPointTo(*Point);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Point);
				return 2;
			} else {
				luaL_error(L, "call FBox2D::GetClosestPointTo error, argc=%d", argc);
				return 0;
			}
		}

		static int GetExtent(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto ret = __newFVector2D();
				*ret = self->GetExtent();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FBox2D::GetExtent error, argc=%d", argc);
				return 0;
			}
		}

		static int GetSize(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto ret = __newFVector2D();
				*ret = self->GetSize();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FBox2D::GetSize error, argc=%d", argc);
				return 0;
			}
		}

		static int Init(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				self->Init();
				return 0;
			} else {
				luaL_error(L, "call FBox2D::Init error, argc=%d", argc);
				return 0;
			}
		}

		static int Intersect(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto other = LuaObject::checkValue<FBox2D*>(L, 2);
				auto ret = self->Intersect(*other);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, other);
				return 2;
			} else {
				luaL_error(L, "call FBox2D::Intersect error, argc=%d", argc);
				return 0;
			}
		}

		static int IsInside(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto TestPoint = LuaObject::checkValue<FVector2D*>(L, 2);
				auto ret = self->IsInside(*TestPoint);
				LuaObject::push(L, ret);
				LuaObject::pushValue(L, TestPoint);
				return 2;
			} else {
				luaL_error(L, "call FBox2D::IsInside error, argc=%d", argc);
				return 0;
			}
		}

		static int ShiftBy(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto Offset = LuaObject::checkValue<FVector2D*>(L, 2);
				auto ret = __newFBox2D();
				*ret = self->ShiftBy(*Offset);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Offset);
				return 2;
			} else {
				luaL_error(L, "call FBox2D::ShiftBy error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FBox2D*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FBox2D::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FBox2D>("FBox2D");
			LuaObject::newType(L, "FBox2D");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FFloatRangeBound"));
#endif
				auto self = new FFloatRangeBound();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FFloatRangeBound"));
#endif
				auto InValue = LuaObject::checkValue<int>(L, 2);
				auto self = new FFloatRangeBound((const long long)InValue);
				LuaObject::push(L, InValue);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FFloatRangeBound() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FFloatRangeBound"));
#endif
			auto self = LuaObject::checkValue<FFloatRangeBound*>(L, 1);
			delete self;
			return 0;
		}

		static int Exclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::Exclusive((const float)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FFloatRangeBound::Exclusive error, argc=%d", argc);
				return 0;
			}
		}

		static int Inclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::Inclusive((const float)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FFloatRangeBound::Inclusive error, argc=%d", argc);
				return 0;
			}
		}

		static int Open(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::Open();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FFloatRangeBound::Open error, argc=%d", argc);
				return 0;
			}
		}

		static int FlipInclusion(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Bound = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::FlipInclusion(*Bound);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Bound);
				return 2;
			} else {
				luaL_error(L, "call FFloatRangeBound::FlipInclusion error, argc=%d", argc);
				return 0;
			}
		}

		static int MaxLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MaxLower(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FFloatRangeBound::MaxLower error, argc=%d", argc);
				return 0;
			}
		}

		static int MaxUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MaxUpper(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FFloatRangeBound::MaxUpper error, argc=%d", argc);
				return 0;
			}
		}

		static int MinLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MinLower(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FFloatRangeBound::MinLower error, argc=%d", argc);
				return 0;
			}
		}

		static int MinUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
				auto ret = __newFFloatRangeBound();
				*ret = FFloatRangeBound::MinUpper(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FFloatRangeBound::MinUpper error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FFloatRangeBound>("FFloatRangeBound");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FFloatRange"));
#endif
				auto self = new FFloatRange();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FFloatRange"));
#endif
				auto A = LuaObject::checkValue<float>(L, 2);
				auto self = new FFloatRange((const float)A);
				LuaObject::push(L, A);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 3) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FFloatRange"));
#endif
				auto A = LuaObject::checkValue<float>(L, 2);
				auto B = LuaObject::checkValue<float>(L, 3);
				auto self = new FFloatRange((const float)A, (const float)B);
				LuaObject::push(L, A);
				LuaObject::push(L, B);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FFloatRange() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FFloatRange"));
#endif
			auto self = LuaObject::checkValue<FFloatRange*>(L, 1);
			delete self;
			return 0;
		}

		static int Empty(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFFloatRange();
				*ret = FFloatRange::Empty();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FFloatRange::Empty error, argc=%d", argc);
				return 0;
			}
		}

		static int Hull(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto X = LuaObject::checkValue<FFloatRange*>(L, 2);
				auto Y = LuaObject::checkValue<FFloatRange*>(L, 3);
				auto ret = __newFFloatRange();
				*ret = FFloatRange::Hull(*X, *Y);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, X);
				LuaObject::pushValue(L, Y);
				return 3;
			} else {
				luaL_error(L, "call FFloatRange::Hull error, argc=%d", argc);
				return 0;
			}
		}

		static int Intersection(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto X = LuaObject::checkValue<FFloatRange*>(L, 2);
				auto Y = LuaObject::checkValue<FFloatRange*>(L, 3);
				auto ret = __newFFloatRange();
				*ret = FFloatRange::Intersection(*X, *Y);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, X);
				LuaObject::pushValue(L, Y);
				return 3;
			} else {
				luaL_error(L, "call FFloatRange::Intersection error, argc=%d", argc);
				return 0;
			}
		}

		static int All(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFFloatRange();
				*ret = FFloatRange::All();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FFloatRange::All error, argc=%d", argc);
				return 0;
			}
		}

		static int AtLeast(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFFloatRange();
				*ret = FFloatRange::AtLeast((const float)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FFloatRange::AtLeast error, argc=%d", argc);
				return 0;
			}
		}

		static int AtMost(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<float>(L, 2);
				auto ret = __newFFloatRange();
				*ret = FFloatRange::AtMost((const float)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FFloatRange::AtMost error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FFloatRange>("FFloatRange");
			LuaObject::newType(L, "FFloatRange");
			LuaObject::addMethod(L, "Empty", Empty, false);
			LuaObject::addMethod(L, "Hull", Hull, false);
			LuaObject::addMethod(L, "Intersection", Intersection, false);
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FInt32RangeBound"));
#endif
				auto self = new FInt32RangeBound();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FInt32RangeBound"));
#endif
				auto InValue = LuaObject::checkValue<int>(L, 2);
				auto self = new FInt32RangeBound((const long long)InValue);
				LuaObject::push(L, InValue);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FInt32RangeBound() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FInt32RangeBound"));
#endif
			auto self = LuaObject::checkValue<FInt32RangeBound*>(L, 1);
			delete self;
			return 0;
		}

		static int Exclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<int>(L, 2);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::Exclusive((const int)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FInt32RangeBound::Exclusive error, argc=%d", argc);
				return 0;
			}
		}

		static int Inclusive(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<int>(L, 2);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::Inclusive((const int)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FInt32RangeBound::Inclusive error, argc=%d", argc);
				return 0;
			}
		}

		static int Open(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::Open();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FInt32RangeBound::Open error, argc=%d", argc);
				return 0;
			}
		}

		static int FlipInclusion(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Bound = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::FlipInclusion(*Bound);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, Bound);
				return 2;
			} else {
				luaL_error(L, "call FInt32RangeBound::FlipInclusion error, argc=%d", argc);
				return 0;
			}
		}

		static int MaxLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MaxLower(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FInt32RangeBound::MaxLower error, argc=%d", argc);
				return 0;
			}
		}

		static int MaxUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MaxUpper(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FInt32RangeBound::MaxUpper error, argc=%d", argc);
				return 0;
			}
		}

		static int MinLower(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MinLower(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FInt32RangeBound::MinLower error, argc=%d", argc);
				return 0;
			}
		}

		static int MinUpper(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
				auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
				auto ret = __newFInt32RangeBound();
				*ret = FInt32RangeBound::MinUpper(*A, *B);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, A);
				LuaObject::pushValue(L, B);
				return 3;
			} else {
				luaL_error(L, "call FInt32RangeBound::MinUpper error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FInt32RangeBound>("FInt32RangeBound");
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FInt32Range"));
#endif
				auto self = new FInt32Range();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FInt32Range"));
#endif
				auto A = LuaObject::checkValue<int>(L, 2);
				auto self = new FInt32Range((const int)A);
				LuaObject::push(L, A);
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 3) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FInt32Range"));
#endif
				auto A = LuaObject::checkValue<int>(L, 2);
				auto B = LuaObject::checkValue<int>(L, 3);
				auto self = new FInt32Range((const int)A, (const int)B);
				LuaObject::push(L, A);
				LuaObject::push(L, B);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FInt32Range() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FInt32Range"));
#endif
			auto self = LuaObject::checkValue<FInt32Range*>(L, 1);
			delete self;
			return 0;
		}

		static int Empty(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFInt32Range();
				*ret = FInt32Range::Empty();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FInt32Range::Empty error, argc=%d", argc);
				return 0;
			}
		}

		static int Hull(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto X = LuaObject::checkValue<FInt32Range*>(L, 2);
				auto Y = LuaObject::checkValue<FInt32Range*>(L, 3);
				auto ret = __newFInt32Range();
				*ret = FInt32Range::Hull(*X, *Y);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, X);
				LuaObject::pushValue(L, Y);
				return 3;
			} else {
				luaL_error(L, "call FInt32Range::Hull error, argc=%d", argc);
				return 0;
			}
		}

		static int Intersection(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 3) {
				auto X = LuaObject::checkValue<FInt32Range*>(L, 2);
				auto Y = LuaObject::checkValue<FInt32Range*>(L, 3);
				auto ret = __newFInt32Range();
				*ret = FInt32Range::Intersection(*X, *Y);
				LuaObject::pushValue(L, ret);
				LuaObject::pushValue(L, X);
				LuaObject::pushValue(L, Y);
				return 3;
			} else {
				luaL_error(L, "call FInt32Range::Intersection error, argc=%d", argc);
				return 0;
			}
		}

		static int All(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto ret = __newFInt32Range();
				*ret = FInt32Range::All();
				LuaObject::pushValue(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FInt32Range::All error, argc=%d", argc);
				return 0;
			}
		}

		static int AtLeast(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<int>(L, 2);
				auto ret = __newFInt32Range();
				*ret = FInt32Range::AtLeast((const int)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FInt32Range::AtLeast error, argc=%d", argc);
				return 0;
			}
		}

		static int AtMost(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto Value = LuaObject::checkValue<int>(L, 2);
				auto ret = __newFInt32Range();
				*ret = FInt32Range::AtMost((const int)Value);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, Value);
				return 2;
			} else {
				luaL_error(L, "call FInt32Range::AtMost error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FInt32Range>("FInt32Range");
			LuaObject::newType(L, "FInt32Range");
			LuaObject::addMethod(L, "Empty", Empty, false);
			LuaObject::addMethod(L, "Hull", Hull, false);
			LuaObject::addMethod(L, "Intersection", Intersection, false);
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
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FFloatInterval"));
#endif
				auto self = new FFloatInterval();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 3) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FFloatInterval"));
#endif
				auto InMin = LuaObject::checkValue<float>(L, 2);
				auto InMax = LuaObject::checkValue<float>(L, 3);
				auto self = new FFloatInterval((float)InMin, (float)InMax);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FFloatInterval() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FFloatInterval"));
#endif
			auto self = LuaObject::checkValue<FFloatInterval*>(L, 1);
			delete self;
			return 0;
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FFloatInterval>("FFloatInterval");
			LuaObject::newType(L, "FFloatInterval");
			LuaObject::finishType(L, "FFloatInterval", __ctor, __gc);
		}

	};

	struct FInt32IntervalWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FInt32Interval"));
#endif
				auto self = new FInt32Interval();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 3) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FInt32Interval"));
#endif
				auto InMin = LuaObject::checkValue<int>(L, 2);
				auto InMax = LuaObject::checkValue<int>(L, 3);
				auto self = new FInt32Interval((int)InMin, (int)InMax);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FInt32Interval() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FInt32Interval"));
#endif
			auto self = LuaObject::checkValue<FInt32Interval*>(L, 1);
			delete self;
			return 0;
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FInt32Interval>("FInt32Interval");
			LuaObject::newType(L, "FInt32Interval");
			LuaObject::finishType(L, "FInt32Interval", __ctor, __gc);
		}

	};

	struct FPrimaryAssetTypeWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FPrimaryAssetType"));
#endif
				auto self = new FPrimaryAssetType();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FPrimaryAssetType"));
#endif
				auto InName = LuaObject::checkValue<int>(L, 2);
				auto self = new FPrimaryAssetType((EName)InName);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FPrimaryAssetType() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FPrimaryAssetType"));
#endif
			auto self = LuaObject::checkValue<FPrimaryAssetType*>(L, 1);
			delete self;
			return 0;
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FPrimaryAssetType*>(L, 1);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FPrimaryAssetType::IsValid error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FPrimaryAssetType*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FPrimaryAssetType::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FPrimaryAssetType>("FPrimaryAssetType");
			LuaObject::newType(L, "FPrimaryAssetType");
			LuaObject::addMethod(L, "IsValid", IsValid, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::finishType(L, "FPrimaryAssetType", __ctor, __gc);
		}

	};

	struct FPrimaryAssetIdWrapper {

		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FPrimaryAssetId"));
#endif
				auto self = new FPrimaryAssetId();
				LuaObject::pushValue(L, self);
				return 1;
			} else if (argc == 2) {
#if defined(LUA_WRAPPER_DEBUG)
				Log::Log(TEXT("new FPrimaryAssetId"));
#endif
				auto InString = LuaObject::checkValue<FString>(L, 2);
				auto self = new FPrimaryAssetId(InString);
				LuaObject::push(L, InString);
				LuaObject::pushValue(L, self);
				return 1;
			} else {
				luaL_error(L, "call FPrimaryAssetId() error, argc=%d", argc);
				return 0;
			}
		}

		static int __gc(lua_State* L) {
#if defined(LUA_WRAPPER_DEBUG)
			Log::Log(TEXT("delete FPrimaryAssetId"));
#endif
			auto self = LuaObject::checkValue<FPrimaryAssetId*>(L, 1);
			delete self;
			return 0;
		}

		static int get_PrimaryAssetType(lua_State* L) {
			auto self = LuaObject::checkValue<FPrimaryAssetId*>(L, 1);
			LuaObject::pushValue(L, &self->PrimaryAssetType);
			return 1;
		}

		static int set_PrimaryAssetType(lua_State* L) {
			auto self = LuaObject::checkValue<FPrimaryAssetId*>(L, 1);
			auto a1 = LuaObject::checkValue<FPrimaryAssetType*>(L, 2);
			self->PrimaryAssetType = *a1;
			LuaObject::pushValue(L, a1);
			return 1;
		}

		static int IsValid(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FPrimaryAssetId*>(L, 1);
				auto ret = self->IsValid();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FPrimaryAssetId::IsValid error, argc=%d", argc);
				return 0;
			}
		}

		static int ToString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				auto self = LuaObject::checkValue<FPrimaryAssetId*>(L, 1);
				auto ret = self->ToString();
				LuaObject::push(L, ret);
				return 1;
			} else {
				luaL_error(L, "call FPrimaryAssetId::ToString error, argc=%d", argc);
				return 0;
			}
		}

		static int FromString(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 2) {
				auto String = LuaObject::checkValue<FString>(L, 2);
				auto ret = __newFPrimaryAssetId();
				*ret = FPrimaryAssetId::FromString(String);
				LuaObject::pushValue(L, ret);
				LuaObject::push(L, String);
				return 2;
			} else {
				luaL_error(L, "call FPrimaryAssetId::FromString error, argc=%d", argc);
				return 0;
			}
		}

		static void bind(lua_State* L) {
			LuaObject::initType<FPrimaryAssetId>("FPrimaryAssetId");
			LuaObject::newType(L, "FPrimaryAssetId");
			LuaObject::addField(L, "PrimaryAssetType", get_PrimaryAssetType, set_PrimaryAssetType, true);
			LuaObject::addMethod(L, "IsValid", IsValid, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "FromString", FromString, false);
			LuaObject::finishType(L, "FPrimaryAssetId", __ctor, __gc);
		}

	};

	int LuaWrapper::pushValue(lua_State* L, UStructProperty* p, UScriptStruct* uss, uint8* parms) {
		if (uss == FRotatorStruct) {
			auto ptr = __newFRotator();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FTransformStruct) {
			auto ptr = __newFTransform();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FLinearColorStruct) {
			auto ptr = __newFLinearColor();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FColorStruct) {
			auto ptr = __newFColor();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FVectorStruct) {
			auto ptr = __newFVector();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FVector2DStruct) {
			auto ptr = __newFVector2D();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FRandomStreamStruct) {
			auto ptr = __newFRandomStream();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FGuidStruct) {
			auto ptr = __newFGuid();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FBox2DStruct) {
			auto ptr = __newFBox2D();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FFloatRangeBoundStruct) {
			auto ptr = __newFFloatRangeBound();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FFloatRangeStruct) {
			auto ptr = __newFFloatRange();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FInt32RangeBoundStruct) {
			auto ptr = __newFInt32RangeBound();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FInt32RangeStruct) {
			auto ptr = __newFInt32Range();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FFloatIntervalStruct) {
			auto ptr = __newFFloatInterval();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FInt32IntervalStruct) {
			auto ptr = __newFInt32Interval();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FPrimaryAssetTypeStruct) {
			auto ptr = __newFPrimaryAssetType();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		if (uss == FPrimaryAssetIdStruct) {
			auto ptr = __newFPrimaryAssetId();
			p->CopyValuesInternal(ptr, parms, 1);
			LuaObject::pushValue(L, ptr);
			return 1;
		}
		return 0;
	}

	int LuaWrapper::checkValue(lua_State* L, UStructProperty* p, UScriptStruct* uss, uint8* parms, int i) {
		if (uss == FRotatorStruct) {
			auto v = LuaObject::checkValue<FRotator*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FTransformStruct) {
			auto v = LuaObject::checkValue<FTransform*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FLinearColorStruct) {
			auto v = LuaObject::checkValue<FLinearColor*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FColorStruct) {
			auto v = LuaObject::checkValue<FColor*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FVectorStruct) {
			auto v = LuaObject::checkValue<FVector*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FVector2DStruct) {
			auto v = LuaObject::checkValue<FVector2D*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FRandomStreamStruct) {
			auto v = LuaObject::checkValue<FRandomStream*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FGuidStruct) {
			auto v = LuaObject::checkValue<FGuid*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FBox2DStruct) {
			auto v = LuaObject::checkValue<FBox2D*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FFloatRangeBoundStruct) {
			auto v = LuaObject::checkValue<FFloatRangeBound*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FFloatRangeStruct) {
			auto v = LuaObject::checkValue<FFloatRange*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FInt32RangeBoundStruct) {
			auto v = LuaObject::checkValue<FInt32RangeBound*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FInt32RangeStruct) {
			auto v = LuaObject::checkValue<FInt32Range*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FFloatIntervalStruct) {
			auto v = LuaObject::checkValue<FFloatInterval*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FInt32IntervalStruct) {
			auto v = LuaObject::checkValue<FInt32Interval*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FPrimaryAssetTypeStruct) {
			auto v = LuaObject::checkValue<FPrimaryAssetType*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		if (uss == FPrimaryAssetIdStruct) {
			auto v = LuaObject::checkValue<FPrimaryAssetId*>(L, i);
			p->CopyValuesInternal(parms, v, 1);
			return 1;
		}
		return 0;
	}

	void LuaWrapper::init(lua_State* L) {
		FRotatorStruct = TBaseStructure<FRotator>::Get();
		FTransformStruct = TBaseStructure<FTransform>::Get();
		FLinearColorStruct = TBaseStructure<FLinearColor>::Get();
		FColorStruct = TBaseStructure<FColor>::Get();
		FVectorStruct = TBaseStructure<FVector>::Get();
		FVector2DStruct = TBaseStructure<FVector2D>::Get();
		FRandomStreamStruct = TBaseStructure<FRandomStream>::Get();
		FGuidStruct = TBaseStructure<FGuid>::Get();
		FBox2DStruct = TBaseStructure<FBox2D>::Get();
		FFloatRangeBoundStruct = TBaseStructure<FFloatRangeBound>::Get();
		FFloatRangeStruct = TBaseStructure<FFloatRange>::Get();
		FInt32RangeBoundStruct = TBaseStructure<FInt32RangeBound>::Get();
		FInt32RangeStruct = TBaseStructure<FInt32Range>::Get();
		FFloatIntervalStruct = TBaseStructure<FFloatInterval>::Get();
		FInt32IntervalStruct = TBaseStructure<FInt32Interval>::Get();
		FPrimaryAssetTypeStruct = TBaseStructure<FPrimaryAssetType>::Get();
		FPrimaryAssetIdStruct = TBaseStructure<FPrimaryAssetId>::Get();

		FRotatorWrapper::bind(L);
		FTransformWrapper::bind(L);
		FLinearColorWrapper::bind(L);
		FColorWrapper::bind(L);
		FVectorWrapper::bind(L);
		FVector2DWrapper::bind(L);
		FRandomStreamWrapper::bind(L);
		FGuidWrapper::bind(L);
		FBox2DWrapper::bind(L);
		FFloatRangeBoundWrapper::bind(L);
		FFloatRangeWrapper::bind(L);
		FInt32RangeBoundWrapper::bind(L);
		FInt32RangeWrapper::bind(L);
		FFloatIntervalWrapper::bind(L);
		FInt32IntervalWrapper::bind(L);
		FPrimaryAssetTypeWrapper::bind(L);
		FPrimaryAssetIdWrapper::bind(L);
	}

}

