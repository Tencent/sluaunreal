#include "LuaObject.h"

namespace slua {

	struct FRotatorWrapper {

		static int __ctor(lua_State* L) {
			auto self = new FRotator;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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

		static int IsNearlyZero(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = self->IsNearlyZero((float)Tolerance);
			LuaObject::push(L, ret);
			return 1;
		}

		static int IsZero(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = self->IsZero();
			LuaObject::push(L, ret);
			return 1;
		}

		static int Equals(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto R = LuaObject::checkValue<FRotator*>(L, 2);
			auto Tolerance = LuaObject::checkValue<float>(L, 3);
			auto ret = self->Equals(*R, (float)Tolerance);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, R);
			return 2;
		}

		static int Add(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto DeltaPitch = LuaObject::checkValue<float>(L, 2);
			auto DeltaYaw = LuaObject::checkValue<float>(L, 3);
			auto DeltaRoll = LuaObject::checkValue<float>(L, 4);
			auto ret = new FRotator;
			*ret = self->Add((float)DeltaPitch, (float)DeltaYaw, (float)DeltaRoll);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetInverse(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = new FRotator;
			*ret = self->GetInverse();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GridSnap(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto RotGrid = LuaObject::checkValue<FRotator*>(L, 2);
			auto ret = new FRotator;
			*ret = self->GridSnap(*RotGrid);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, RotGrid);
			return 2;
		}

		static int Vector(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = new FVector;
			*ret = self->Vector();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Euler(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = new FVector;
			*ret = self->Euler();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int RotateVector(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto V = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = self->RotateVector(*V);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, V);
			return 2;
		}

		static int UnrotateVector(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto V = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = self->UnrotateVector(*V);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, V);
			return 2;
		}

		static int Clamp(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = new FRotator;
			*ret = self->Clamp();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetNormalized(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = new FRotator;
			*ret = self->GetNormalized();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetDenormalized(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = new FRotator;
			*ret = self->GetDenormalized();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetComponentForAxis(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto Axis = LuaObject::checkValue<int>(L, 2);
			auto ret = self->GetComponentForAxis((EAxis::Type)Axis);
			LuaObject::push(L, ret);
			return 1;
		}

		static int SetComponentForAxis(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto Axis = LuaObject::checkValue<int>(L, 2);
			auto Component = LuaObject::checkValue<float>(L, 3);
			self->SetComponentForAxis((EAxis::Type)Axis, (float)Component);
			return 0;
		}

		static int Normalize(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			self->Normalize();
			return 0;
		}

		static int GetWindingAndRemainder(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto Winding = LuaObject::checkValue<FRotator*>(L, 2);
			auto Remainder = LuaObject::checkValue<FRotator*>(L, 3);
			self->GetWindingAndRemainder(*Winding, *Remainder);
			LuaObject::pushValue(L, Winding);
			LuaObject::pushValue(L, Remainder);
			return 2;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToCompactString(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = self->ToCompactString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int InitFromString(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto InSourceString = LuaObject::checkValue<FString>(L, 2);
			auto ret = self->InitFromString(InSourceString);
			LuaObject::push(L, ret);
			LuaObject::push(L, InSourceString);
			return 2;
		}

		static int ContainsNaN(lua_State* L) {
			auto self = LuaObject::checkValue<FRotator*>(L, 1);
			auto ret = self->ContainsNaN();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ClampAxis(lua_State* L) {
			auto Angle = LuaObject::checkValue<float>(L, 2);
			auto ret = FRotator::ClampAxis((float)Angle);
			LuaObject::push(L, ret);
			return 1;
		}

		static int NormalizeAxis(lua_State* L) {
			auto Angle = LuaObject::checkValue<float>(L, 2);
			auto ret = FRotator::NormalizeAxis((float)Angle);
			LuaObject::push(L, ret);
			return 1;
		}

		static int CompressAxisToByte(lua_State* L) {
			auto Angle = LuaObject::checkValue<float>(L, 2);
			auto ret = FRotator::CompressAxisToByte((float)Angle);
			LuaObject::push(L, ret);
			return 1;
		}

		static int DecompressAxisFromByte(lua_State* L) {
			auto Angle = LuaObject::checkValue<int>(L, 2);
			auto ret = FRotator::DecompressAxisFromByte((unsigned short)Angle);
			LuaObject::push(L, ret);
			return 1;
		}

		static int CompressAxisToShort(lua_State* L) {
			auto Angle = LuaObject::checkValue<float>(L, 2);
			auto ret = FRotator::CompressAxisToShort((float)Angle);
			LuaObject::push(L, ret);
			return 1;
		}

		static int DecompressAxisFromShort(lua_State* L) {
			auto Angle = LuaObject::checkValue<int>(L, 2);
			auto ret = FRotator::DecompressAxisFromShort((unsigned short)Angle);
			LuaObject::push(L, ret);
			return 1;
		}

		static int MakeFromEuler(lua_State* L) {
			auto Euler = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FRotator;
			*ret = FRotator::MakeFromEuler(*Euler);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Euler);
			return 2;
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

		static void bind(lua_State* L) {
			LuaObject::initType<FRotator>("FRotator");
			LuaObject::newType(L, "FRotator");
			LuaObject::addField(L, "Pitch", get_Pitch, set_Pitch, true);
			LuaObject::addField(L, "Yaw", get_Yaw, set_Yaw, true);
			LuaObject::addField(L, "Roll", get_Roll, set_Roll, true);
			LuaObject::addField(L, "ZeroRotator", get_ZeroRotator, nullptr, false);
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
			LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
			LuaObject::finishType(L, "FRotator", __ctor, __gc);
		}

	};

	struct FLinearColorWrapper {

		static int __ctor(lua_State* L) {
			auto self = new FLinearColor;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = new FColor;
			*ret = self->ToRGBE();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetClamped(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto InMin = LuaObject::checkValue<float>(L, 2);
			auto InMax = LuaObject::checkValue<float>(L, 3);
			auto ret = new FLinearColor;
			*ret = self->GetClamped((float)InMin, (float)InMax);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Equals(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
			auto Tolerance = LuaObject::checkValue<float>(L, 3);
			auto ret = self->Equals(*ColorB, (float)Tolerance);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, ColorB);
			return 2;
		}

		static int CopyWithNewOpacity(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto NewOpacicty = LuaObject::checkValue<float>(L, 2);
			auto ret = new FLinearColor;
			*ret = self->CopyWithNewOpacity((float)NewOpacicty);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int LinearRGBToHSV(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = new FLinearColor;
			*ret = self->LinearRGBToHSV();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int HSVToLinearRGB(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = new FLinearColor;
			*ret = self->HSVToLinearRGB();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Quantize(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = new FColor;
			*ret = self->Quantize();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int QuantizeRound(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = new FColor;
			*ret = self->QuantizeRound();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int ToFColor(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto bSRGB = LuaObject::checkValue<bool>(L, 2);
			auto ret = new FColor;
			*ret = self->ToFColor((const bool)bSRGB);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Desaturate(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto Desaturation = LuaObject::checkValue<float>(L, 2);
			auto ret = new FLinearColor;
			*ret = self->Desaturate((float)Desaturation);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int ComputeLuminance(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = self->ComputeLuminance();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetMax(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = self->GetMax();
			LuaObject::push(L, ret);
			return 1;
		}

		static int IsAlmostBlack(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = self->IsAlmostBlack();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetMin(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = self->GetMin();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetLuminance(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = self->GetLuminance();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int InitFromString(lua_State* L) {
			auto self = LuaObject::checkValue<FLinearColor*>(L, 1);
			auto InSourceString = LuaObject::checkValue<FString>(L, 2);
			auto ret = self->InitFromString(InSourceString);
			LuaObject::push(L, ret);
			LuaObject::push(L, InSourceString);
			return 2;
		}

		static int FromSRGBColor(lua_State* L) {
			auto Color = LuaObject::checkValue<FColor*>(L, 2);
			auto ret = new FLinearColor;
			*ret = FLinearColor::FromSRGBColor(*Color);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Color);
			return 2;
		}

		static int FromPow22Color(lua_State* L) {
			auto Color = LuaObject::checkValue<FColor*>(L, 2);
			auto ret = new FLinearColor;
			*ret = FLinearColor::FromPow22Color(*Color);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Color);
			return 2;
		}

		static int FGetHSV(lua_State* L) {
			auto H = LuaObject::checkValue<int>(L, 2);
			auto S = LuaObject::checkValue<int>(L, 3);
			auto V = LuaObject::checkValue<int>(L, 4);
			auto ret = new FLinearColor;
			*ret = FLinearColor::FGetHSV((unsigned char)H, (unsigned char)S, (unsigned char)V);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int MakeRandomColor(lua_State* L) {
			auto ret = new FLinearColor;
			*ret = FLinearColor::MakeRandomColor();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int MakeFromColorTemperature(lua_State* L) {
			auto Temp = LuaObject::checkValue<float>(L, 2);
			auto ret = new FLinearColor;
			*ret = FLinearColor::MakeFromColorTemperature((float)Temp);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Dist(lua_State* L) {
			auto V1 = LuaObject::checkValue<FLinearColor*>(L, 2);
			auto V2 = LuaObject::checkValue<FLinearColor*>(L, 3);
			auto ret = FLinearColor::Dist(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int LerpUsingHSV(lua_State* L) {
			auto From = LuaObject::checkValue<FLinearColor*>(L, 2);
			auto To = LuaObject::checkValue<FLinearColor*>(L, 3);
			auto Progress = LuaObject::checkValue<float>(L, 4);
			auto ret = new FLinearColor;
			*ret = FLinearColor::LerpUsingHSV(*From, *To, (const float)Progress);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, From);
			LuaObject::pushValue(L, To);
			return 3;
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
			LuaObject::addMethod(L, "Component", Component, true);
			LuaObject::finishType(L, "FLinearColor", __ctor, __gc);
		}

	};

	struct FColorWrapper {

		static int __ctor(lua_State* L) {
			auto self = new FColor;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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

		static int FromRGBE(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = new FLinearColor;
			*ret = self->FromRGBE();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int WithAlpha(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto Alpha = LuaObject::checkValue<int>(L, 2);
			auto ret = new FColor;
			*ret = self->WithAlpha((unsigned char)Alpha);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int ReinterpretAsLinear(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = new FLinearColor;
			*ret = self->ReinterpretAsLinear();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int ToHex(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = self->ToHex();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int InitFromString(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto InSourceString = LuaObject::checkValue<FString>(L, 2);
			auto ret = self->InitFromString(InSourceString);
			LuaObject::push(L, ret);
			LuaObject::push(L, InSourceString);
			return 2;
		}

		static int ToPackedARGB(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = self->ToPackedARGB();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToPackedABGR(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = self->ToPackedABGR();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToPackedRGBA(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = self->ToPackedRGBA();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToPackedBGRA(lua_State* L) {
			auto self = LuaObject::checkValue<FColor*>(L, 1);
			auto ret = self->ToPackedBGRA();
			LuaObject::push(L, ret);
			return 1;
		}

		static int FromHex(lua_State* L) {
			auto HexString = LuaObject::checkValue<FString>(L, 2);
			auto ret = new FColor;
			*ret = FColor::FromHex(HexString);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, HexString);
			return 2;
		}

		static int MakeRandomColor(lua_State* L) {
			auto ret = new FColor;
			*ret = FColor::MakeRandomColor();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int MakeRedToGreenColorFromScalar(lua_State* L) {
			auto Scalar = LuaObject::checkValue<float>(L, 2);
			auto ret = new FColor;
			*ret = FColor::MakeRedToGreenColorFromScalar((float)Scalar);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int MakeFromColorTemperature(lua_State* L) {
			auto Temp = LuaObject::checkValue<float>(L, 2);
			auto ret = new FColor;
			*ret = FColor::MakeFromColorTemperature((float)Temp);
			LuaObject::pushValue(L, ret);
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
			LuaObject::addMethod(L, "DWColor", DWColor, true);
			LuaObject::finishType(L, "FColor", __ctor, __gc);
		}

	};

	struct FVectorWrapper {

		static int __ctor(lua_State* L) {
			auto self = new FVector;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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

		static int Equals(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto V = LuaObject::checkValue<FVector*>(L, 2);
			auto Tolerance = LuaObject::checkValue<float>(L, 3);
			auto ret = self->Equals(*V, (float)Tolerance);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V);
			return 2;
		}

		static int AllComponentsEqual(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = self->AllComponentsEqual((float)Tolerance);
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetComponentForAxis(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Axis = LuaObject::checkValue<int>(L, 2);
			auto ret = self->GetComponentForAxis((EAxis::Type)Axis);
			LuaObject::push(L, ret);
			return 1;
		}

		static int SetComponentForAxis(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Axis = LuaObject::checkValue<int>(L, 2);
			auto Component = LuaObject::checkValue<float>(L, 3);
			self->SetComponentForAxis((EAxis::Type)Axis, (float)Component);
			return 0;
		}

		static int Set(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto InX = LuaObject::checkValue<float>(L, 2);
			auto InY = LuaObject::checkValue<float>(L, 3);
			auto InZ = LuaObject::checkValue<float>(L, 4);
			self->Set((float)InX, (float)InY, (float)InZ);
			return 0;
		}

		static int GetMax(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->GetMax();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetAbsMax(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->GetAbsMax();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetMin(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->GetMin();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetAbsMin(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->GetAbsMin();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ComponentMin(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Other = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = self->ComponentMin(*Other);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Other);
			return 2;
		}

		static int ComponentMax(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Other = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = self->ComponentMax(*Other);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Other);
			return 2;
		}

		static int GetAbs(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FVector;
			*ret = self->GetAbs();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Size(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->Size();
			LuaObject::push(L, ret);
			return 1;
		}

		static int SizeSquared(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->SizeSquared();
			LuaObject::push(L, ret);
			return 1;
		}

		static int Size2D(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->Size2D();
			LuaObject::push(L, ret);
			return 1;
		}

		static int SizeSquared2D(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->SizeSquared2D();
			LuaObject::push(L, ret);
			return 1;
		}

		static int IsNearlyZero(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = self->IsNearlyZero((float)Tolerance);
			LuaObject::push(L, ret);
			return 1;
		}

		static int IsZero(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->IsZero();
			LuaObject::push(L, ret);
			return 1;
		}

		static int Normalize(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = self->Normalize((float)Tolerance);
			LuaObject::push(L, ret);
			return 1;
		}

		static int IsNormalized(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->IsNormalized();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToDirectionAndLength(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto OutDir = LuaObject::checkValue<FVector*>(L, 2);
			auto OutLength = LuaObject::checkValue<float>(L, 3);
			self->ToDirectionAndLength(*OutDir, (float)OutLength);
			LuaObject::pushValue(L, OutDir);
			LuaObject::push(L, OutLength);
			return 2;
		}

		static int GetSignVector(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FVector;
			*ret = self->GetSignVector();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Projection(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FVector;
			*ret = self->Projection();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetUnsafeNormal(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FVector;
			*ret = self->GetUnsafeNormal();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GridSnap(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto GridSz = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector;
			*ret = self->GridSnap((const float)GridSz);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, GridSz);
			return 2;
		}

		static int BoundToCube(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Radius = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector;
			*ret = self->BoundToCube((float)Radius);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetClampedToSize(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Min = LuaObject::checkValue<float>(L, 2);
			auto Max = LuaObject::checkValue<float>(L, 3);
			auto ret = new FVector;
			*ret = self->GetClampedToSize((float)Min, (float)Max);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetClampedToSize2D(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Min = LuaObject::checkValue<float>(L, 2);
			auto Max = LuaObject::checkValue<float>(L, 3);
			auto ret = new FVector;
			*ret = self->GetClampedToSize2D((float)Min, (float)Max);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetClampedToMaxSize(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto MaxSize = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector;
			*ret = self->GetClampedToMaxSize((float)MaxSize);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetClampedToMaxSize2D(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto MaxSize = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector;
			*ret = self->GetClampedToMaxSize2D((float)MaxSize);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int AddBounded(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto V = LuaObject::checkValue<FVector*>(L, 2);
			auto Radius = LuaObject::checkValue<float>(L, 3);
			self->AddBounded(*V, (float)Radius);
			LuaObject::pushValue(L, V);
			return 1;
		}

		static int Reciprocal(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FVector;
			*ret = self->Reciprocal();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int IsUniform(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = self->IsUniform((float)Tolerance);
			LuaObject::push(L, ret);
			return 1;
		}

		static int MirrorByVector(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto MirrorNormal = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = self->MirrorByVector(*MirrorNormal);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, MirrorNormal);
			return 2;
		}

		static int RotateAngleAxis(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto AngleDeg = LuaObject::checkValue<float>(L, 2);
			auto Axis = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = new FVector;
			*ret = self->RotateAngleAxis((const float)AngleDeg, *Axis);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Axis);
			return 2;
		}

		static int GetSafeNormal(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector;
			*ret = self->GetSafeNormal((float)Tolerance);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetSafeNormal2D(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector;
			*ret = self->GetSafeNormal2D((float)Tolerance);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int CosineAngle2D(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto B = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = self->CosineAngle2D(*B);
			LuaObject::push(L, ret);
			return 1;
		}

		static int ProjectOnTo(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto A = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = self->ProjectOnTo(*A);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			return 2;
		}

		static int ProjectOnToNormal(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Normal = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = self->ProjectOnToNormal(*Normal);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Normal);
			return 2;
		}

		static int ToOrientationRotator(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FRotator;
			*ret = self->ToOrientationRotator();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Rotation(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FRotator;
			*ret = self->Rotation();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int FindBestAxisVectors(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto Axis1 = LuaObject::checkValue<FVector*>(L, 2);
			auto Axis2 = LuaObject::checkValue<FVector*>(L, 3);
			self->FindBestAxisVectors(*Axis1, *Axis2);
			LuaObject::pushValue(L, Axis1);
			LuaObject::pushValue(L, Axis2);
			return 2;
		}

		static int UnwindEuler(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			self->UnwindEuler();
			return 0;
		}

		static int ContainsNaN(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->ContainsNaN();
			LuaObject::push(L, ret);
			return 1;
		}

		static int IsUnit(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto LengthSquaredTolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = self->IsUnit((float)LengthSquaredTolerance);
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToCompactString(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->ToCompactString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int InitFromString(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto InSourceString = LuaObject::checkValue<FString>(L, 2);
			auto ret = self->InitFromString(InSourceString);
			LuaObject::push(L, ret);
			LuaObject::push(L, InSourceString);
			return 2;
		}

		static int UnitCartesianToSpherical(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = new FVector2D;
			*ret = self->UnitCartesianToSpherical();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int HeadingAngle(lua_State* L) {
			auto self = LuaObject::checkValue<FVector*>(L, 1);
			auto ret = self->HeadingAngle();
			LuaObject::push(L, ret);
			return 1;
		}

		static int CrossProduct(lua_State* L) {
			auto A = LuaObject::checkValue<FVector*>(L, 2);
			auto B = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = new FVector;
			*ret = FVector::CrossProduct(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int DotProduct(lua_State* L) {
			auto A = LuaObject::checkValue<FVector*>(L, 2);
			auto B = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::DotProduct(*A, *B);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int CreateOrthonormalBasis(lua_State* L) {
			auto XAxis = LuaObject::checkValue<FVector*>(L, 2);
			auto YAxis = LuaObject::checkValue<FVector*>(L, 3);
			auto ZAxis = LuaObject::checkValue<FVector*>(L, 4);
			FVector::CreateOrthonormalBasis(*XAxis, *YAxis, *ZAxis);
			LuaObject::pushValue(L, XAxis);
			LuaObject::pushValue(L, YAxis);
			LuaObject::pushValue(L, ZAxis);
			return 3;
		}

		static int PointsAreSame(lua_State* L) {
			auto P = LuaObject::checkValue<FVector*>(L, 2);
			auto Q = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::PointsAreSame(*P, *Q);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, P);
			LuaObject::pushValue(L, Q);
			return 3;
		}

		static int PointsAreNear(lua_State* L) {
			auto Point1 = LuaObject::checkValue<FVector*>(L, 2);
			auto Point2 = LuaObject::checkValue<FVector*>(L, 3);
			auto Dist = LuaObject::checkValue<float>(L, 4);
			auto ret = FVector::PointsAreNear(*Point1, *Point2, (float)Dist);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, Point1);
			LuaObject::pushValue(L, Point2);
			return 3;
		}

		static int PointPlaneDist(lua_State* L) {
			auto Point = LuaObject::checkValue<FVector*>(L, 2);
			auto PlaneBase = LuaObject::checkValue<FVector*>(L, 3);
			auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 4);
			auto ret = FVector::PointPlaneDist(*Point, *PlaneBase, *PlaneNormal);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, Point);
			LuaObject::pushValue(L, PlaneBase);
			LuaObject::pushValue(L, PlaneNormal);
			return 4;
		}

		static int VectorPlaneProject(lua_State* L) {
			auto V = LuaObject::checkValue<FVector*>(L, 2);
			auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = new FVector;
			*ret = FVector::VectorPlaneProject(*V, *PlaneNormal);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, V);
			LuaObject::pushValue(L, PlaneNormal);
			return 3;
		}

		static int Dist(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::Dist(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int Distance(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::Distance(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int DistXY(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::DistXY(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int Dist2D(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::Dist2D(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int DistSquared(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::DistSquared(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int DistSquaredXY(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::DistSquaredXY(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int DistSquared2D(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::DistSquared2D(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int BoxPushOut(lua_State* L) {
			auto Normal = LuaObject::checkValue<FVector*>(L, 2);
			auto Size = LuaObject::checkValue<FVector*>(L, 3);
			auto ret = FVector::BoxPushOut(*Normal, *Size);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, Normal);
			LuaObject::pushValue(L, Size);
			return 3;
		}

		static int Parallel(lua_State* L) {
			auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
			auto Normal2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 4);
			auto ret = FVector::Parallel(*Normal1, *Normal2, (float)ParallelCosineThreshold);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, Normal1);
			LuaObject::pushValue(L, Normal2);
			return 3;
		}

		static int Coincident(lua_State* L) {
			auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
			auto Normal2 = LuaObject::checkValue<FVector*>(L, 3);
			auto ParallelCosineThreshold = LuaObject::checkValue<float>(L, 4);
			auto ret = FVector::Coincident(*Normal1, *Normal2, (float)ParallelCosineThreshold);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, Normal1);
			LuaObject::pushValue(L, Normal2);
			return 3;
		}

		static int Orthogonal(lua_State* L) {
			auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
			auto Normal2 = LuaObject::checkValue<FVector*>(L, 3);
			auto OrthogonalCosineThreshold = LuaObject::checkValue<float>(L, 4);
			auto ret = FVector::Orthogonal(*Normal1, *Normal2, (float)OrthogonalCosineThreshold);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, Normal1);
			LuaObject::pushValue(L, Normal2);
			return 3;
		}

		static int Coplanar(lua_State* L) {
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
		}

		static int Triple(lua_State* L) {
			auto X = LuaObject::checkValue<FVector*>(L, 2);
			auto Y = LuaObject::checkValue<FVector*>(L, 3);
			auto Z = LuaObject::checkValue<FVector*>(L, 4);
			auto ret = FVector::Triple(*X, *Y, *Z);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, X);
			LuaObject::pushValue(L, Y);
			LuaObject::pushValue(L, Z);
			return 4;
		}

		static int RadiansToDegrees(lua_State* L) {
			auto RadVector = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = FVector::RadiansToDegrees(*RadVector);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, RadVector);
			return 2;
		}

		static int DegreesToRadians(lua_State* L) {
			auto DegVector = LuaObject::checkValue<FVector*>(L, 2);
			auto ret = new FVector;
			*ret = FVector::DegreesToRadians(*DegVector);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, DegVector);
			return 2;
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

		static int PointPlaneProject(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 4) {
				auto Point = LuaObject::checkValue<FVector*>(L, 2);
				auto PlaneBase = LuaObject::checkValue<FVector*>(L, 3);
				auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 4);
				auto ret = new FVector;
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
				auto ret = new FVector;
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
			LuaObject::addMethod(L, "Equals", Equals, true);
			LuaObject::addMethod(L, "AllComponentsEqual", AllComponentsEqual, true);
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
			LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
			LuaObject::addMethod(L, "Component", Component, true);
			LuaObject::addMethod(L, "PointPlaneProject", PointPlaneProject, false);
			LuaObject::finishType(L, "FVector", __ctor, __gc);
		}

	};

	struct FVector2DWrapper {

		static int __ctor(lua_State* L) {
			auto self = new FVector2D;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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

		static int Equals(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto V = LuaObject::checkValue<FVector2D*>(L, 2);
			auto Tolerance = LuaObject::checkValue<float>(L, 3);
			auto ret = self->Equals(*V, (float)Tolerance);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V);
			return 2;
		}

		static int Set(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto InX = LuaObject::checkValue<float>(L, 2);
			auto InY = LuaObject::checkValue<float>(L, 3);
			self->Set((float)InX, (float)InY);
			return 0;
		}

		static int GetMax(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->GetMax();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetAbsMax(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->GetAbsMax();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetMin(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->GetMin();
			LuaObject::push(L, ret);
			return 1;
		}

		static int Size(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->Size();
			LuaObject::push(L, ret);
			return 1;
		}

		static int SizeSquared(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->SizeSquared();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetRotated(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto AngleDeg = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector2D;
			*ret = self->GetRotated((float)AngleDeg);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetSafeNormal(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = new FVector2D;
			*ret = self->GetSafeNormal((float)Tolerance);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Normalize(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			self->Normalize((float)Tolerance);
			return 0;
		}

		static int IsNearlyZero(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto Tolerance = LuaObject::checkValue<float>(L, 2);
			auto ret = self->IsNearlyZero((float)Tolerance);
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToDirectionAndLength(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto OutDir = LuaObject::checkValue<FVector2D*>(L, 2);
			auto OutLength = LuaObject::checkValue<float>(L, 3);
			self->ToDirectionAndLength(*OutDir, (float)OutLength);
			LuaObject::pushValue(L, OutDir);
			LuaObject::push(L, OutLength);
			return 2;
		}

		static int IsZero(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->IsZero();
			LuaObject::push(L, ret);
			return 1;
		}

		static int RoundToVector(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = new FVector2D;
			*ret = self->RoundToVector();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int ClampAxes(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto MinAxisVal = LuaObject::checkValue<float>(L, 2);
			auto MaxAxisVal = LuaObject::checkValue<float>(L, 3);
			auto ret = new FVector2D;
			*ret = self->ClampAxes((float)MinAxisVal, (float)MaxAxisVal);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetSignVector(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = new FVector2D;
			*ret = self->GetSignVector();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetAbs(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = new FVector2D;
			*ret = self->GetAbs();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int InitFromString(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto InSourceString = LuaObject::checkValue<FString>(L, 2);
			auto ret = self->InitFromString(InSourceString);
			LuaObject::push(L, ret);
			LuaObject::push(L, InSourceString);
			return 2;
		}

		static int DiagnosticCheckNaN(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			self->DiagnosticCheckNaN();
			return 0;
		}

		static int ContainsNaN(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = self->ContainsNaN();
			LuaObject::push(L, ret);
			return 1;
		}

		static int SphericalToUnitCartesian(lua_State* L) {
			auto self = LuaObject::checkValue<FVector2D*>(L, 1);
			auto ret = new FVector;
			*ret = self->SphericalToUnitCartesian();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int DotProduct(lua_State* L) {
			auto A = LuaObject::checkValue<FVector2D*>(L, 2);
			auto B = LuaObject::checkValue<FVector2D*>(L, 3);
			auto ret = FVector2D::DotProduct(*A, *B);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int DistSquared(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector2D*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector2D*>(L, 3);
			auto ret = FVector2D::DistSquared(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int Distance(lua_State* L) {
			auto V1 = LuaObject::checkValue<FVector2D*>(L, 2);
			auto V2 = LuaObject::checkValue<FVector2D*>(L, 3);
			auto ret = FVector2D::Distance(*V1, *V2);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, V1);
			LuaObject::pushValue(L, V2);
			return 3;
		}

		static int CrossProduct(lua_State* L) {
			auto A = LuaObject::checkValue<FVector2D*>(L, 2);
			auto B = LuaObject::checkValue<FVector2D*>(L, 3);
			auto ret = FVector2D::CrossProduct(*A, *B);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
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

		static void bind(lua_State* L) {
			LuaObject::initType<FVector2D>("FVector2D");
			LuaObject::newType(L, "FVector2D");
			LuaObject::addField(L, "X", get_X, set_X, true);
			LuaObject::addField(L, "Y", get_Y, set_Y, true);
			LuaObject::addField(L, "ZeroVector", get_ZeroVector, nullptr, false);
			LuaObject::addField(L, "UnitVector", get_UnitVector, nullptr, false);
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
			LuaObject::addMethod(L, "Component", Component, true);
			LuaObject::finishType(L, "FVector2D", __ctor, __gc);
		}

	};

	struct FBox2DWrapper {

		static int __ctor(lua_State* L) {
			auto self = new FBox2D;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto Point = LuaObject::checkValue<FVector2D*>(L, 2);
			auto ret = self->ComputeSquaredDistanceToPoint(*Point);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, Point);
			return 2;
		}

		static int ExpandBy(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto W = LuaObject::checkValue<float>(L, 2);
			auto ret = new FBox2D;
			*ret = self->ExpandBy((const float)W);
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetArea(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto ret = self->GetArea();
			LuaObject::push(L, ret);
			return 1;
		}

		static int GetCenter(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto ret = new FVector2D;
			*ret = self->GetCenter();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetCenterAndExtents(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto center = LuaObject::checkValue<FVector2D*>(L, 2);
			auto Extents = LuaObject::checkValue<FVector2D*>(L, 3);
			self->GetCenterAndExtents(*center, *Extents);
			LuaObject::pushValue(L, center);
			LuaObject::pushValue(L, Extents);
			return 2;
		}

		static int GetClosestPointTo(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto Point = LuaObject::checkValue<FVector2D*>(L, 2);
			auto ret = new FVector2D;
			*ret = self->GetClosestPointTo(*Point);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Point);
			return 2;
		}

		static int GetExtent(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto ret = new FVector2D;
			*ret = self->GetExtent();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int GetSize(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto ret = new FVector2D;
			*ret = self->GetSize();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Init(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			self->Init();
			return 0;
		}

		static int Intersect(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto other = LuaObject::checkValue<FBox2D*>(L, 2);
			auto ret = self->Intersect(*other);
			LuaObject::push(L, ret);
			LuaObject::pushValue(L, other);
			return 2;
		}

		static int ShiftBy(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto Offset = LuaObject::checkValue<FVector2D*>(L, 2);
			auto ret = new FBox2D;
			*ret = self->ShiftBy(*Offset);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Offset);
			return 2;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FBox2D*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
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
			LuaObject::addMethod(L, "ShiftBy", ShiftBy, true);
			LuaObject::addMethod(L, "ToString", ToString, true);
			LuaObject::addMethod(L, "IsInside", IsInside, true);
			LuaObject::finishType(L, "FBox2D", __ctor, __gc);
		}

	};

	struct FFloatRangeBoundWrapper {

		static int __ctor(lua_State* L) {
			auto self = new FFloatRangeBound;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
			auto self = LuaObject::checkValue<FFloatRangeBound*>(L, 1);
			delete self;
			return 0;
		}

		static int Exclusive(lua_State* L) {
			auto Value = LuaObject::checkValue<float>(L, 2);
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::Exclusive((const float)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
		}

		static int Inclusive(lua_State* L) {
			auto Value = LuaObject::checkValue<float>(L, 2);
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::Inclusive((const float)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
		}

		static int Open(lua_State* L) {
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::Open();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int FlipInclusion(lua_State* L) {
			auto Bound = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::FlipInclusion(*Bound);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Bound);
			return 2;
		}

		static int MaxLower(lua_State* L) {
			auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::MaxLower(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int MaxUpper(lua_State* L) {
			auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::MaxUpper(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int MinLower(lua_State* L) {
			auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::MinLower(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int MinUpper(lua_State* L) {
			auto A = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 3);
			auto ret = new FFloatRangeBound;
			*ret = FFloatRangeBound::MinUpper(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
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
			auto self = new FFloatRange;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
			auto self = LuaObject::checkValue<FFloatRange*>(L, 1);
			delete self;
			return 0;
		}

		static int Empty(lua_State* L) {
			auto ret = new FFloatRange;
			*ret = FFloatRange::Empty();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Hull(lua_State* L) {
			auto X = LuaObject::checkValue<FFloatRange*>(L, 2);
			auto Y = LuaObject::checkValue<FFloatRange*>(L, 3);
			auto ret = new FFloatRange;
			*ret = FFloatRange::Hull(*X, *Y);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, X);
			LuaObject::pushValue(L, Y);
			return 3;
		}

		static int Intersection(lua_State* L) {
			auto X = LuaObject::checkValue<FFloatRange*>(L, 2);
			auto Y = LuaObject::checkValue<FFloatRange*>(L, 3);
			auto ret = new FFloatRange;
			*ret = FFloatRange::Intersection(*X, *Y);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, X);
			LuaObject::pushValue(L, Y);
			return 3;
		}

		static int All(lua_State* L) {
			auto ret = new FFloatRange;
			*ret = FFloatRange::All();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int AtLeast(lua_State* L) {
			auto Value = LuaObject::checkValue<float>(L, 2);
			auto ret = new FFloatRange;
			*ret = FFloatRange::AtLeast((const float)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
		}

		static int AtMost(lua_State* L) {
			auto Value = LuaObject::checkValue<float>(L, 2);
			auto ret = new FFloatRange;
			*ret = FFloatRange::AtMost((const float)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
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
			auto self = new FInt32RangeBound;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
			auto self = LuaObject::checkValue<FInt32RangeBound*>(L, 1);
			delete self;
			return 0;
		}

		static int Exclusive(lua_State* L) {
			auto Value = LuaObject::checkValue<int>(L, 2);
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::Exclusive((const int)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
		}

		static int Inclusive(lua_State* L) {
			auto Value = LuaObject::checkValue<int>(L, 2);
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::Inclusive((const int)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
		}

		static int Open(lua_State* L) {
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::Open();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int FlipInclusion(lua_State* L) {
			auto Bound = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::FlipInclusion(*Bound);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, Bound);
			return 2;
		}

		static int MaxLower(lua_State* L) {
			auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::MaxLower(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int MaxUpper(lua_State* L) {
			auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::MaxUpper(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int MinLower(lua_State* L) {
			auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::MinLower(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
		}

		static int MinUpper(lua_State* L) {
			auto A = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
			auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 3);
			auto ret = new FInt32RangeBound;
			*ret = FInt32RangeBound::MinUpper(*A, *B);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, A);
			LuaObject::pushValue(L, B);
			return 3;
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
			auto self = new FInt32Range;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
			auto self = LuaObject::checkValue<FInt32Range*>(L, 1);
			delete self;
			return 0;
		}

		static int Empty(lua_State* L) {
			auto ret = new FInt32Range;
			*ret = FInt32Range::Empty();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int Hull(lua_State* L) {
			auto X = LuaObject::checkValue<FInt32Range*>(L, 2);
			auto Y = LuaObject::checkValue<FInt32Range*>(L, 3);
			auto ret = new FInt32Range;
			*ret = FInt32Range::Hull(*X, *Y);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, X);
			LuaObject::pushValue(L, Y);
			return 3;
		}

		static int Intersection(lua_State* L) {
			auto X = LuaObject::checkValue<FInt32Range*>(L, 2);
			auto Y = LuaObject::checkValue<FInt32Range*>(L, 3);
			auto ret = new FInt32Range;
			*ret = FInt32Range::Intersection(*X, *Y);
			LuaObject::pushValue(L, ret);
			LuaObject::pushValue(L, X);
			LuaObject::pushValue(L, Y);
			return 3;
		}

		static int All(lua_State* L) {
			auto ret = new FInt32Range;
			*ret = FInt32Range::All();
			LuaObject::pushValue(L, ret);
			return 1;
		}

		static int AtLeast(lua_State* L) {
			auto Value = LuaObject::checkValue<int>(L, 2);
			auto ret = new FInt32Range;
			*ret = FInt32Range::AtLeast((const int)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
		}

		static int AtMost(lua_State* L) {
			auto Value = LuaObject::checkValue<int>(L, 2);
			auto ret = new FInt32Range;
			*ret = FInt32Range::AtMost((const int)Value);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, Value);
			return 2;
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
			auto self = new FFloatInterval;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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
			auto self = new FInt32Interval;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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
			auto self = new FPrimaryAssetType;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
			auto self = LuaObject::checkValue<FPrimaryAssetType*>(L, 1);
			delete self;
			return 0;
		}

		static int IsValid(lua_State* L) {
			auto self = LuaObject::checkValue<FPrimaryAssetType*>(L, 1);
			auto ret = self->IsValid();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FPrimaryAssetType*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
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
			auto self = new FPrimaryAssetId;
			LuaObject::pushValue(L, self);
			return 1;
		}

		static int __gc(lua_State* L) {
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
			auto self = LuaObject::checkValue<FPrimaryAssetId*>(L, 1);
			auto ret = self->IsValid();
			LuaObject::push(L, ret);
			return 1;
		}

		static int ToString(lua_State* L) {
			auto self = LuaObject::checkValue<FPrimaryAssetId*>(L, 1);
			auto ret = self->ToString();
			LuaObject::push(L, ret);
			return 1;
		}

		static int FromString(lua_State* L) {
			auto String = LuaObject::checkValue<FString>(L, 2);
			auto ret = new FPrimaryAssetId;
			*ret = FPrimaryAssetId::FromString(String);
			LuaObject::pushValue(L, ret);
			LuaObject::push(L, String);
			return 2;
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

	void bindAll(lua_State* L) {
		FRotatorWrapper::bind(L);
		FLinearColorWrapper::bind(L);
		FColorWrapper::bind(L);
		FVectorWrapper::bind(L);
		FVector2DWrapper::bind(L);
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

