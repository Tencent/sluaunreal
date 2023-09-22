// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "SluaTestCase.h"
#include "slua.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Misc/AssertionMacros.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"


namespace NS_SLUA {

    class Base {
        LuaClassBody()
    public:
        virtual ~Base() {
            Log::Log("Base object %p had been freed",this);
        }

        void baseFunc1() {
            Log::Log("baseFunc1 call");
        }
    };

    DefLuaClass(Base)
        DefLuaMethod(baseFunc1,&Base::baseFunc1)
    EndDef(Base,&NoConstructor)

    enum class Fruit {
        Apple=1,
        Orange,
        Banana,
    };

    class Foo : public Base {

        LuaClassBody()

    public:
        Foo(int v):value(v) {}
        virtual ~Foo() {
            Log::Log("Foo object %p had been freed",this);
        }

        // constructor function for lua
        // LuaOwnedPtr will hold ptr by lua and auto collect it;
        static LuaOwnedPtr<Foo> create(int v) {
            return new Foo(v);
        }

        // raw ptr not hold by lua, lua not collect it
        static const Foo* getInstance() {
            static Foo s_inst(2048);
            return &s_inst;
        }

		EInputEvent testEnum(const char* v, EInputEvent evt) {
			Log::Log("get text %s, evt is %d", v, evt);
			return evt;
		}

        void bar(const char* v) {
            Log::Log("get text %s and value is %d",v,value);
        }

        static FString getStr() { 
            return FString(UTF8_TO_TCHAR("some text"));
        }

        virtual int virtualFunc() const {
            Log::Log("virtual func from Foo");
            return 1;
        }

        Fruit getFruit() {
            return Fruit::Apple;
        }

        // overriade version
        Fruit getFruit(int) {
            return Fruit::Apple;
        }

        void setCallback(const TFunction<void(int)>& func) {
            callback = func;
        }

        void docall() {
            callback(1024);
            callback = nullptr;
        }

		int get_value() {
			return value;
		}

		void set_value(int v) {
			value = v;
		}

        TFunction<void(int)> callback;
        int value;
    };

    DefLuaClass(Foo,Base)
		DefLuaMethod(testEnum, &Foo::testEnum)
        DefLuaMethod(bar,&Foo::bar)
        DefLuaMethod(getStr,&Foo::getStr)
        DefLuaMethod(getInstance,&Foo::getInstance)
        DefLuaMethod(virtualFunc,&Foo::virtualFunc)
        DefLuaMethod(setCallback,&Foo::setCallback)
        DefLuaMethod(docall,&Foo::docall)
		DefLuaProperty(value,&Foo::get_value,&Foo::set_value,true)
        DefLuaMethod_With_Type(getFruit_1,&Foo::getFruit,Fruit (Foo::*) ())
        DefLuaMethod_With_Type(getFruit_2,&Foo::getFruit,Fruit (Foo::*) (int))
        DefLuaMethod_With_Lambda(helloWorld,false,[]()->void {
            NS_SLUA::Log::Log("Hello World from slua");
        })
    EndDef(Foo,&Foo::create)

	class Box {
	public:
		Box() {
			gi = 1024;
			Log::Log("Box construct");
		}
		~Box() {
			Log::Log("Box destruct");
		}
		int getCount() {
			Log::Log( "Box getCount" );
			return gi++;
		}
		int gi;
	};

	DefLuaClass(Box)
		DefLuaMethod(getCount, &Box::getCount)
	EndDef(Box,nullptr)

    class FooChild : public Foo {

        LuaClassBody()

    public:
        FooChild(int v):Foo(v) {

        }

        void fooChildFunc1() {
            Log::Log("baseFunc1 call");
        }

        static LuaOwnedPtr<FooChild> create(int v) {
            return new FooChild(v);
        }

        virtual int virtualFunc() const {
            Log::Log("virtual func from %s",typeNameFromPtr(this));
            return 2;
        }

        void setEventListener(LuaVar lv) {
            event = lv;
        }

        void eventTrigger() {
			TSharedPtr<Box> ptr = getBoxPtr();
            event.call(ptr);
        }

		void testArrMap(float f, TArray<int> arr, TMap<int, FString> map) {
			Log::Log("f=%f", f);
			for (auto& i : arr) {
				Log::Log("i=%d", i);
			}
			for (TPair<int, FString>& element : map) {
				Log::Log("key=%d, value=%s", element.Key, TCHAR_TO_UTF8(*element.Value));
			}
		}

		int testArrMap2(float f, TArray<int> arr, TMap<int, FString> map) {
			Log::Log("f=%f", f);
			for (auto& i : arr) {
				Log::Log("i=%d", i);
			}
			for (TPair<int, FString>& element : map) {
				Log::Log("key=%d, value=%s", element.Key, TCHAR_TO_UTF8(*element.Value));
			}
			return 100;
		}

		TArray<FString> getTArray() {
			return {"a","b","c","d"};
		}

		TMap<int,FString> getTMap() {
#if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
			return { {1,"s"},{2,"a"},{3,"b"} };
#else
			TMap<int, FString> ret;
			ret.Add(1, "s");
			ret.Add(2, "a");
			ret.Add(3, "b");
			return ret;
#endif
		}

		TSharedPtr<Box> getBoxPtr() {
			return MakeShareable(new Box);
		}

		float hit(const FHitResult& r) {
			float t = r.Time;
			float d = r.Distance;
			Log::Log("Time=%f, Distance=%f", t, d );
			return r.Distance;
		}

        LuaVar event;
    };

    DefLuaClass(FooChild,Foo)
        DefLuaMethod(fooChildFunc1,&FooChild::fooChildFunc1)
        DefLuaMethod(virtualFunc,&FooChild::virtualFunc)
        DefLuaMethod(setEventListener,&FooChild::setEventListener)
        DefLuaMethod(eventTrigger,&FooChild::eventTrigger)
		DefLuaMethod(testArrMap, &FooChild::testArrMap)
		DefLuaMethod(testArrMap2, &FooChild::testArrMap2)
		DefLuaMethod(getTArray, &FooChild::getTArray)
		DefLuaMethod(getTMap, &FooChild::getTMap)
		DefLuaMethod(getBoxPtr, &FooChild::getBoxPtr)
		DefLuaMethod(hit, &FooChild::hit)
    EndDef(FooChild,&FooChild::create)


    class PerfTest {
    public:

        static LuaOwnedPtr<PerfTest> create(int v) {
            return new PerfTest();
        }

        void EmptyFunc() {}

        int ReturnInt() {
            return 1024;
        }

        int ReturnIntWithInt(int i) {
            return i;
        }

        int FuncWithStr(const FString& str) {
            return str.Len();
        }
    };

    DefLuaClass(PerfTest)
        DefLuaMethod(EmptyFunc,&PerfTest::EmptyFunc)
        DefLuaMethod(ReturnInt,&PerfTest::ReturnInt)
        DefLuaMethod(ReturnIntWithInt,&PerfTest::ReturnIntWithInt)
        DefLuaMethod(FuncWithStr,&PerfTest::FuncWithStr)
    EndDef(PerfTest,&PerfTest::create)

	enum TestEnum {
		TE_OK,
		TE_BAD,
		TE_COUNT,
	};
	DefEnum(TestEnum, TE_OK, TE_BAD, TE_COUNT);

	enum class TestEnum2 {
		OK,
		BAD,
		COUNT,
	};
	DefEnumClass(TestEnum2, TestEnum2::OK, TestEnum2::BAD, TestEnum2::COUNT);

	// test http module 

	DefLuaClass(IHttpResponse)
		DefLuaMethod(GetResponseCode, &IHttpResponse::GetResponseCode)
	EndDef(IHttpResponse, nullptr)

	DefLuaClass(IHttpRequest)
		DefLuaMethod(GetResponse, &IHttpRequest::GetResponse)
		DefLuaMethod(SetVerb, &IHttpRequest::SetVerb)
		DefLuaMethod(ProcessRequest, &IHttpRequest::ProcessRequest)
		DefLuaMethod(SetURL, &IHttpRequest::SetURL)
		//DefLuaMethod(SetContent, &IHttpRequest::SetContent)
		//DefLuaMethod(OnRequestProgress, &IHttpRequest::OnRequestProgress)
		//DefLuaMethod(OnProcessRequestComplete, &IHttpRequest::OnProcessRequestComplete)
#if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
		//DefLuaMethod(OnHeaderReceived, &IHttpRequest::OnHeaderReceived)
#endif
	EndDef(IHttpRequest, nullptr)

	DefLuaClass(FHttpModule)
		DefLuaMethod_With_Lambda(Get, true, []()->FHttpModule* {
		return &FHttpModule::Get();
		})
		DefLuaMethod(CreateRequest, &FHttpModule::CreateRequest)
		DefLuaMethod(GetHttpTimeout, &FHttpModule::GetHttpTimeout)

	EndDef(FHttpModule,nullptr)
}

UTestObject::UTestObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

}

USluaTestCase::USluaTestCase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    this->Value=2048;
    using namespace NS_SLUA;
    REG_EXTENSION_METHOD(USluaTestCase,"SetArrayStrEx",&USluaTestCase::SetArrayStrEx);
    REG_EXTENSION_METHOD_IMP(UObject,"IsA",{
        CheckUD(UObject,L,1);
        auto clazz = LuaObject::checkUD<UClass>(L,2);
        bool ret = UD->IsA(clazz);
        return LuaObject::push(L,ret);
    });  
    REG_EXTENSION_METHOD(USluaTestCase, "constRetFunc", &USluaTestCase::constRetFunc);
	REG_EXTENSION_METHOD(USluaTestCase, "inlineFunc", &USluaTestCase::inlineFunc);

	info.obj = this;
	info.name = UTF8_TO_TCHAR("女战士");
	info.id = 1001001;
	info.level = 12;
	info.pos = { 1,2,3,4 };
	info.ids = { 1,2,3,4 };

	userInfo.Add(1, info);

	weakptr = NewObject<UTestObject>(this,TEXT("TestUObject"));
}

void USluaTestCase::setupfoo(UObject* obj) {
	foos.Add(obj);
	foos.Add(obj);
	foos.Add(obj);
	foos.Add(obj);
}

void USluaTestCase::delfoo() {
	foos.Empty();
}

const FUserInfo& USluaTestCase::GetUserInfo() {
	return info;
}

TArray<int> USluaTestCase::GetArray() {
    TArray<int> array={1,0,2,4,2,0,4,8};
    return array;
}

TMap<int, FString> USluaTestCase::GetMap() {
	TMap<int, FString> FruitMap;

	FruitMap.Add(5, TEXT("Banana"));
	FruitMap.Add(2, TEXT("Grapefruit"));
	FruitMap.Add(7, TEXT("Pineapple"));
	FruitMap.Add(2, TEXT("Grapefruit"));
	FruitMap.Add(7, TEXT("Pineapple"));
	return FruitMap;
}

TArray<FString> USluaTestCase::GetArrayStr() {
    TArray<FString> array={"hello","world","nihao"};
    return array;
}

void USluaTestCase::SetArrayStr(const TArray<FString>& array) {
    for(auto it:array) {
        NS_SLUA::Log::Log("output array = %s", TCHAR_TO_UTF8(*it));
    }
}

void USluaTestCase::SetArrayStrEx(const TArray<FString>& array) {
    for(auto it:array) {
        NS_SLUA::Log::Log("output array = %s", TCHAR_TO_UTF8(*it));
    }
}

FVector USluaTestCase::TestStruct(FVector v, ESlateVisibility e, FVector& v2, int i, int& i2, FString str) {
	NS_SLUA::Log::Log("v.X=%f, v.Y=%f, v.Z=%f", v.X, v.Y, v.Z);
	NS_SLUA::Log::Log("i = %d", i);
	NS_SLUA::Log::Log("s = %s", TCHAR_TO_UTF8(*str));
	NS_SLUA::Log::Log("e = %d", (int)e);
	v2 = v * 2;
    i2 = i;
	return v2 * 2;
}

int USluaTestCase::TestInt_int(int i) {
	NS_SLUA::Log::Log("TestInt_int i=%d", i);
	return i * 2;
}

FString USluaTestCase::TestIntStr_Str(int i, FString s) {
	NS_SLUA::Log::Log("TestIntStr_Str i=%d, s=%s", i, TCHAR_TO_UTF8(*s));
	return FString(UTF8_TO_TCHAR("TestIntStr_Str"));
}

ESlateVisibility USluaTestCase::TestIntStrEnum_Enum(int i, FString s, ESlateVisibility e) {
	NS_SLUA::Log::Log("TestIntStrEnum_Enum i=%d, s=%s, e=%d", i, TCHAR_TO_UTF8(*s), (int)e);
	return ESlateVisibility((int)e + 1);
}

TArray<int> USluaTestCase::TestIntStrEnum_Arr(int i, FString s, ESlateVisibility e) {
	NS_SLUA::Log::Log("TestIntStrEnum_Arr i=%d, s=%s, e=%d", i, TCHAR_TO_UTF8(*s), (int)e);
	TArray<int> arr = { 123, 321 };
	return arr;
}

void USluaTestCase::TestOIntOStrOEnum(int i, int& oi, FString s, FString& os, ESlateVisibility e, ESlateVisibility& oe) {
	NS_SLUA::Log::Log("TestOIntOStrOEnum i=%d, s=%s, e=%d", i, TCHAR_TO_UTF8(*s), (int)e);
	NS_SLUA::Log::Log("TestOIntOStrOEnum oi=%d, os=%s, oe=%d", oi, TCHAR_TO_UTF8(*os), (int)oe);
}

void USluaTestCase::TwoArgs(FString a,int b,float c,FString d,UObject* widget) {
	NS_SLUA::Log::Log("We get 5 args %s,%d,%f,%s,%p", TCHAR_TO_UTF8(*a),b,c,TCHAR_TO_UTF8(*d),widget);    
}

void USluaTestCase::SetButton(UUserWidget* widget) {
    NS_SLUA::Log::Log("Set Button %p",widget);
}

FSlateBrush USluaTestCase::GetBrush() {
    return FSlateBrush();
}

void USluaTestCase::StaticFunc() {
    NS_SLUA::Log::Log("static function call");
}

static USluaTestCase::FOnAssetClassLoaded s_onloaded;
void USluaTestCase::LoadAssetClass(FOnAssetClassLoaded OnLoaded) {
    s_onloaded = OnLoaded;
}

void USluaTestCase::callback() {
    s_onloaded.ExecuteIfBound(1024);
}

void USluaTestCase::EmptyFunc() {}

int USluaTestCase::ReturnInt() {
    return 1024;
}

int USluaTestCase::ReturnIntWithInt(int i) {
    return i;
}

int USluaTestCase::FuncWithStr(FString str) {
    return str.Len();
}

void USluaTestCase::TestUnicastDelegate(FString str)
{
    int32 retVal = OnTestGetCount.IsBound() ? OnTestGetCount.Execute(str) : -1;
    NS_SLUA::Log::Log("TestUnicastDelegate retVal=%d", retVal);
}