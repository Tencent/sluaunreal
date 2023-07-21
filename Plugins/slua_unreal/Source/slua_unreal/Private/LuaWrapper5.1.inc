
    static UScriptStruct* FIntPointStruct = nullptr;
    static UScriptStruct* FLinearColorStruct = nullptr;
    static UScriptStruct* FColorStruct = nullptr;
    static UScriptStruct* FRandomStreamStruct = nullptr;
    static UScriptStruct* FGuidStruct = nullptr;
    static UScriptStruct* FInterpCurvePointVector2DStruct = nullptr;
    static UScriptStruct* FInterpCurvePointVectorStruct = nullptr;
    static UScriptStruct* FInterpCurvePointQuatStruct = nullptr;
    static UScriptStruct* FInterpCurvePointTwoVectorsStruct = nullptr;
    static UScriptStruct* FInterpCurvePointLinearColorStruct = nullptr;
    static UScriptStruct* FFloatRangeBoundStruct = nullptr;
    static UScriptStruct* FFloatRangeStruct = nullptr;
    static UScriptStruct* FDoubleRangeBoundStruct = nullptr;
    static UScriptStruct* FDoubleRangeStruct = nullptr;
    static UScriptStruct* FInt32RangeBoundStruct = nullptr;
    static UScriptStruct* FInt32RangeStruct = nullptr;
    static UScriptStruct* FFloatIntervalStruct = nullptr;
    static UScriptStruct* FDoubleIntervalStruct = nullptr;
    static UScriptStruct* FInt32IntervalStruct = nullptr;
    static UScriptStruct* FFrameNumberStruct = nullptr;
    static UScriptStruct* FPrimaryAssetTypeStruct = nullptr;
    static UScriptStruct* FPrimaryAssetIdStruct = nullptr;
    static UScriptStruct* FDateTimeStruct = nullptr;
    static UScriptStruct* FTestUninitializedScriptStructMembersTestStruct = nullptr;
    static UScriptStruct* FTopLevelAssetPathStruct = nullptr;
    static UScriptStruct* FVectorStruct = nullptr;
    static UScriptStruct* FPlaneStruct = nullptr;
    static UScriptStruct* FQuatStruct = nullptr;
    static UScriptStruct* FTransformStruct = nullptr;
    static UScriptStruct* FMatrixStruct = nullptr;
    static UScriptStruct* FSoftObjectPathStruct = nullptr;
    static UScriptStruct* FSoftClassPathStruct = nullptr;

    typedef void(*pushStructFunction)(lua_State* L, FStructProperty* p, uint8* parms);
    typedef void* (*checkStructFunction)(lua_State* L, FStructProperty* p, uint8* parms, int i);

    TMap<UScriptStruct*, pushStructFunction> _pushStructMap;
    TMap<UScriptStruct*, checkStructFunction> _checkStructMap;

    static inline FIntPoint* __newFIntPoint() {
        return new FIntPoint();
    }

    static void __pushFIntPoint(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFIntPoint();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FIntPoint>(L, "FIntPoint", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFIntPoint(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FIntPoint*>(L, i);
        if (!v) {
            luaL_error(L, "check FIntPoint nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FLinearColor* __newFLinearColor() {
        return new FLinearColor();
    }

    static void __pushFLinearColor(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFLinearColor();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FLinearColor>(L, "FLinearColor", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFLinearColor(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FLinearColor*>(L, i);
        if (!v) {
            luaL_error(L, "check FLinearColor nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FColor* __newFColor() {
        return new FColor();
    }

    static void __pushFColor(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFColor();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FColor>(L, "FColor", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFColor(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FColor*>(L, i);
        if (!v) {
            luaL_error(L, "check FColor nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FRandomStream* __newFRandomStream() {
        return new FRandomStream();
    }

    static void __pushFRandomStream(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFRandomStream();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FRandomStream>(L, "FRandomStream", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFRandomStream(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FRandomStream*>(L, i);
        if (!v) {
            luaL_error(L, "check FRandomStream nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FGuid* __newFGuid() {
        return new FGuid();
    }

    static void __pushFGuid(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFGuid();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FGuid>(L, "FGuid", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFGuid(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FGuid*>(L, i);
        if (!v) {
            luaL_error(L, "check FGuid nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInterpCurvePointVector2D* __newFInterpCurvePointVector2D() {
        return new FInterpCurvePointVector2D();
    }

    static void __pushFInterpCurvePointVector2D(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInterpCurvePointVector2D();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInterpCurvePointVector2D>(L, "FInterpCurvePointVector2D", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInterpCurvePointVector2D(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInterpCurvePointVector2D*>(L, i);
        if (!v) {
            luaL_error(L, "check FInterpCurvePointVector2D nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInterpCurvePointVector* __newFInterpCurvePointVector() {
        return new FInterpCurvePointVector();
    }

    static void __pushFInterpCurvePointVector(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInterpCurvePointVector();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInterpCurvePointVector>(L, "FInterpCurvePointVector", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInterpCurvePointVector(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInterpCurvePointVector*>(L, i);
        if (!v) {
            luaL_error(L, "check FInterpCurvePointVector nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInterpCurvePointQuat* __newFInterpCurvePointQuat() {
        return new FInterpCurvePointQuat();
    }

    static void __pushFInterpCurvePointQuat(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInterpCurvePointQuat();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInterpCurvePointQuat>(L, "FInterpCurvePointQuat", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInterpCurvePointQuat(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInterpCurvePointQuat*>(L, i);
        if (!v) {
            luaL_error(L, "check FInterpCurvePointQuat nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInterpCurvePointTwoVectors* __newFInterpCurvePointTwoVectors() {
        return new FInterpCurvePointTwoVectors();
    }

    static void __pushFInterpCurvePointTwoVectors(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInterpCurvePointTwoVectors();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInterpCurvePointTwoVectors>(L, "FInterpCurvePointTwoVectors", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInterpCurvePointTwoVectors(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInterpCurvePointTwoVectors*>(L, i);
        if (!v) {
            luaL_error(L, "check FInterpCurvePointTwoVectors nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInterpCurvePointLinearColor* __newFInterpCurvePointLinearColor() {
        return new FInterpCurvePointLinearColor();
    }

    static void __pushFInterpCurvePointLinearColor(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInterpCurvePointLinearColor();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInterpCurvePointLinearColor>(L, "FInterpCurvePointLinearColor", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInterpCurvePointLinearColor(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInterpCurvePointLinearColor*>(L, i);
        if (!v) {
            luaL_error(L, "check FInterpCurvePointLinearColor nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FFloatRangeBound* __newFFloatRangeBound() {
        return new FFloatRangeBound();
    }

    static void __pushFFloatRangeBound(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFFloatRangeBound();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFFloatRangeBound(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FFloatRangeBound*>(L, i);
        if (!v) {
            luaL_error(L, "check FFloatRangeBound nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FFloatRange* __newFFloatRange() {
        return new FFloatRange();
    }

    static void __pushFFloatRange(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFFloatRange();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FFloatRange>(L, "FFloatRange", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFFloatRange(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FFloatRange*>(L, i);
        if (!v) {
            luaL_error(L, "check FFloatRange nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FDoubleRangeBound* __newFDoubleRangeBound() {
        return new FDoubleRangeBound();
    }

    static void __pushFDoubleRangeBound(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFDoubleRangeBound();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFDoubleRangeBound(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FDoubleRangeBound*>(L, i);
        if (!v) {
            luaL_error(L, "check FDoubleRangeBound nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FDoubleRange* __newFDoubleRange() {
        return new FDoubleRange();
    }

    static void __pushFDoubleRange(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFDoubleRange();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FDoubleRange>(L, "FDoubleRange", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFDoubleRange(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FDoubleRange*>(L, i);
        if (!v) {
            luaL_error(L, "check FDoubleRange nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInt32RangeBound* __newFInt32RangeBound() {
        return new FInt32RangeBound();
    }

    static void __pushFInt32RangeBound(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInt32RangeBound();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInt32RangeBound(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInt32RangeBound*>(L, i);
        if (!v) {
            luaL_error(L, "check FInt32RangeBound nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInt32Range* __newFInt32Range() {
        return new FInt32Range();
    }

    static void __pushFInt32Range(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInt32Range();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInt32Range>(L, "FInt32Range", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInt32Range(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInt32Range*>(L, i);
        if (!v) {
            luaL_error(L, "check FInt32Range nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FFloatInterval* __newFFloatInterval() {
        return new FFloatInterval();
    }

    static void __pushFFloatInterval(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFFloatInterval();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FFloatInterval>(L, "FFloatInterval", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFFloatInterval(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FFloatInterval*>(L, i);
        if (!v) {
            luaL_error(L, "check FFloatInterval nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FDoubleInterval* __newFDoubleInterval() {
        return new FDoubleInterval();
    }

    static void __pushFDoubleInterval(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFDoubleInterval();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FDoubleInterval>(L, "FDoubleInterval", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFDoubleInterval(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FDoubleInterval*>(L, i);
        if (!v) {
            luaL_error(L, "check FDoubleInterval nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInt32Interval* __newFInt32Interval() {
        return new FInt32Interval();
    }

    static void __pushFInt32Interval(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInt32Interval();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInt32Interval>(L, "FInt32Interval", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInt32Interval(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInt32Interval*>(L, i);
        if (!v) {
            luaL_error(L, "check FInt32Interval nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FFrameNumber* __newFFrameNumber() {
        return new FFrameNumber();
    }

    static void __pushFFrameNumber(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFFrameNumber();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FFrameNumber>(L, "FFrameNumber", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFFrameNumber(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FFrameNumber*>(L, i);
        if (!v) {
            luaL_error(L, "check FFrameNumber nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FPrimaryAssetType* __newFPrimaryAssetType() {
        return new FPrimaryAssetType();
    }

    static void __pushFPrimaryAssetType(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFPrimaryAssetType();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FPrimaryAssetType>(L, "FPrimaryAssetType", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFPrimaryAssetType(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FPrimaryAssetType*>(L, i);
        if (!v) {
            luaL_error(L, "check FPrimaryAssetType nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FPrimaryAssetId* __newFPrimaryAssetId() {
        return new FPrimaryAssetId();
    }

    static void __pushFPrimaryAssetId(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFPrimaryAssetId();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFPrimaryAssetId(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FPrimaryAssetId*>(L, i);
        if (!v) {
            luaL_error(L, "check FPrimaryAssetId nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FDateTime* __newFDateTime() {
        return new FDateTime();
    }

    static void __pushFDateTime(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFDateTime();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FDateTime>(L, "FDateTime", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFDateTime(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FDateTime*>(L, i);
        if (!v) {
            luaL_error(L, "check FDateTime nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FTestUninitializedScriptStructMembersTest* __newFTestUninitializedScriptStructMembersTest() {
        return new FTestUninitializedScriptStructMembersTest();
    }

    static void __pushFTestUninitializedScriptStructMembersTest(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFTestUninitializedScriptStructMembersTest();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FTestUninitializedScriptStructMembersTest>(L, "FTestUninitializedScriptStructMembersTest", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFTestUninitializedScriptStructMembersTest(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FTestUninitializedScriptStructMembersTest*>(L, i);
        if (!v) {
            luaL_error(L, "check FTestUninitializedScriptStructMembersTest nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FTopLevelAssetPath* __newFTopLevelAssetPath() {
        return new FTopLevelAssetPath();
    }

    static void __pushFTopLevelAssetPath(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFTopLevelAssetPath();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FTopLevelAssetPath>(L, "FTopLevelAssetPath", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFTopLevelAssetPath(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FTopLevelAssetPath*>(L, i);
        if (!v) {
            luaL_error(L, "check FTopLevelAssetPath nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FVector* __newFVector() {
        return new FVector();
    }

    static void __pushFVector(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFVector();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FVector>(L, "FVector", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFVector(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FVector*>(L, i);
        if (!v) {
            luaL_error(L, "check FVector nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FPlane* __newFPlane() {
        return new FPlane();
    }

    static void __pushFPlane(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFPlane();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FPlane>(L, "FPlane", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFPlane(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FPlane*>(L, i);
        if (!v) {
            luaL_error(L, "check FPlane nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FQuat* __newFQuat() {
        return new FQuat();
    }

    static void __pushFQuat(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFQuat();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FQuat>(L, "FQuat", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFQuat(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FQuat*>(L, i);
        if (!v) {
            luaL_error(L, "check FQuat nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FTransform* __newFTransform() {
        return new FTransform();
    }

    static void __pushFTransform(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFTransform();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FTransform>(L, "FTransform", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFTransform(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FTransform*>(L, i);
        if (!v) {
            luaL_error(L, "check FTransform nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FMatrix* __newFMatrix() {
        return new FMatrix();
    }

    static void __pushFMatrix(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFMatrix();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FMatrix>(L, "FMatrix", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFMatrix(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FMatrix*>(L, i);
        if (!v) {
            luaL_error(L, "check FMatrix nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FSoftObjectPath* __newFSoftObjectPath() {
        return new FSoftObjectPath();
    }

    static void __pushFSoftObjectPath(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFSoftObjectPath();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FSoftObjectPath>(L, "FSoftObjectPath", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFSoftObjectPath(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FSoftObjectPath*>(L, i);
        if (!v) {
            luaL_error(L, "check FSoftObjectPath nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FSoftClassPath* __newFSoftClassPath() {
        return new FSoftClassPath();
    }

    static void __pushFSoftClassPath(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFSoftClassPath();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FSoftClassPath>(L, "FSoftClassPath", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFSoftClassPath(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FSoftClassPath*>(L, i);
        if (!v) {
            luaL_error(L, "check FSoftClassPath nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    struct FIntPointWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FIntPoint();
                LuaObject::push<FIntPoint>(L, "FIntPoint", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FIntPoint(_a0Val);
                LuaObject::push<FIntPoint>(L, "FIntPoint", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntPoint() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FIntPoint);
            auto ret = __newFIntPoint();
            *ret = *self;
            LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FIntPoint);
            SLUA_GCSTRUCT(FIntPoint);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FIntPoint);
            if (LuaObject::matchType(L, 2, "FIntPoint")) {
                auto Other = LuaObject::checkValue<FIntPoint*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = (*self == OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
            return 1;
        }

        static int __add(lua_State* L) {
            CheckSelf(FIntPoint);
            if (LuaObject::matchType(L, 2, "FIntPoint")) {
                auto Other = LuaObject::checkValue<FIntPoint*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntPoint();
                *ret = (*self + OtherRef);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntPoint operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __sub(lua_State* L) {
            CheckSelf(FIntPoint);
            if (LuaObject::matchType(L, 2, "FIntPoint")) {
                auto Other = LuaObject::checkValue<FIntPoint*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntPoint();
                *ret = (*self - OtherRef);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntPoint operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __mul(lua_State* L) {
            CheckSelf(FIntPoint);
            if (LuaObject::matchType(L, 2, "FIntPoint")) {
                auto Other = LuaObject::checkValue<FIntPoint*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntPoint();
                *ret = (*self * OtherRef);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntPoint operator__mul error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __div(lua_State* L) {
            CheckSelf(FIntPoint);
            if (LuaObject::matchType(L, 2, "FIntPoint")) {
                auto Other = LuaObject::checkValue<FIntPoint*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntPoint();
                *ret = (*self / OtherRef);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntPoint operator__div error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int get_ZeroValue(lua_State* L) {
            auto& ZeroValue = FIntPoint::ZeroValue;
            LuaObject::push<FIntPoint>(L, "FIntPoint", &ZeroValue);
            return 1;
        }

        static int get_NoneValue(lua_State* L) {
            auto& NoneValue = FIntPoint::NoneValue;
            LuaObject::push<FIntPoint>(L, "FIntPoint", &NoneValue);
            return 1;
        }

        static int ComponentMin(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FIntPoint);
                auto Other = LuaObject::checkValue<FIntPoint*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntPoint();
                *ret = self->ComponentMin(OtherRef);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntPoint::ComponentMin error, argc=%d", argc);
            return 0;
        }

        static int ComponentMax(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FIntPoint);
                auto Other = LuaObject::checkValue<FIntPoint*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntPoint();
                *ret = self->ComponentMax(OtherRef);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntPoint::ComponentMax error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FIntPoint);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FIntPoint::ToString error, argc=%d", argc);
            return 0;
        }

        static int DivideAndRoundUp(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto lhs = LuaObject::checkValue<FIntPoint*>(L, 1);
                auto lhsVal = *lhs;
                auto Divisor = LuaObject::checkValue<FIntPoint*>(L, 2);
                auto DivisorVal = *Divisor;
                auto ret = __newFIntPoint();
                *ret = FIntPoint::DivideAndRoundUp(lhsVal, DivisorVal);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntPoint::DivideAndRoundUp error, argc=%d", argc);
            return 0;
        }

        static int Num(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = FIntPoint::Num();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FIntPoint::Num error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FIntPoint");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__div", __div);
            LuaObject::addField(L, "ZeroValue", get_ZeroValue, nullptr, false);
            LuaObject::addField(L, "NoneValue", get_NoneValue, nullptr, false);
            LuaObject::addMethod(L, "ComponentMin", ComponentMin, true);
            LuaObject::addMethod(L, "ComponentMax", ComponentMax, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "DivideAndRoundUp", DivideAndRoundUp, false);
            LuaObject::addMethod(L, "Num", Num, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FIntPoint", __ctor, __gc);
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

        static int clone(lua_State* L) {
            CheckSelf(FLinearColor);
            auto ret = __newFLinearColor();
            *ret = *self;
            LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FLinearColor);
            SLUA_GCSTRUCT(FLinearColor);
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FLinearColor);
            if (LuaObject::matchType(L, 2, "FLinearColor")) {
                auto ColorB = LuaObject::checkValue<FLinearColor*>(L, 2);
                if (!ColorB) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!ColorB) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!ColorB) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!ColorB) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!ColorB) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ColorBRef = *ColorB;
                auto ret = (*self == ColorBRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
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
                if (!ColorB) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int QuantizeFloor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FLinearColor);
                auto ret = __newFColor();
                *ret = self->QuantizeFloor();
                LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FLinearColor::QuantizeFloor error, argc=%d", argc);
            return 0;
        }

        static int ToFColorSRGB(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FLinearColor);
                auto ret = __newFColor();
                *ret = self->ToFColorSRGB();
                LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FLinearColor::ToFColorSRGB error, argc=%d", argc);
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
                if (!Color) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Color) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ColorRef = *Color;
                auto ret = __newFLinearColor();
                *ret = FLinearColor::FromPow22Color(ColorRef);
                LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FLinearColor::FromPow22Color error, argc=%d", argc);
            return 0;
        }

        static int MakeFromHSV8(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto H = LuaObject::checkValue<int>(L, 1);
                auto S = LuaObject::checkValue<int>(L, 2);
                auto V = LuaObject::checkValue<int>(L, 3);
                auto ret = __newFLinearColor();
                *ret = FLinearColor::MakeFromHSV8(H, S, V);
                LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FLinearColor::MakeFromHSV8 error, argc=%d", argc);
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

        static int MakeRandomSeededColor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Seed = LuaObject::checkValue<int>(L, 1);
                auto ret = __newFLinearColor();
                *ret = FLinearColor::MakeRandomSeededColor(Seed);
                LuaObject::push<FLinearColor>(L, "FLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FLinearColor::MakeRandomSeededColor error, argc=%d", argc);
            return 0;
        }

        static int Dist(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto V1 = LuaObject::checkValue<FLinearColor*>(L, 1);
                if (!V1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& V1Ref = *V1;
                auto V2 = LuaObject::checkValue<FLinearColor*>(L, 2);
                if (!V2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!From) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& FromRef = *From;
                auto To = LuaObject::checkValue<FLinearColor*>(L, 2);
                if (!To) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int Clamp01NansTo0(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto InValue = LuaObject::checkValue<float>(L, 1);
                auto ret = FLinearColor::Clamp01NansTo0(InValue);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FLinearColor::Clamp01NansTo0 error, argc=%d", argc);
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
            LuaObject::addMethod(L, "QuantizeRound", QuantizeRound, true);
            LuaObject::addMethod(L, "QuantizeFloor", QuantizeFloor, true);
            LuaObject::addMethod(L, "ToFColorSRGB", ToFColorSRGB, true);
            LuaObject::addMethod(L, "ToFColor", ToFColor, true);
            LuaObject::addMethod(L, "Desaturate", Desaturate, true);
            LuaObject::addMethod(L, "GetLuminance", GetLuminance, true);
            LuaObject::addMethod(L, "GetMax", GetMax, true);
            LuaObject::addMethod(L, "IsAlmostBlack", IsAlmostBlack, true);
            LuaObject::addMethod(L, "GetMin", GetMin, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "InitFromString", InitFromString, true);
            LuaObject::addMethod(L, "FromSRGBColor", FromSRGBColor, false);
            LuaObject::addMethod(L, "FromPow22Color", FromPow22Color, false);
            LuaObject::addMethod(L, "MakeFromHSV8", MakeFromHSV8, false);
            LuaObject::addMethod(L, "MakeRandomColor", MakeRandomColor, false);
            LuaObject::addMethod(L, "MakeFromColorTemperature", MakeFromColorTemperature, false);
            LuaObject::addMethod(L, "MakeRandomSeededColor", MakeRandomSeededColor, false);
            LuaObject::addMethod(L, "Dist", Dist, false);
            LuaObject::addMethod(L, "LerpUsingHSV", LerpUsingHSV, false);
            LuaObject::addMethod(L, "Clamp01NansTo0", Clamp01NansTo0, false);
            LuaObject::addMethod(L, "clone", clone, true);
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
                auto InG = LuaObject::checkValue<int>(L, 3);
                auto InB = LuaObject::checkValue<int>(L, 4);
                auto InA = LuaObject::checkValue<int>(L, 5);
                auto self = new FColor(InR, InG, InB, InA);
                LuaObject::push<FColor>(L, "FColor", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FColor() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FColor);
            auto ret = __newFColor();
            *ret = *self;
            LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FColor);
            SLUA_GCSTRUCT(FColor);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FColor);
            if (LuaObject::matchType(L, 2, "FColor")) {
                auto C = LuaObject::checkValue<FColor*>(L, 2);
                if (!C) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                auto ret = __newFColor();
                *ret = self->WithAlpha(Alpha);
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

        static int MakeRandomSeededColor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Seed = LuaObject::checkValue<int>(L, 1);
                auto ret = __newFColor();
                *ret = FColor::MakeRandomSeededColor(Seed);
                LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FColor::MakeRandomSeededColor error, argc=%d", argc);
            return 0;
        }

        static int QuantizeUNormFloatTo8(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto UnitFloat = LuaObject::checkValue<float>(L, 1);
                auto ret = FColor::QuantizeUNormFloatTo8(UnitFloat);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FColor::QuantizeUNormFloatTo8 error, argc=%d", argc);
            return 0;
        }

        static int QuantizeUNormFloatTo16(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto UnitFloat = LuaObject::checkValue<float>(L, 1);
                auto ret = FColor::QuantizeUNormFloatTo16(UnitFloat);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FColor::QuantizeUNormFloatTo16 error, argc=%d", argc);
            return 0;
        }

        static int DequantizeUNorm8ToFloat(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value8 = LuaObject::checkValue<int>(L, 1);
                auto ret = FColor::DequantizeUNorm8ToFloat(Value8);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FColor::DequantizeUNorm8ToFloat error, argc=%d", argc);
            return 0;
        }

        static int DequantizeUNorm16ToFloat(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value16 = LuaObject::checkValue<int>(L, 1);
                auto ret = FColor::DequantizeUNorm16ToFloat(Value16);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FColor::DequantizeUNorm16ToFloat error, argc=%d", argc);
            return 0;
        }

        static int Requantize10to8(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value10 = LuaObject::checkValue<int>(L, 1);
                auto ret = FColor::Requantize10to8(Value10);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FColor::Requantize10to8 error, argc=%d", argc);
            return 0;
        }

        static int Requantize16to8(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value16 = LuaObject::checkValue<int>(L, 1);
                auto ret = FColor::Requantize16to8(Value16);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FColor::Requantize16to8 error, argc=%d", argc);
            return 0;
        }

        static int MakeRequantizeFrom1010102(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 4) {
                auto R = LuaObject::checkValue<int>(L, 1);
                auto G = LuaObject::checkValue<int>(L, 2);
                auto B = LuaObject::checkValue<int>(L, 3);
                auto A = LuaObject::checkValue<int>(L, 4);
                auto ret = __newFColor();
                *ret = FColor::MakeRequantizeFrom1010102(R, G, B, A);
                LuaObject::push<FColor>(L, "FColor", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FColor::MakeRequantizeFrom1010102 error, argc=%d", argc);
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
            LuaObject::addMethod(L, "MakeRandomSeededColor", MakeRandomSeededColor, false);
            LuaObject::addMethod(L, "QuantizeUNormFloatTo8", QuantizeUNormFloatTo8, false);
            LuaObject::addMethod(L, "QuantizeUNormFloatTo16", QuantizeUNormFloatTo16, false);
            LuaObject::addMethod(L, "DequantizeUNorm8ToFloat", DequantizeUNorm8ToFloat, false);
            LuaObject::addMethod(L, "DequantizeUNorm16ToFloat", DequantizeUNorm16ToFloat, false);
            LuaObject::addMethod(L, "Requantize10to8", Requantize10to8, false);
            LuaObject::addMethod(L, "Requantize16to8", Requantize16to8, false);
            LuaObject::addMethod(L, "MakeRequantizeFrom1010102", MakeRequantizeFrom1010102, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FColor", __ctor, __gc);
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

        static int clone(lua_State* L) {
            CheckSelf(FRandomStream);
            auto ret = __newFRandomStream();
            *ret = *self;
            LuaObject::push<FRandomStream>(L, "FRandomStream", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FRandomStream);
            SLUA_GCSTRUCT(FRandomStream);
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
                if (!Dir) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Dir) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FRandomStream);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FRandomStream::ToString error, argc=%d", argc);
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
            LuaObject::addMethod(L, "VRand", VRand, true);
            LuaObject::addMethod(L, "VRandCone", VRandCone, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "clone", clone, true);
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
            if (argc == 2) {
                auto InGuidStr = LuaObject::checkValue<FString>(L, 2);
                auto self = new FGuid(InGuidStr);
                LuaObject::push<FGuid>(L, "FGuid", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 5) {
                auto InA = LuaObject::checkValue<int>(L, 2);
                auto InB = LuaObject::checkValue<int>(L, 3);
                auto InC = LuaObject::checkValue<int>(L, 4);
                auto InD = LuaObject::checkValue<int>(L, 5);
                auto self = new FGuid(InA, InB, InC, InD);
                LuaObject::push<FGuid>(L, "FGuid", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FGuid() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FGuid);
            auto ret = __newFGuid();
            *ret = *self;
            LuaObject::push<FGuid>(L, "FGuid", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FGuid);
            SLUA_GCSTRUCT(FGuid);
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

        static int AppendString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FGuid);
                auto Out = LuaObject::checkValue<FString>(L, 2);
                auto Format = LuaObject::checkValue<int>(L, 3);
                auto FormatVal = (EGuidFormats)Format;
                self->AppendString(Out, FormatVal);
                LuaObject::push(L, Out);
                return 1;
            }
            luaL_error(L, "call FGuid::AppendString error, argc=%d", argc);
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
                if (!OutGuid) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!OutGuid) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            LuaObject::addMethod(L, "AppendString", AppendString, true);
            LuaObject::addMethod(L, "NewGuid", NewGuid, false);
            LuaObject::addMethod(L, "Parse", Parse, false);
            LuaObject::addMethod(L, "ParseExact", ParseExact, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FGuid", __ctor, __gc);
        }

    };

    struct FInterpCurvePointVector2DWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FInterpCurvePointVector2D() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FInterpCurvePointVector2D);
            auto ret = __newFInterpCurvePointVector2D();
            *ret = *self;
            LuaObject::push<FInterpCurvePointVector2D>(L, "FInterpCurvePointVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInterpCurvePointVector2D);
            SLUA_GCSTRUCT(FInterpCurvePointVector2D);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointVector2D");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointVector2D", __ctor, __gc);
        }

    };

    struct FInterpCurvePointVectorWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FInterpCurvePointVector() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto ret = __newFInterpCurvePointVector();
            *ret = *self;
            LuaObject::push<FInterpCurvePointVector>(L, "FInterpCurvePointVector", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInterpCurvePointVector);
            SLUA_GCSTRUCT(FInterpCurvePointVector);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newTypeWithBase(L, "FInterpCurvePointVector", std::initializer_list<const char*>{ "TVector" });
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointVector", __ctor, __gc);
        }

    };

    struct FInterpCurvePointQuatWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FInterpCurvePointQuat() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto ret = __newFInterpCurvePointQuat();
            *ret = *self;
            LuaObject::push<FInterpCurvePointQuat>(L, "FInterpCurvePointQuat", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInterpCurvePointQuat);
            SLUA_GCSTRUCT(FInterpCurvePointQuat);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newTypeWithBase(L, "FInterpCurvePointQuat", std::initializer_list<const char*>{ "TQuat" });
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointQuat", __ctor, __gc);
        }

    };

    struct FInterpCurvePointTwoVectorsWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FInterpCurvePointTwoVectors() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FInterpCurvePointTwoVectors);
            auto ret = __newFInterpCurvePointTwoVectors();
            *ret = *self;
            LuaObject::push<FInterpCurvePointTwoVectors>(L, "FInterpCurvePointTwoVectors", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInterpCurvePointTwoVectors);
            SLUA_GCSTRUCT(FInterpCurvePointTwoVectors);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointTwoVectors");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointTwoVectors", __ctor, __gc);
        }

    };

    struct FInterpCurvePointLinearColorWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FInterpCurvePointLinearColor() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto ret = __newFInterpCurvePointLinearColor();
            *ret = *self;
            LuaObject::push<FInterpCurvePointLinearColor>(L, "FInterpCurvePointLinearColor", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInterpCurvePointLinearColor);
            SLUA_GCSTRUCT(FInterpCurvePointLinearColor);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newTypeWithBase(L, "FInterpCurvePointLinearColor", std::initializer_list<const char*>{ "FLinearColor" });
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointLinearColor", __ctor, __gc);
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
                auto InValue = LuaObject::checkValue<float>(L, 2);
                auto self = new FFloatRangeBound(InValue);
                LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFloatRangeBound() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FFloatRangeBound);
            auto ret = __newFFloatRangeBound();
            *ret = *self;
            LuaObject::push<FFloatRangeBound>(L, "FFloatRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FFloatRangeBound);
            SLUA_GCSTRUCT(FFloatRangeBound);
            return 0;
        }

        static int Exclusive(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value = LuaObject::checkValue<int>(L, 1);
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
                auto Value = LuaObject::checkValue<int>(L, 1);
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
                if (!Bound) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FFloatRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            LuaObject::addMethod(L, "clone", clone, true);
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
                auto A = LuaObject::checkValue<int>(L, 2);
                auto self = new FFloatRange(A);
                LuaObject::push<FFloatRange>(L, "FFloatRange", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto A = LuaObject::checkValue<int>(L, 2);
                auto B = LuaObject::checkValue<int>(L, 3);
                auto self = new FFloatRange(A, B);
                LuaObject::push<FFloatRange>(L, "FFloatRange", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFloatRange() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FFloatRange);
            auto ret = __newFFloatRange();
            *ret = *self;
            LuaObject::push<FFloatRange>(L, "FFloatRange", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FFloatRange);
            SLUA_GCSTRUCT(FFloatRange);
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
                auto Value = LuaObject::checkValue<int>(L, 1);
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
                auto Value = LuaObject::checkValue<int>(L, 1);
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
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FFloatRange", __ctor, __gc);
        }

    };

    struct FDoubleRangeBoundWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FDoubleRangeBound();
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto InValue = LuaObject::checkValue<float>(L, 2);
                auto InValueVal = (double)InValue;
                auto self = new FDoubleRangeBound(InValueVal);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FDoubleRangeBound);
            auto ret = __newFDoubleRangeBound();
            *ret = *self;
            LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FDoubleRangeBound);
            SLUA_GCSTRUCT(FDoubleRangeBound);
            return 0;
        }

        static int Exclusive(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value = LuaObject::checkValue<int>(L, 1);
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::Exclusive(Value);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::Exclusive error, argc=%d", argc);
            return 0;
        }

        static int Inclusive(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value = LuaObject::checkValue<int>(L, 1);
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::Inclusive(Value);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::Inclusive error, argc=%d", argc);
            return 0;
        }

        static int Open(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::Open();
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::Open error, argc=%d", argc);
            return 0;
        }

        static int FlipInclusion(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Bound = LuaObject::checkValue<FDoubleRangeBound*>(L, 1);
                if (!Bound) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BoundRef = *Bound;
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::FlipInclusion(BoundRef);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::FlipInclusion error, argc=%d", argc);
            return 0;
        }

        static int MaxLower(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FDoubleRangeBound*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FDoubleRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::MaxLower(ARef, BRef);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::MaxLower error, argc=%d", argc);
            return 0;
        }

        static int MaxUpper(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FDoubleRangeBound*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FDoubleRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::MaxUpper(ARef, BRef);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::MaxUpper error, argc=%d", argc);
            return 0;
        }

        static int MinLower(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FDoubleRangeBound*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FDoubleRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::MinLower(ARef, BRef);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::MinLower error, argc=%d", argc);
            return 0;
        }

        static int MinUpper(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FDoubleRangeBound*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FDoubleRangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto ret = __newFDoubleRangeBound();
                *ret = FDoubleRangeBound::MinUpper(ARef, BRef);
                LuaObject::push<FDoubleRangeBound>(L, "FDoubleRangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRangeBound::MinUpper error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FDoubleRangeBound");
            LuaObject::addMethod(L, "Exclusive", Exclusive, false);
            LuaObject::addMethod(L, "Inclusive", Inclusive, false);
            LuaObject::addMethod(L, "Open", Open, false);
            LuaObject::addMethod(L, "FlipInclusion", FlipInclusion, false);
            LuaObject::addMethod(L, "MaxLower", MaxLower, false);
            LuaObject::addMethod(L, "MaxUpper", MaxUpper, false);
            LuaObject::addMethod(L, "MinLower", MinLower, false);
            LuaObject::addMethod(L, "MinUpper", MinUpper, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FDoubleRangeBound", __ctor, __gc);
        }

    };

    struct FDoubleRangeWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FDoubleRange();
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto A = LuaObject::checkValue<int>(L, 2);
                auto self = new FDoubleRange(A);
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto A = LuaObject::checkValue<int>(L, 2);
                auto B = LuaObject::checkValue<int>(L, 3);
                auto self = new FDoubleRange(A, B);
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRange() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FDoubleRange);
            auto ret = __newFDoubleRange();
            *ret = *self;
            LuaObject::push<FDoubleRange>(L, "FDoubleRange", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FDoubleRange);
            SLUA_GCSTRUCT(FDoubleRange);
            return 0;
        }

        static int Empty(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDoubleRange();
                *ret = FDoubleRange::Empty();
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRange::Empty error, argc=%d", argc);
            return 0;
        }

        static int All(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDoubleRange();
                *ret = FDoubleRange::All();
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRange::All error, argc=%d", argc);
            return 0;
        }

        static int AtLeast(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value = LuaObject::checkValue<int>(L, 1);
                auto ret = __newFDoubleRange();
                *ret = FDoubleRange::AtLeast(Value);
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRange::AtLeast error, argc=%d", argc);
            return 0;
        }

        static int AtMost(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Value = LuaObject::checkValue<int>(L, 1);
                auto ret = __newFDoubleRange();
                *ret = FDoubleRange::AtMost(Value);
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleRange::AtMost error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FDoubleRange");
            LuaObject::addMethod(L, "Empty", Empty, false);
            LuaObject::addMethod(L, "All", All, false);
            LuaObject::addMethod(L, "AtLeast", AtLeast, false);
            LuaObject::addMethod(L, "AtMost", AtMost, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FDoubleRange", __ctor, __gc);
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
                auto self = new FInt32RangeBound(InValue);
                LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FInt32RangeBound() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FInt32RangeBound);
            auto ret = __newFInt32RangeBound();
            *ret = *self;
            LuaObject::push<FInt32RangeBound>(L, "FInt32RangeBound", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInt32RangeBound);
            SLUA_GCSTRUCT(FInt32RangeBound);
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
                if (!Bound) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FInt32RangeBound*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            LuaObject::addMethod(L, "clone", clone, true);
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

        static int clone(lua_State* L) {
            CheckSelf(FInt32Range);
            auto ret = __newFInt32Range();
            *ret = *self;
            LuaObject::push<FInt32Range>(L, "FInt32Range", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInt32Range);
            SLUA_GCSTRUCT(FInt32Range);
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
            LuaObject::addMethod(L, "clone", clone, true);
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

        static int clone(lua_State* L) {
            CheckSelf(FFloatInterval);
            auto ret = __newFFloatInterval();
            *ret = *self;
            LuaObject::push<FFloatInterval>(L, "FFloatInterval", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FFloatInterval);
            SLUA_GCSTRUCT(FFloatInterval);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FFloatInterval");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FFloatInterval", __ctor, __gc);
        }

    };

    struct FDoubleIntervalWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FDoubleInterval();
                LuaObject::push<FDoubleInterval>(L, "FDoubleInterval", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InMin = LuaObject::checkValue<float>(L, 2);
                auto InMinVal = (double)InMin;
                auto InMax = LuaObject::checkValue<float>(L, 3);
                auto InMaxVal = (double)InMax;
                auto self = new FDoubleInterval(InMinVal, InMaxVal);
                LuaObject::push<FDoubleInterval>(L, "FDoubleInterval", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDoubleInterval() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FDoubleInterval);
            auto ret = __newFDoubleInterval();
            *ret = *self;
            LuaObject::push<FDoubleInterval>(L, "FDoubleInterval", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FDoubleInterval);
            SLUA_GCSTRUCT(FDoubleInterval);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FDoubleInterval");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FDoubleInterval", __ctor, __gc);
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

        static int clone(lua_State* L) {
            CheckSelf(FInt32Interval);
            auto ret = __newFInt32Interval();
            *ret = *self;
            LuaObject::push<FInt32Interval>(L, "FInt32Interval", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInt32Interval);
            SLUA_GCSTRUCT(FInt32Interval);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInt32Interval");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInt32Interval", __ctor, __gc);
        }

    };

    struct FFrameNumberWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FFrameNumber();
                LuaObject::push<FFrameNumber>(L, "FFrameNumber", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFrameNumber() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FFrameNumber);
            auto ret = __newFFrameNumber();
            *ret = *self;
            LuaObject::push<FFrameNumber>(L, "FFrameNumber", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FFrameNumber);
            SLUA_GCSTRUCT(FFrameNumber);
            return 0;
        }

        static int get_Value(lua_State* L) {
            CheckSelf(FFrameNumber);
            auto& Value = self->Value;
            LuaObject::push(L, Value);
            return 1;
        }

        static int set_Value(lua_State* L) {
            CheckSelf(FFrameNumber);
            auto& Value = self->Value;
            auto ValueIn = LuaObject::checkValue<int32>(L, 2);
            Value = ValueIn;
            LuaObject::push(L, ValueIn);
            return 1;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FFrameNumber");
            LuaObject::addField(L, "Value", get_Value, set_Value, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FFrameNumber", __ctor, __gc);
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

        static int clone(lua_State* L) {
            CheckSelf(FPrimaryAssetType);
            auto ret = __newFPrimaryAssetType();
            *ret = *self;
            LuaObject::push<FPrimaryAssetType>(L, "FPrimaryAssetType", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FPrimaryAssetType);
            SLUA_GCSTRUCT(FPrimaryAssetType);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FPrimaryAssetType);
            if (LuaObject::matchType(L, 2, "FPrimaryAssetType")) {
                auto Other = LuaObject::checkValue<FPrimaryAssetType*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int LexicalLess(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FPrimaryAssetType);
                auto Other = LuaObject::checkValue<FPrimaryAssetType*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = self->LexicalLess(OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FPrimaryAssetType::LexicalLess error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FPrimaryAssetType");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addMethod(L, "IsValid", IsValid, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "LexicalLess", LexicalLess, true);
            LuaObject::addMethod(L, "clone", clone, true);
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
                auto TypeAndName = LuaObject::checkValue<FString>(L, 2);
                auto self = new FPrimaryAssetId(TypeAndName);
                LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPrimaryAssetId() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FPrimaryAssetId);
            auto ret = __newFPrimaryAssetId();
            *ret = *self;
            LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FPrimaryAssetId);
            SLUA_GCSTRUCT(FPrimaryAssetId);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FPrimaryAssetId);
            if (LuaObject::matchType(L, 2, "FPrimaryAssetId")) {
                auto Other = LuaObject::checkValue<FPrimaryAssetId*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            LuaObject::pushAndLink<FPrimaryAssetType>(L, udptr->parent ? udptr->parent : self, "FPrimaryAssetType", &PrimaryAssetType);
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

        static int ParseTypeAndName(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto TypeAndName = LuaObject::checkValue<FString>(L, 1);
                auto ret = __newFPrimaryAssetId();
                *ret = FPrimaryAssetId::ParseTypeAndName(TypeAndName);
                LuaObject::push<FPrimaryAssetId>(L, "FPrimaryAssetId", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPrimaryAssetId::ParseTypeAndName error, argc=%d", argc);
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
            LuaObject::addMethod(L, "ParseTypeAndName", ParseTypeAndName, false);
            LuaObject::addMethod(L, "FromString", FromString, false);
            LuaObject::addMethod(L, "clone", clone, true);
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
                auto InTicks = LuaObject::checkValue<int>(L, 2);
                auto self = new FDateTime(InTicks);
                LuaObject::push<FDateTime>(L, "FDateTime", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 8) {
                auto Year = LuaObject::checkValue<int>(L, 2);
                auto Month = LuaObject::checkValue<int>(L, 3);
                auto Day = LuaObject::checkValue<int>(L, 4);
                auto Hour = LuaObject::checkValue<int>(L, 5);
                auto Minute = LuaObject::checkValue<int>(L, 6);
                auto Second = LuaObject::checkValue<int>(L, 7);
                auto Millisecond = LuaObject::checkValue<int>(L, 8);
                auto self = new FDateTime(Year, Month, Day, Hour, Minute, Second, Millisecond);
                LuaObject::push<FDateTime>(L, "FDateTime", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FDateTime);
            auto ret = __newFDateTime();
            *ret = *self;
            LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FDateTime);
            SLUA_GCSTRUCT(FDateTime);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FDateTime);
            if (LuaObject::matchType(L, 2, "FDateTime")) {
                auto Other = LuaObject::checkValue<FDateTime*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = (*self == OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
            return 1;
        }

        static int GetDate(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FDateTime);
                auto ret = __newFDateTime();
                *ret = self->GetDate();
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 4) {
                CheckSelf(FDateTime);
                auto OutYear = LuaObject::checkValue<int>(L, 2);
                auto OutMonth = LuaObject::checkValue<int>(L, 3);
                auto OutDay = LuaObject::checkValue<int>(L, 4);
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
                LuaObject::push(L, static_cast<int>(ret));
                return 1;
            }
            luaL_error(L, "call FDateTime::GetDayOfWeek error, argc=%d", argc);
            return 0;
        }

        static int GetDayOfYear(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FDateTime);
                auto ret = self->GetDayOfYear();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::GetDayOfYear error, argc=%d", argc);
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
                LuaObject::push(L, static_cast<int>(ret));
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

        static int ToIso8601(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FDateTime);
                auto ret = self->ToIso8601();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::ToIso8601 error, argc=%d", argc);
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
                auto Year = LuaObject::checkValue<int>(L, 1);
                auto Month = LuaObject::checkValue<int>(L, 2);
                auto ret = FDateTime::DaysInMonth(Year, Month);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::DaysInMonth error, argc=%d", argc);
            return 0;
        }

        static int DaysInYear(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Year = LuaObject::checkValue<int>(L, 1);
                auto ret = FDateTime::DaysInYear(Year);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::DaysInYear error, argc=%d", argc);
            return 0;
        }

        static int FromJulianDay(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto JulianDay = LuaObject::checkValue<float>(L, 1);
                auto JulianDayVal = (double)JulianDay;
                auto ret = __newFDateTime();
                *ret = FDateTime::FromJulianDay(JulianDayVal);
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime::FromJulianDay error, argc=%d", argc);
            return 0;
        }

        static int FromUnixTimestamp(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto UnixTime = LuaObject::checkValue<int>(L, 1);
                auto ret = __newFDateTime();
                *ret = FDateTime::FromUnixTimestamp(UnixTime);
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime::FromUnixTimestamp error, argc=%d", argc);
            return 0;
        }

        static int IsLeapYear(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Year = LuaObject::checkValue<int>(L, 1);
                auto ret = FDateTime::IsLeapYear(Year);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::IsLeapYear error, argc=%d", argc);
            return 0;
        }

        static int MaxValue(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDateTime();
                *ret = FDateTime::MaxValue();
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime::MaxValue error, argc=%d", argc);
            return 0;
        }

        static int MinValue(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDateTime();
                *ret = FDateTime::MinValue();
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime::MinValue error, argc=%d", argc);
            return 0;
        }

        static int Now(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDateTime();
                *ret = FDateTime::Now();
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime::Now error, argc=%d", argc);
            return 0;
        }

        static int Parse(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto DateTimeString = LuaObject::checkValue<FString>(L, 1);
                auto OutDateTime = LuaObject::checkValue<FDateTime*>(L, 2);
                if (!OutDateTime) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OutDateTimeRef = *OutDateTime;
                auto ret = FDateTime::Parse(DateTimeString, OutDateTimeRef);
                LuaObject::push(L, ret);
                LuaObject::push<FDateTime>(L, "FDateTime", OutDateTime);
                return 2;
            }
            luaL_error(L, "call FDateTime::Parse error, argc=%d", argc);
            return 0;
        }

        static int ParseHttpDate(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto HttpDate = LuaObject::checkValue<FString>(L, 1);
                auto OutDateTime = LuaObject::checkValue<FDateTime*>(L, 2);
                if (!OutDateTime) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OutDateTimeRef = *OutDateTime;
                auto ret = FDateTime::ParseHttpDate(HttpDate, OutDateTimeRef);
                LuaObject::push(L, ret);
                LuaObject::push<FDateTime>(L, "FDateTime", OutDateTime);
                return 2;
            }
            luaL_error(L, "call FDateTime::ParseHttpDate error, argc=%d", argc);
            return 0;
        }

        static int Today(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDateTime();
                *ret = FDateTime::Today();
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime::Today error, argc=%d", argc);
            return 0;
        }

        static int UtcNow(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFDateTime();
                *ret = FDateTime::UtcNow();
                LuaObject::push<FDateTime>(L, "FDateTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FDateTime::UtcNow error, argc=%d", argc);
            return 0;
        }

        static int Validate(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 7) {
                auto Year = LuaObject::checkValue<int>(L, 1);
                auto Month = LuaObject::checkValue<int>(L, 2);
                auto Day = LuaObject::checkValue<int>(L, 3);
                auto Hour = LuaObject::checkValue<int>(L, 4);
                auto Minute = LuaObject::checkValue<int>(L, 5);
                auto Second = LuaObject::checkValue<int>(L, 6);
                auto Millisecond = LuaObject::checkValue<int>(L, 7);
                auto ret = FDateTime::Validate(Year, Month, Day, Hour, Minute, Second, Millisecond);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::Validate error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FDateTime");
            LuaObject::addOperator(L, "__eq", __eq);
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
            LuaObject::addMethod(L, "ToIso8601", ToIso8601, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
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
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FDateTime", __ctor, __gc);
        }

    };

    struct FTestUninitializedScriptStructMembersTestWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FTestUninitializedScriptStructMembersTest() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FTestUninitializedScriptStructMembersTest);
            auto ret = __newFTestUninitializedScriptStructMembersTest();
            *ret = *self;
            LuaObject::push<FTestUninitializedScriptStructMembersTest>(L, "FTestUninitializedScriptStructMembersTest", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FTestUninitializedScriptStructMembersTest);
            SLUA_GCSTRUCT(FTestUninitializedScriptStructMembersTest);
            return 0;
        }

        static int get_UnusedValue(lua_State* L) {
            CheckSelf(FTestUninitializedScriptStructMembersTest);
            auto& UnusedValue = self->UnusedValue;
            LuaObject::push(L, UnusedValue);
            return 1;
        }

        static int set_UnusedValue(lua_State* L) {
            CheckSelf(FTestUninitializedScriptStructMembersTest);
            auto& UnusedValue = self->UnusedValue;
            auto UnusedValueIn = LuaObject::checkValue<float>(L, 2);
            UnusedValue = UnusedValueIn;
            LuaObject::push(L, UnusedValueIn);
            return 1;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FTestUninitializedScriptStructMembersTest");
            LuaObject::addField(L, "UnusedValue", get_UnusedValue, set_UnusedValue, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FTestUninitializedScriptStructMembersTest", __ctor, __gc);
        }

    };

    struct FTopLevelAssetPathWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FTopLevelAssetPath();
                LuaObject::push<FTopLevelAssetPath>(L, "FTopLevelAssetPath", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FTopLevelAssetPath);
            auto ret = __newFTopLevelAssetPath();
            *ret = *self;
            LuaObject::push<FTopLevelAssetPath>(L, "FTopLevelAssetPath", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FTopLevelAssetPath);
            SLUA_GCSTRUCT(FTopLevelAssetPath);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FTopLevelAssetPath);
            if (LuaObject::matchType(L, 2, "FTopLevelAssetPath")) {
                auto Other = LuaObject::checkValue<FTopLevelAssetPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = (*self == OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
            return 1;
        }

        static int TrySetPath(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTopLevelAssetPath);
                auto Path = LuaObject::checkValue<FString>(L, 2);
                auto ret = self->TrySetPath(Path);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath::TrySetPath error, argc=%d", argc);
            return 0;
        }

        static int AppendString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTopLevelAssetPath);
                auto OutString = LuaObject::checkValue<FString>(L, 2);
                self->AppendString(OutString);
                LuaObject::push(L, OutString);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath::AppendString error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTopLevelAssetPath);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            if (argc == 2) {
                CheckSelf(FTopLevelAssetPath);
                auto OutString = LuaObject::checkValue<FString>(L, 2);
                self->ToString(OutString);
                LuaObject::push(L, OutString);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath::ToString error, argc=%d", argc);
            return 0;
        }

        static int IsValid(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTopLevelAssetPath);
                auto ret = self->IsValid();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath::IsValid error, argc=%d", argc);
            return 0;
        }

        static int IsNull(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTopLevelAssetPath);
                auto ret = self->IsNull();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath::IsNull error, argc=%d", argc);
            return 0;
        }

        static int Reset(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTopLevelAssetPath);
                self->Reset();
                return 0;
            }
            luaL_error(L, "call FTopLevelAssetPath::Reset error, argc=%d", argc);
            return 0;
        }

        static int Compare(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTopLevelAssetPath);
                auto Other = LuaObject::checkValue<FTopLevelAssetPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = self->Compare(OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath::Compare error, argc=%d", argc);
            return 0;
        }

        static int CompareFast(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTopLevelAssetPath);
                auto Other = LuaObject::checkValue<FTopLevelAssetPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = self->CompareFast(OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTopLevelAssetPath::CompareFast error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FTopLevelAssetPath");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addMethod(L, "TrySetPath", TrySetPath, true);
            LuaObject::addMethod(L, "AppendString", AppendString, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "IsValid", IsValid, true);
            LuaObject::addMethod(L, "IsNull", IsNull, true);
            LuaObject::addMethod(L, "Reset", Reset, true);
            LuaObject::addMethod(L, "Compare", Compare, true);
            LuaObject::addMethod(L, "CompareFast", CompareFast, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FTopLevelAssetPath", __ctor, __gc);
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
                auto InColor = LuaObject::checkValue<FLinearColor*>(L, 2);
                if (!InColor) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InColorRef = *InColor;
                auto self = new FVector(InColorRef);
                LuaObject::push<FVector>(L, "FVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FVector);
            auto ret = __newFVector();
            *ret = *self;
            LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FVector);
            SLUA_GCSTRUCT(FVector);
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FVector);
            if (LuaObject::matchType(L, 2, "FVector")) {
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector();
                *ret = (*self + VRef);
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector();
                *ret = (*self - VRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FVector operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __mul(lua_State* L) {
            CheckSelf(FVector);
            if (LuaObject::matchType(L, 2, "FVector")) {
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            if (LuaObject::matchType(L, 2, "FVector")) {
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = (*self == VRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
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

        static int get_DownVector(lua_State* L) {
            auto& DownVector = FVector::DownVector;
            LuaObject::push<FVector>(L, "FVector", &DownVector);
            return 1;
        }

        static int get_ForwardVector(lua_State* L) {
            auto& ForwardVector = FVector::ForwardVector;
            LuaObject::push<FVector>(L, "FVector", &ForwardVector);
            return 1;
        }

        static int get_BackwardVector(lua_State* L) {
            auto& BackwardVector = FVector::BackwardVector;
            LuaObject::push<FVector>(L, "FVector", &BackwardVector);
            return 1;
        }

        static int get_RightVector(lua_State* L) {
            auto& RightVector = FVector::RightVector;
            LuaObject::push<FVector>(L, "FVector", &RightVector);
            return 1;
        }

        static int get_LeftVector(lua_State* L) {
            auto& LeftVector = FVector::LeftVector;
            LuaObject::push<FVector>(L, "FVector", &LeftVector);
            return 1;
        }

        static int get_XAxisVector(lua_State* L) {
            auto& XAxisVector = FVector::XAxisVector;
            LuaObject::push<FVector>(L, "FVector", &XAxisVector);
            return 1;
        }

        static int get_YAxisVector(lua_State* L) {
            auto& YAxisVector = FVector::YAxisVector;
            LuaObject::push<FVector>(L, "FVector", &YAxisVector);
            return 1;
        }

        static int get_ZAxisVector(lua_State* L) {
            auto& ZAxisVector = FVector::ZAxisVector;
            LuaObject::push<FVector>(L, "FVector", &ZAxisVector);
            return 1;
        }

        static int DiagnosticCheckNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector);
                self->DiagnosticCheckNaN();
                return 0;
            }
            luaL_error(L, "call FVector::DiagnosticCheckNaN error, argc=%d", argc);
            return 0;
        }

        static int Cross(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto V2 = LuaObject::checkValue<FVector*>(L, 2);
                if (!V2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& V2Ref = *V2;
                auto ret = __newFVector();
                *ret = self->Cross(V2Ref);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::Cross error, argc=%d", argc);
            return 0;
        }

        static int ComponentMin(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto Other = LuaObject::checkValue<FVector*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int ToDirectionAndLength(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto OutDir = LuaObject::checkValue<FVector*>(L, 2);
                if (!OutDir) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OutDirRef = *OutDir;
                auto OutLength = LuaObject::checkValue<float>(L, 3);
                auto OutLengthVal = (double)OutLength;
                self->ToDirectionAndLength(OutDirRef, OutLengthVal);
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

        static int GetUnsafeNormal2D(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector);
                auto ret = __newFVector();
                *ret = self->GetUnsafeNormal2D();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::GetUnsafeNormal2D error, argc=%d", argc);
            return 0;
        }

        static int BoundToBox(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto Min = LuaObject::checkValue<FVector*>(L, 2);
                if (!Min) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MinRef = *Min;
                auto Max = LuaObject::checkValue<FVector*>(L, 3);
                if (!Max) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MaxRef = *Max;
                auto ret = __newFVector();
                *ret = self->BoundToBox(MinRef, MaxRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::BoundToBox error, argc=%d", argc);
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

        static int MirrorByVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto MirrorNormal = LuaObject::checkValue<FVector*>(L, 2);
                if (!MirrorNormal) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MirrorNormalRef = *MirrorNormal;
                auto ret = __newFVector();
                *ret = self->MirrorByVector(MirrorNormalRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::MirrorByVector error, argc=%d", argc);
            return 0;
        }

        static int MirrorByPlane(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto Plane = LuaObject::checkValue<FPlane*>(L, 2);
                if (!Plane) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PlaneRef = *Plane;
                auto ret = __newFVector();
                *ret = self->MirrorByPlane(PlaneRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::MirrorByPlane error, argc=%d", argc);
            return 0;
        }

        static int ProjectOnTo(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto A = LuaObject::checkValue<FVector*>(L, 2);
                if (!A) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Normal) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NormalRef = *Normal;
                auto ret = __newFVector();
                *ret = self->ProjectOnToNormal(NormalRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::ProjectOnToNormal error, argc=%d", argc);
            return 0;
        }

        static int ToOrientationQuat(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector);
                auto ret = __newFQuat();
                *ret = self->ToOrientationQuat();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::ToOrientationQuat error, argc=%d", argc);
            return 0;
        }

        static int FindBestAxisVectors(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto Axis1 = LuaObject::checkValue<FVector*>(L, 2);
                if (!Axis1) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Axis1Ref = *Axis1;
                auto Axis2 = LuaObject::checkValue<FVector*>(L, 3);
                if (!Axis2) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int InitFromCompactString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto InSourceString = LuaObject::checkValue<FString>(L, 2);
                auto ret = self->InitFromCompactString(InSourceString);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector::InitFromCompactString error, argc=%d", argc);
            return 0;
        }

        static int Zero(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFVector();
                *ret = FVector::Zero();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::Zero error, argc=%d", argc);
            return 0;
        }

        static int One(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFVector();
                *ret = FVector::One();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::One error, argc=%d", argc);
            return 0;
        }

        static int UnitX(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFVector();
                *ret = FVector::UnitX();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::UnitX error, argc=%d", argc);
            return 0;
        }

        static int UnitY(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFVector();
                *ret = FVector::UnitY();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::UnitY error, argc=%d", argc);
            return 0;
        }

        static int UnitZ(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFVector();
                *ret = FVector::UnitZ();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::UnitZ error, argc=%d", argc);
            return 0;
        }

        static int CrossProduct(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FVector*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FVector*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto ret = __newFVector();
                *ret = FVector::CrossProduct(ARef, BRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::CrossProduct error, argc=%d", argc);
            return 0;
        }

        static int CreateOrthonormalBasis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto XAxis = LuaObject::checkValue<FVector*>(L, 1);
                if (!XAxis) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& XAxisRef = *XAxis;
                auto YAxis = LuaObject::checkValue<FVector*>(L, 2);
                if (!YAxis) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& YAxisRef = *YAxis;
                auto ZAxis = LuaObject::checkValue<FVector*>(L, 3);
                if (!ZAxis) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!P) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PRef = *P;
                auto Q = LuaObject::checkValue<FVector*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto ret = FVector::PointsAreSame(PRef, QRef);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector::PointsAreSame error, argc=%d", argc);
            return 0;
        }

        static int PointPlaneProject(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto Point = LuaObject::checkValue<FVector*>(L, 1);
                if (!Point) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PointRef = *Point;
                auto Plane = LuaObject::checkValue<FPlane*>(L, 2);
                if (!Plane) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PlaneRef = *Plane;
                auto ret = __newFVector();
                *ret = FVector::PointPlaneProject(PointRef, PlaneRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto Point = LuaObject::checkValue<FVector*>(L, 1);
                if (!Point) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PointRef = *Point;
                auto PlaneBase = LuaObject::checkValue<FVector*>(L, 2);
                if (!PlaneBase) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PlaneBaseRef = *PlaneBase;
                auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 3);
                if (!PlaneNormal) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PlaneNormalRef = *PlaneNormal;
                auto ret = __newFVector();
                *ret = FVector::PointPlaneProject(PointRef, PlaneBaseRef, PlaneNormalRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 4) {
                auto Point = LuaObject::checkValue<FVector*>(L, 1);
                if (!Point) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PointRef = *Point;
                auto A = LuaObject::checkValue<FVector*>(L, 2);
                if (!A) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FVector*>(L, 3);
                if (!B) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto C = LuaObject::checkValue<FVector*>(L, 4);
                if (!C) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto PlaneNormal = LuaObject::checkValue<FVector*>(L, 2);
                if (!PlaneNormal) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PlaneNormalRef = *PlaneNormal;
                auto ret = __newFVector();
                *ret = FVector::VectorPlaneProject(VRef, PlaneNormalRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::VectorPlaneProject error, argc=%d", argc);
            return 0;
        }

        static int Min(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FVector*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FVector*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto ret = __newFVector();
                *ret = FVector::Min(ARef, BRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::Min error, argc=%d", argc);
            return 0;
        }

        static int Max(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FVector*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FVector*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto ret = __newFVector();
                *ret = FVector::Max(ARef, BRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::Max error, argc=%d", argc);
            return 0;
        }

        static int Min3(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto A = LuaObject::checkValue<FVector*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FVector*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto C = LuaObject::checkValue<FVector*>(L, 3);
                if (!C) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& CRef = *C;
                auto ret = __newFVector();
                *ret = FVector::Min3(ARef, BRef, CRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::Min3 error, argc=%d", argc);
            return 0;
        }

        static int Max3(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto A = LuaObject::checkValue<FVector*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FVector*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto C = LuaObject::checkValue<FVector*>(L, 3);
                if (!C) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& CRef = *C;
                auto ret = __newFVector();
                *ret = FVector::Max3(ARef, BRef, CRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::Max3 error, argc=%d", argc);
            return 0;
        }

        static int RadiansToDegrees(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto RadVector = LuaObject::checkValue<FVector*>(L, 1);
                if (!RadVector) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!DegVector) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            LuaObject::addField(L, "ZeroVector", get_ZeroVector, nullptr, false);
            LuaObject::addField(L, "OneVector", get_OneVector, nullptr, false);
            LuaObject::addField(L, "UpVector", get_UpVector, nullptr, false);
            LuaObject::addField(L, "DownVector", get_DownVector, nullptr, false);
            LuaObject::addField(L, "ForwardVector", get_ForwardVector, nullptr, false);
            LuaObject::addField(L, "BackwardVector", get_BackwardVector, nullptr, false);
            LuaObject::addField(L, "RightVector", get_RightVector, nullptr, false);
            LuaObject::addField(L, "LeftVector", get_LeftVector, nullptr, false);
            LuaObject::addField(L, "XAxisVector", get_XAxisVector, nullptr, false);
            LuaObject::addField(L, "YAxisVector", get_YAxisVector, nullptr, false);
            LuaObject::addField(L, "ZAxisVector", get_ZAxisVector, nullptr, false);
            LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
            LuaObject::addMethod(L, "Cross", Cross, true);
            LuaObject::addMethod(L, "ComponentMin", ComponentMin, true);
            LuaObject::addMethod(L, "ComponentMax", ComponentMax, true);
            LuaObject::addMethod(L, "GetAbs", GetAbs, true);
            LuaObject::addMethod(L, "IsZero", IsZero, true);
            LuaObject::addMethod(L, "IsNormalized", IsNormalized, true);
            LuaObject::addMethod(L, "GetUnsafeNormal", GetUnsafeNormal, true);
            LuaObject::addMethod(L, "ToDirectionAndLength", ToDirectionAndLength, true);
            LuaObject::addMethod(L, "GetSignVector", GetSignVector, true);
            LuaObject::addMethod(L, "Projection", Projection, true);
            LuaObject::addMethod(L, "GetUnsafeNormal2D", GetUnsafeNormal2D, true);
            LuaObject::addMethod(L, "BoundToBox", BoundToBox, true);
            LuaObject::addMethod(L, "Reciprocal", Reciprocal, true);
            LuaObject::addMethod(L, "MirrorByVector", MirrorByVector, true);
            LuaObject::addMethod(L, "MirrorByPlane", MirrorByPlane, true);
            LuaObject::addMethod(L, "ProjectOnTo", ProjectOnTo, true);
            LuaObject::addMethod(L, "ProjectOnToNormal", ProjectOnToNormal, true);
            LuaObject::addMethod(L, "ToOrientationQuat", ToOrientationQuat, true);
            LuaObject::addMethod(L, "FindBestAxisVectors", FindBestAxisVectors, true);
            LuaObject::addMethod(L, "UnwindEuler", UnwindEuler, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "ToCompactString", ToCompactString, true);
            LuaObject::addMethod(L, "InitFromString", InitFromString, true);
            LuaObject::addMethod(L, "InitFromCompactString", InitFromCompactString, true);
            LuaObject::addMethod(L, "Zero", Zero, false);
            LuaObject::addMethod(L, "One", One, false);
            LuaObject::addMethod(L, "UnitX", UnitX, false);
            LuaObject::addMethod(L, "UnitY", UnitY, false);
            LuaObject::addMethod(L, "UnitZ", UnitZ, false);
            LuaObject::addMethod(L, "CrossProduct", CrossProduct, false);
            LuaObject::addMethod(L, "CreateOrthonormalBasis", CreateOrthonormalBasis, false);
            LuaObject::addMethod(L, "PointsAreSame", PointsAreSame, false);
            LuaObject::addMethod(L, "PointPlaneProject", PointPlaneProject, false);
            LuaObject::addMethod(L, "VectorPlaneProject", VectorPlaneProject, false);
            LuaObject::addMethod(L, "Min", Min, false);
            LuaObject::addMethod(L, "Max", Max, false);
            LuaObject::addMethod(L, "Min3", Min3, false);
            LuaObject::addMethod(L, "Max3", Max3, false);
            LuaObject::addMethod(L, "RadiansToDegrees", RadiansToDegrees, false);
            LuaObject::addMethod(L, "DegreesToRadians", DegreesToRadians, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FVector", __ctor, __gc);
        }

    };

    struct FPlaneWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FPlane();
                LuaObject::push<FPlane>(L, "FPlane", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FPlane(_a0Val);
                LuaObject::push<FPlane>(L, "FPlane", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InBase = LuaObject::checkValue<FVector*>(L, 2);
                auto InBaseVal = *InBase;
                auto InNormal = LuaObject::checkValue<FVector*>(L, 3);
                if (!InNormal) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InNormalRef = *InNormal;
                auto self = new FPlane(InBaseVal, InNormalRef);
                LuaObject::push<FPlane>(L, "FPlane", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 4) {
                auto A = LuaObject::checkValue<FVector*>(L, 2);
                auto AVal = *A;
                auto B = LuaObject::checkValue<FVector*>(L, 3);
                auto BVal = *B;
                auto C = LuaObject::checkValue<FVector*>(L, 4);
                auto CVal = *C;
                auto self = new FPlane(AVal, BVal, CVal);
                LuaObject::push<FPlane>(L, "FPlane", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPlane() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FPlane);
            auto ret = __newFPlane();
            *ret = *self;
            LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FPlane);
            SLUA_GCSTRUCT(FPlane);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FPlane);
            if (LuaObject::matchType(L, 2, "FPlane")) {
                auto V = LuaObject::checkValue<FPlane*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = (*self == VRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
            return 1;
        }

        static int __add(lua_State* L) {
            CheckSelf(FPlane);
            if (LuaObject::matchType(L, 2, "FPlane")) {
                auto V = LuaObject::checkValue<FPlane*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFPlane();
                *ret = (*self + VRef);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FPlane operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __sub(lua_State* L) {
            CheckSelf(FPlane);
            if (LuaObject::matchType(L, 2, "FPlane")) {
                auto V = LuaObject::checkValue<FPlane*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFPlane();
                *ret = (*self - VRef);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FPlane operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __mul(lua_State* L) {
            CheckSelf(FPlane);
            if (LuaObject::matchType(L, 2, "FPlane")) {
                auto V = LuaObject::checkValue<FPlane*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFPlane();
                *ret = (*self * VRef);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FPlane operator__mul error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int DiagnosticCheckNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FPlane);
                self->DiagnosticCheckNaN();
                return 0;
            }
            luaL_error(L, "call FPlane::DiagnosticCheckNaN error, argc=%d", argc);
            return 0;
        }

        static int IsValid(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FPlane);
                auto ret = self->IsValid();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FPlane::IsValid error, argc=%d", argc);
            return 0;
        }

        static int GetOrigin(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FPlane);
                auto ret = __newFVector();
                *ret = self->GetOrigin();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPlane::GetOrigin error, argc=%d", argc);
            return 0;
        }

        static int GetNormal(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FPlane);
                auto ret = __newFVector();
                *ret = self->GetNormal();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPlane::GetNormal error, argc=%d", argc);
            return 0;
        }

        static int Flip(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FPlane);
                auto ret = __newFPlane();
                *ret = self->Flip();
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPlane::Flip error, argc=%d", argc);
            return 0;
        }

        static int TransformBy(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FPlane);
                auto M = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!M) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MRef = *M;
                auto ret = __newFPlane();
                *ret = self->TransformBy(MRef);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPlane::TransformBy error, argc=%d", argc);
            return 0;
        }

        static int TranslateBy(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FPlane);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFPlane();
                *ret = self->TranslateBy(VRef);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPlane::TranslateBy error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newTypeWithBase(L, "FPlane", std::initializer_list<const char*>{ "TVector" });
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
            LuaObject::addMethod(L, "IsValid", IsValid, true);
            LuaObject::addMethod(L, "GetOrigin", GetOrigin, true);
            LuaObject::addMethod(L, "GetNormal", GetNormal, true);
            LuaObject::addMethod(L, "Flip", Flip, true);
            LuaObject::addMethod(L, "TransformBy", TransformBy, true);
            LuaObject::addMethod(L, "TranslateBy", TranslateBy, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FPlane", __ctor, __gc);
        }

    };

    struct FQuatWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FQuat();
                LuaObject::push<FQuat>(L, "FQuat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FQuat(_a0Val);
                LuaObject::push<FQuat>(L, "FQuat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FQuat);
            auto ret = __newFQuat();
            *ret = *self;
            LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FQuat);
            SLUA_GCSTRUCT(FQuat);
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FQuat);
            if (LuaObject::matchType(L, 2, "FQuat")) {
                auto Q = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto ret = __newFQuat();
                *ret = (*self + QRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FQuat operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __sub(lua_State* L) {
            CheckSelf(FQuat);
            if (LuaObject::matchType(L, 2, "FQuat")) {
                auto Q = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto ret = __newFQuat();
                *ret = (*self - QRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FQuat operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __mul(lua_State* L) {
            CheckSelf(FQuat);
            if (LuaObject::matchType(L, 2, "FQuat")) {
                auto Q = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto ret = __newFQuat();
                *ret = (*self * QRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (LuaObject::matchType(L, 2, "FQuat")) {
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector();
                *ret = (*self * VRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (LuaObject::matchType(L, 2, "FQuat")) {
                auto M = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!M) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MRef = *M;
                auto ret = __newFMatrix();
                *ret = (*self * MRef);
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FQuat operator__mul error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FQuat);
            if (LuaObject::matchType(L, 2, "FQuat")) {
                auto Q = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto ret = (*self == QRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
            return 1;
        }

        static int get_Identity(lua_State* L) {
            auto& Identity = FQuat::Identity;
            LuaObject::push<FQuat>(L, "FQuat", &Identity);
            return 1;
        }

        static int Euler(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->Euler();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Euler error, argc=%d", argc);
            return 0;
        }

        static int IsNormalized(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = self->IsNormalized();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FQuat::IsNormalized error, argc=%d", argc);
            return 0;
        }

        static int ToAxisAndAngle(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FQuat);
                auto Axis = LuaObject::checkValue<FVector*>(L, 2);
                if (!Axis) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& AxisRef = *Axis;
                auto Angle = LuaObject::checkValue<float>(L, 3);
                self->ToAxisAndAngle(AxisRef, Angle);
                LuaObject::push<FVector>(L, "FVector", Axis);
                LuaObject::push(L, Angle);
                return 2;
            }
            luaL_error(L, "call FQuat::ToAxisAndAngle error, argc=%d", argc);
            return 0;
        }

        static int ToRotationVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->ToRotationVector();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::ToRotationVector error, argc=%d", argc);
            return 0;
        }

        static int ToSwingTwist(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 4) {
                CheckSelf(FQuat);
                auto InTwistAxis = LuaObject::checkValue<FVector*>(L, 2);
                if (!InTwistAxis) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InTwistAxisRef = *InTwistAxis;
                auto OutSwing = LuaObject::checkValue<FQuat*>(L, 3);
                if (!OutSwing) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OutSwingRef = *OutSwing;
                auto OutTwist = LuaObject::checkValue<FQuat*>(L, 4);
                if (!OutTwist) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OutTwistRef = *OutTwist;
                self->ToSwingTwist(InTwistAxisRef, OutSwingRef, OutTwistRef);
                LuaObject::push<FQuat>(L, "FQuat", OutSwing);
                LuaObject::push<FQuat>(L, "FQuat", OutTwist);
                return 2;
            }
            luaL_error(L, "call FQuat::ToSwingTwist error, argc=%d", argc);
            return 0;
        }

        static int RotateVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FQuat);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                auto VVal = *V;
                auto ret = __newFVector();
                *ret = self->RotateVector(VVal);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::RotateVector error, argc=%d", argc);
            return 0;
        }

        static int UnrotateVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FQuat);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                auto VVal = *V;
                auto ret = __newFVector();
                *ret = self->UnrotateVector(VVal);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::UnrotateVector error, argc=%d", argc);
            return 0;
        }

        static int Log(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFQuat();
                *ret = self->Log();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Log error, argc=%d", argc);
            return 0;
        }

        static int Exp(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFQuat();
                *ret = self->Exp();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Exp error, argc=%d", argc);
            return 0;
        }

        static int Inverse(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFQuat();
                *ret = self->Inverse();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Inverse error, argc=%d", argc);
            return 0;
        }

        static int EnforceShortestArcWith(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FQuat);
                auto OtherQuat = LuaObject::checkValue<FQuat*>(L, 2);
                if (!OtherQuat) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherQuatRef = *OtherQuat;
                self->EnforceShortestArcWith(OtherQuatRef);
                return 0;
            }
            luaL_error(L, "call FQuat::EnforceShortestArcWith error, argc=%d", argc);
            return 0;
        }

        static int GetAxisX(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->GetAxisX();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetAxisX error, argc=%d", argc);
            return 0;
        }

        static int GetAxisY(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->GetAxisY();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetAxisY error, argc=%d", argc);
            return 0;
        }

        static int GetAxisZ(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->GetAxisZ();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetAxisZ error, argc=%d", argc);
            return 0;
        }

        static int GetForwardVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->GetForwardVector();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetForwardVector error, argc=%d", argc);
            return 0;
        }

        static int GetRightVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->GetRightVector();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetRightVector error, argc=%d", argc);
            return 0;
        }

        static int GetUpVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->GetUpVector();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetUpVector error, argc=%d", argc);
            return 0;
        }

        static int Vector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->Vector();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Vector error, argc=%d", argc);
            return 0;
        }

        static int ToMatrix(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFMatrix();
                *ret = self->ToMatrix();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                CheckSelf(FQuat);
                auto Mat = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!Mat) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MatRef = *Mat;
                self->ToMatrix(MatRef);
                LuaObject::push<FMatrix>(L, "FMatrix", Mat);
                return 1;
            }
            luaL_error(L, "call FQuat::ToMatrix error, argc=%d", argc);
            return 0;
        }

        static int GetRotationAxis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFVector();
                *ret = self->GetRotationAxis();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetRotationAxis error, argc=%d", argc);
            return 0;
        }

        static int ContainsNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = self->ContainsNaN();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FQuat::ContainsNaN error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FQuat::ToString error, argc=%d", argc);
            return 0;
        }

        static int InitFromString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FQuat);
                auto InSourceString = LuaObject::checkValue<FString>(L, 2);
                auto ret = self->InitFromString(InSourceString);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FQuat::InitFromString error, argc=%d", argc);
            return 0;
        }

        static int DiagnosticCheckNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                self->DiagnosticCheckNaN();
                return 0;
            }
            luaL_error(L, "call FQuat::DiagnosticCheckNaN error, argc=%d", argc);
            return 0;
        }

        static int MakeFromEuler(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Euler = LuaObject::checkValue<FVector*>(L, 1);
                if (!Euler) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& EulerRef = *Euler;
                auto ret = __newFQuat();
                *ret = FQuat::MakeFromEuler(EulerRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::MakeFromEuler error, argc=%d", argc);
            return 0;
        }

        static int MakeFromRotationVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto RotationVector = LuaObject::checkValue<FVector*>(L, 1);
                if (!RotationVector) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& RotationVectorRef = *RotationVector;
                auto ret = __newFQuat();
                *ret = FQuat::MakeFromRotationVector(RotationVectorRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::MakeFromRotationVector error, argc=%d", argc);
            return 0;
        }

        static int FindBetween(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto Vector1 = LuaObject::checkValue<FVector*>(L, 1);
                if (!Vector1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Vector1Ref = *Vector1;
                auto Vector2 = LuaObject::checkValue<FVector*>(L, 2);
                if (!Vector2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Vector2Ref = *Vector2;
                auto ret = __newFQuat();
                *ret = FQuat::FindBetween(Vector1Ref, Vector2Ref);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::FindBetween error, argc=%d", argc);
            return 0;
        }

        static int FindBetweenNormals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto Normal1 = LuaObject::checkValue<FVector*>(L, 1);
                if (!Normal1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Normal1Ref = *Normal1;
                auto Normal2 = LuaObject::checkValue<FVector*>(L, 2);
                if (!Normal2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Normal2Ref = *Normal2;
                auto ret = __newFQuat();
                *ret = FQuat::FindBetweenNormals(Normal1Ref, Normal2Ref);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::FindBetweenNormals error, argc=%d", argc);
            return 0;
        }

        static int FindBetweenVectors(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto Vector1 = LuaObject::checkValue<FVector*>(L, 1);
                if (!Vector1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Vector1Ref = *Vector1;
                auto Vector2 = LuaObject::checkValue<FVector*>(L, 2);
                if (!Vector2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Vector2Ref = *Vector2;
                auto ret = __newFQuat();
                *ret = FQuat::FindBetweenVectors(Vector1Ref, Vector2Ref);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::FindBetweenVectors error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FQuat");
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addField(L, "Identity", get_Identity, nullptr, false);
            LuaObject::addMethod(L, "Euler", Euler, true);
            LuaObject::addMethod(L, "IsNormalized", IsNormalized, true);
            LuaObject::addMethod(L, "ToAxisAndAngle", ToAxisAndAngle, true);
            LuaObject::addMethod(L, "ToRotationVector", ToRotationVector, true);
            LuaObject::addMethod(L, "ToSwingTwist", ToSwingTwist, true);
            LuaObject::addMethod(L, "RotateVector", RotateVector, true);
            LuaObject::addMethod(L, "UnrotateVector", UnrotateVector, true);
            LuaObject::addMethod(L, "Log", Log, true);
            LuaObject::addMethod(L, "Exp", Exp, true);
            LuaObject::addMethod(L, "Inverse", Inverse, true);
            LuaObject::addMethod(L, "EnforceShortestArcWith", EnforceShortestArcWith, true);
            LuaObject::addMethod(L, "GetAxisX", GetAxisX, true);
            LuaObject::addMethod(L, "GetAxisY", GetAxisY, true);
            LuaObject::addMethod(L, "GetAxisZ", GetAxisZ, true);
            LuaObject::addMethod(L, "GetForwardVector", GetForwardVector, true);
            LuaObject::addMethod(L, "GetRightVector", GetRightVector, true);
            LuaObject::addMethod(L, "GetUpVector", GetUpVector, true);
            LuaObject::addMethod(L, "Vector", Vector, true);
            LuaObject::addMethod(L, "ToMatrix", ToMatrix, true);
            LuaObject::addMethod(L, "GetRotationAxis", GetRotationAxis, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "InitFromString", InitFromString, true);
            LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
            LuaObject::addMethod(L, "MakeFromEuler", MakeFromEuler, false);
            LuaObject::addMethod(L, "MakeFromRotationVector", MakeFromRotationVector, false);
            LuaObject::addMethod(L, "FindBetween", FindBetween, false);
            LuaObject::addMethod(L, "FindBetweenNormals", FindBetweenNormals, false);
            LuaObject::addMethod(L, "FindBetweenVectors", FindBetweenVectors, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FQuat", __ctor, __gc);
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
                if (!InTranslation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InTranslationRef = *InTranslation;
                auto self = new FTransform(InTranslationRef);
                LuaObject::push<FTransform>(L, "FTransform", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 5) {
                auto InX = LuaObject::checkValue<FVector*>(L, 2);
                if (!InX) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InXRef = *InX;
                auto InY = LuaObject::checkValue<FVector*>(L, 3);
                if (!InY) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InYRef = *InY;
                auto InZ = LuaObject::checkValue<FVector*>(L, 4);
                if (!InZ) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InZRef = *InZ;
                auto InTranslation = LuaObject::checkValue<FVector*>(L, 5);
                if (!InTranslation) {
                    luaL_error(L, "%s argument 5 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InTranslationRef = *InTranslation;
                auto self = new FTransform(InXRef, InYRef, InZRef, InTranslationRef);
                LuaObject::push<FTransform>(L, "FTransform", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FTransform);
            auto ret = __newFTransform();
            *ret = *self;
            LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FTransform);
            SLUA_GCSTRUCT(FTransform);
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FTransform);
            if (LuaObject::matchType(L, 2, "FTransform")) {
                auto Atom = LuaObject::checkValue<FTransform*>(L, 2);
                if (!Atom) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFTransform();
                *ret = (*self * OtherRef);
                LuaObject::push<FTransform>(L, "FTransform", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (LuaObject::matchType(L, 2, "FTransform")) {
                auto Other = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int ToMatrixWithScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTransform);
                auto ret = __newFMatrix();
                *ret = self->ToMatrixWithScale();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::ToMatrixWithScale error, argc=%d", argc);
            return 0;
        }

        static int ToInverseMatrixWithScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTransform);
                auto ret = __newFMatrix();
                *ret = self->ToInverseMatrixWithScale();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::ToInverseMatrixWithScale error, argc=%d", argc);
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

        static int ToMatrixNoScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTransform);
                auto ret = __newFMatrix();
                *ret = self->ToMatrixNoScale();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::ToMatrixNoScale error, argc=%d", argc);
            return 0;
        }

        static int Blend(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 4) {
                CheckSelf(FTransform);
                auto Atom1 = LuaObject::checkValue<FTransform*>(L, 2);
                if (!Atom1) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Atom1Ref = *Atom1;
                auto Atom2 = LuaObject::checkValue<FTransform*>(L, 3);
                if (!Atom2) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!OtherAtom) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!InScale3D) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InScale3DRef = *InScale3D;
                self->ScaleTranslation(InScale3DRef);
                return 0;
            }
            luaL_error(L, "call FTransform::ScaleTranslation error, argc=%d", argc);
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!ParentTransform) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector();
                *ret = self->InverseTransformVectorNoScale(VRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::InverseTransformVectorNoScale error, argc=%d", argc);
            return 0;
        }

        static int TransformRotation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto Q = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto ret = __newFQuat();
                *ret = self->TransformRotation(QRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::TransformRotation error, argc=%d", argc);
            return 0;
        }

        static int InverseTransformRotation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto Q = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto ret = __newFQuat();
                *ret = self->InverseTransformRotation(QRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::InverseTransformRotation error, argc=%d", argc);
            return 0;
        }

        static int GetScaled(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto Scale = LuaObject::checkValue<FVector*>(L, 2);
                auto ScaleVal = *Scale;
                auto ret = __newFTransform();
                *ret = self->GetScaled(ScaleVal);
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

        static int SetLocation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto Origin = LuaObject::checkValue<FVector*>(L, 2);
                if (!Origin) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int SetComponents(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 4) {
                CheckSelf(FTransform);
                auto InRotation = LuaObject::checkValue<FQuat*>(L, 2);
                if (!InRotation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InRotationRef = *InRotation;
                auto InTranslation = LuaObject::checkValue<FVector*>(L, 3);
                if (!InTranslation) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InTranslationRef = *InTranslation;
                auto InScale3D = LuaObject::checkValue<FVector*>(L, 4);
                if (!InScale3D) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InScale3DRef = *InScale3D;
                self->SetComponents(InRotationRef, InTranslationRef, InScale3DRef);
                return 0;
            }
            luaL_error(L, "call FTransform::SetComponents error, argc=%d", argc);
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

        static int SetIdentityZeroScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTransform);
                self->SetIdentityZeroScale();
                return 0;
            }
            luaL_error(L, "call FTransform::SetIdentityZeroScale error, argc=%d", argc);
            return 0;
        }

        static int MultiplyScale3D(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto Scale3DMultiplier = LuaObject::checkValue<FVector*>(L, 2);
                if (!Scale3DMultiplier) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!NewTranslation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                self->CopyTranslation(OtherRef);
                return 0;
            }
            luaL_error(L, "call FTransform::CopyTranslation error, argc=%d", argc);
            return 0;
        }

        static int ConcatenateRotation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto DeltaRotation = LuaObject::checkValue<FQuat*>(L, 2);
                if (!DeltaRotation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& DeltaRotationRef = *DeltaRotation;
                self->ConcatenateRotation(DeltaRotationRef);
                return 0;
            }
            luaL_error(L, "call FTransform::ConcatenateRotation error, argc=%d", argc);
            return 0;
        }

        static int AddToTranslation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto DeltaTranslation = LuaObject::checkValue<FVector*>(L, 2);
                if (!DeltaTranslation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& DeltaTranslationRef = *DeltaTranslation;
                self->AddToTranslation(DeltaTranslationRef);
                return 0;
            }
            luaL_error(L, "call FTransform::AddToTranslation error, argc=%d", argc);
            return 0;
        }

        static int SetRotation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto NewRotation = LuaObject::checkValue<FQuat*>(L, 2);
                if (!NewRotation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NewRotationRef = *NewRotation;
                self->SetRotation(NewRotationRef);
                return 0;
            }
            luaL_error(L, "call FTransform::SetRotation error, argc=%d", argc);
            return 0;
        }

        static int CopyRotation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto Other = LuaObject::checkValue<FTransform*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!NewScale3D) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!NewTranslation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NewTranslationRef = *NewTranslation;
                auto NewScale3D = LuaObject::checkValue<FVector*>(L, 3);
                if (!NewScale3D) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NewScale3DRef = *NewScale3D;
                self->SetTranslationAndScale3D(NewTranslationRef, NewScale3DRef);
                return 0;
            }
            luaL_error(L, "call FTransform::SetTranslationAndScale3D error, argc=%d", argc);
            return 0;
        }

        static int GetTranslationRegister(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTransform);
                auto ret = self->GetTranslationRegister();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTransform::GetTranslationRegister error, argc=%d", argc);
            return 0;
        }

        static int GetRotationRegister(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTransform);
                auto ret = self->GetRotationRegister();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTransform::GetRotationRegister error, argc=%d", argc);
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

        static int GetRotation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FTransform);
                auto ret = __newFQuat();
                *ret = self->GetRotation();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::GetRotation error, argc=%d", argc);
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
                if (!SrcBA) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!SrcBA) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& SrcBARef = *SrcBA;
                self->CopyTranslationAndScale3D(SrcBARef);
                return 0;
            }
            luaL_error(L, "call FTransform::CopyTranslationAndScale3D error, argc=%d", argc);
            return 0;
        }

        static int SetFromMatrix(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto InMatrix = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!InMatrix) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InMatrixRef = *InMatrix;
                self->SetFromMatrix(InMatrixRef);
                return 0;
            }
            luaL_error(L, "call FTransform::SetFromMatrix error, argc=%d", argc);
            return 0;
        }

        static int AnyHasNegativeScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto InScale3D = LuaObject::checkValue<FVector*>(L, 1);
                if (!InScale3D) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InScale3DRef = *InScale3D;
                auto InOtherScale3D = LuaObject::checkValue<FVector*>(L, 2);
                if (!InOtherScale3D) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InOtherScale3DRef = *InOtherScale3D;
                auto ret = FTransform::AnyHasNegativeScale(InScale3DRef, InOtherScale3DRef);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTransform::AnyHasNegativeScale error, argc=%d", argc);
            return 0;
        }

        static int AddTranslations(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto A = LuaObject::checkValue<FTransform*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FTransform*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FTransform*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            LuaObject::addMethod(L, "ToMatrixWithScale", ToMatrixWithScale, true);
            LuaObject::addMethod(L, "ToInverseMatrixWithScale", ToInverseMatrixWithScale, true);
            LuaObject::addMethod(L, "Inverse", Inverse, true);
            LuaObject::addMethod(L, "ToMatrixNoScale", ToMatrixNoScale, true);
            LuaObject::addMethod(L, "Blend", Blend, true);
            LuaObject::addMethod(L, "BlendWith", BlendWith, true);
            LuaObject::addMethod(L, "ScaleTranslation", ScaleTranslation, true);
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
            LuaObject::addMethod(L, "TransformRotation", TransformRotation, true);
            LuaObject::addMethod(L, "InverseTransformRotation", InverseTransformRotation, true);
            LuaObject::addMethod(L, "GetScaled", GetScaled, true);
            LuaObject::addMethod(L, "GetScaledAxis", GetScaledAxis, true);
            LuaObject::addMethod(L, "GetUnitAxis", GetUnitAxis, true);
            LuaObject::addMethod(L, "Mirror", Mirror, true);
            LuaObject::addMethod(L, "GetLocation", GetLocation, true);
            LuaObject::addMethod(L, "SetLocation", SetLocation, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "IsValid", IsValid, true);
            LuaObject::addMethod(L, "SetComponents", SetComponents, true);
            LuaObject::addMethod(L, "SetIdentity", SetIdentity, true);
            LuaObject::addMethod(L, "SetIdentityZeroScale", SetIdentityZeroScale, true);
            LuaObject::addMethod(L, "MultiplyScale3D", MultiplyScale3D, true);
            LuaObject::addMethod(L, "SetTranslation", SetTranslation, true);
            LuaObject::addMethod(L, "CopyTranslation", CopyTranslation, true);
            LuaObject::addMethod(L, "ConcatenateRotation", ConcatenateRotation, true);
            LuaObject::addMethod(L, "AddToTranslation", AddToTranslation, true);
            LuaObject::addMethod(L, "SetRotation", SetRotation, true);
            LuaObject::addMethod(L, "CopyRotation", CopyRotation, true);
            LuaObject::addMethod(L, "SetScale3D", SetScale3D, true);
            LuaObject::addMethod(L, "CopyScale3D", CopyScale3D, true);
            LuaObject::addMethod(L, "SetTranslationAndScale3D", SetTranslationAndScale3D, true);
            LuaObject::addMethod(L, "GetTranslationRegister", GetTranslationRegister, true);
            LuaObject::addMethod(L, "GetRotationRegister", GetRotationRegister, true);
            LuaObject::addMethod(L, "NormalizeRotation", NormalizeRotation, true);
            LuaObject::addMethod(L, "IsRotationNormalized", IsRotationNormalized, true);
            LuaObject::addMethod(L, "GetRotation", GetRotation, true);
            LuaObject::addMethod(L, "GetTranslation", GetTranslation, true);
            LuaObject::addMethod(L, "GetScale3D", GetScale3D, true);
            LuaObject::addMethod(L, "CopyRotationPart", CopyRotationPart, true);
            LuaObject::addMethod(L, "CopyTranslationAndScale3D", CopyTranslationAndScale3D, true);
            LuaObject::addMethod(L, "SetFromMatrix", SetFromMatrix, true);
            LuaObject::addMethod(L, "AnyHasNegativeScale", AnyHasNegativeScale, false);
            LuaObject::addMethod(L, "AddTranslations", AddTranslations, false);
            LuaObject::addMethod(L, "SubtractTranslations", SubtractTranslations, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FTransform", __ctor, __gc);
        }

    };

    struct FMatrixWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FMatrix();
                LuaObject::push<FMatrix>(L, "FMatrix", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FMatrix(_a0Val);
                LuaObject::push<FMatrix>(L, "FMatrix", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 5) {
                auto InX = LuaObject::checkValue<FPlane*>(L, 2);
                if (!InX) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InXRef = *InX;
                auto InY = LuaObject::checkValue<FPlane*>(L, 3);
                if (!InY) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InYRef = *InY;
                auto InZ = LuaObject::checkValue<FPlane*>(L, 4);
                if (!InZ) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InZRef = *InZ;
                auto InW = LuaObject::checkValue<FPlane*>(L, 5);
                if (!InW) {
                    luaL_error(L, "%s argument 5 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InWRef = *InW;
                auto self = new FMatrix(InXRef, InYRef, InZRef, InWRef);
                LuaObject::push<FMatrix>(L, "FMatrix", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FMatrix);
            auto ret = __newFMatrix();
            *ret = *self;
            LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FMatrix);
            SLUA_GCSTRUCT(FMatrix);
            return 0;
        }

        static int __mul(lua_State* L) {
            CheckSelf(FMatrix);
            if (LuaObject::matchType(L, 2, "FMatrix")) {
                auto Other = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFMatrix();
                *ret = (*self * OtherRef);
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FMatrix operator__mul error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FMatrix);
            if (LuaObject::matchType(L, 2, "FMatrix")) {
                auto Other = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFMatrix();
                *ret = (*self + OtherRef);
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FMatrix operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FMatrix);
            if (LuaObject::matchType(L, 2, "FMatrix")) {
                auto Other = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = (*self == OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
            return 1;
        }

        static int get_Identity(lua_State* L) {
            auto& Identity = FMatrix::Identity;
            LuaObject::push<FMatrix>(L, "FMatrix", &Identity);
            return 1;
        }

        static int DiagnosticCheckNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                self->DiagnosticCheckNaN();
                return 0;
            }
            luaL_error(L, "call FMatrix::DiagnosticCheckNaN error, argc=%d", argc);
            return 0;
        }

        static int SetIdentity(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                self->SetIdentity();
                return 0;
            }
            luaL_error(L, "call FMatrix::SetIdentity error, argc=%d", argc);
            return 0;
        }

        static int InverseTransformPosition(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector();
                *ret = self->InverseTransformPosition(VRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::InverseTransformPosition error, argc=%d", argc);
            return 0;
        }

        static int InverseTransformVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector();
                *ret = self->InverseTransformVector(VRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::InverseTransformVector error, argc=%d", argc);
            return 0;
        }

        static int GetTransposed(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFMatrix();
                *ret = self->GetTransposed();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::GetTransposed error, argc=%d", argc);
            return 0;
        }

        static int InverseFast(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFMatrix();
                *ret = self->InverseFast();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::InverseFast error, argc=%d", argc);
            return 0;
        }

        static int Inverse(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFMatrix();
                *ret = self->Inverse();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::Inverse error, argc=%d", argc);
            return 0;
        }

        static int TransposeAdjoint(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFMatrix();
                *ret = self->TransposeAdjoint();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::TransposeAdjoint error, argc=%d", argc);
            return 0;
        }

        static int RemoveTranslation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFMatrix();
                *ret = self->RemoveTranslation();
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::RemoveTranslation error, argc=%d", argc);
            return 0;
        }

        static int ConcatTranslation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Translation = LuaObject::checkValue<FVector*>(L, 2);
                if (!Translation) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& TranslationRef = *Translation;
                auto ret = __newFMatrix();
                *ret = self->ConcatTranslation(TranslationRef);
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::ConcatTranslation error, argc=%d", argc);
            return 0;
        }

        static int ContainsNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = self->ContainsNaN();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FMatrix::ContainsNaN error, argc=%d", argc);
            return 0;
        }

        static int ScaleTranslation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Scale3D = LuaObject::checkValue<FVector*>(L, 2);
                if (!Scale3D) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Scale3DRef = *Scale3D;
                self->ScaleTranslation(Scale3DRef);
                return 0;
            }
            luaL_error(L, "call FMatrix::ScaleTranslation error, argc=%d", argc);
            return 0;
        }

        static int GetOrigin(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFVector();
                *ret = self->GetOrigin();
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::GetOrigin error, argc=%d", argc);
            return 0;
        }

        static int GetScaledAxis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Axis = LuaObject::checkValue<int>(L, 2);
                auto AxisVal = (EAxis::Type)Axis;
                auto ret = __newFVector();
                *ret = self->GetScaledAxis(AxisVal);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::GetScaledAxis error, argc=%d", argc);
            return 0;
        }

        static int GetScaledAxes(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 4) {
                CheckSelf(FMatrix);
                auto X = LuaObject::checkValue<FVector*>(L, 2);
                if (!X) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& XRef = *X;
                auto Y = LuaObject::checkValue<FVector*>(L, 3);
                if (!Y) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& YRef = *Y;
                auto Z = LuaObject::checkValue<FVector*>(L, 4);
                if (!Z) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ZRef = *Z;
                self->GetScaledAxes(XRef, YRef, ZRef);
                LuaObject::push<FVector>(L, "FVector", X);
                LuaObject::push<FVector>(L, "FVector", Y);
                LuaObject::push<FVector>(L, "FVector", Z);
                return 3;
            }
            luaL_error(L, "call FMatrix::GetScaledAxes error, argc=%d", argc);
            return 0;
        }

        static int GetUnitAxis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Axis = LuaObject::checkValue<int>(L, 2);
                auto AxisVal = (EAxis::Type)Axis;
                auto ret = __newFVector();
                *ret = self->GetUnitAxis(AxisVal);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::GetUnitAxis error, argc=%d", argc);
            return 0;
        }

        static int GetUnitAxes(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 4) {
                CheckSelf(FMatrix);
                auto X = LuaObject::checkValue<FVector*>(L, 2);
                if (!X) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& XRef = *X;
                auto Y = LuaObject::checkValue<FVector*>(L, 3);
                if (!Y) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& YRef = *Y;
                auto Z = LuaObject::checkValue<FVector*>(L, 4);
                if (!Z) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ZRef = *Z;
                self->GetUnitAxes(XRef, YRef, ZRef);
                LuaObject::push<FVector>(L, "FVector", X);
                LuaObject::push<FVector>(L, "FVector", Y);
                LuaObject::push<FVector>(L, "FVector", Z);
                return 3;
            }
            luaL_error(L, "call FMatrix::GetUnitAxes error, argc=%d", argc);
            return 0;
        }

        static int SetAxis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FMatrix);
                auto i = LuaObject::checkValue<int>(L, 2);
                auto Axis = LuaObject::checkValue<FVector*>(L, 3);
                if (!Axis) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& AxisRef = *Axis;
                self->SetAxis(i, AxisRef);
                return 0;
            }
            luaL_error(L, "call FMatrix::SetAxis error, argc=%d", argc);
            return 0;
        }

        static int SetOrigin(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto NewOrigin = LuaObject::checkValue<FVector*>(L, 2);
                if (!NewOrigin) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NewOriginRef = *NewOrigin;
                self->SetOrigin(NewOriginRef);
                return 0;
            }
            luaL_error(L, "call FMatrix::SetOrigin error, argc=%d", argc);
            return 0;
        }

        static int GetColumn(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto i = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFVector();
                *ret = self->GetColumn(i);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::GetColumn error, argc=%d", argc);
            return 0;
        }

        static int SetColumn(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FMatrix);
                auto i = LuaObject::checkValue<int>(L, 2);
                auto Value = LuaObject::checkValue<FVector*>(L, 3);
                auto ValueVal = *Value;
                self->SetColumn(i, ValueVal);
                return 0;
            }
            luaL_error(L, "call FMatrix::SetColumn error, argc=%d", argc);
            return 0;
        }

        static int ToQuat(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFQuat();
                *ret = self->ToQuat();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::ToQuat error, argc=%d", argc);
            return 0;
        }

        static int GetFrustumNearPlane(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto OuTPln = LuaObject::checkValue<FPlane*>(L, 2);
                if (!OuTPln) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OuTPlnRef = *OuTPln;
                auto ret = self->GetFrustumNearPlane(OuTPlnRef);
                LuaObject::push(L, ret);
                LuaObject::push<FPlane>(L, "FPlane", OuTPln);
                return 2;
            }
            luaL_error(L, "call FMatrix::GetFrustumNearPlane error, argc=%d", argc);
            return 0;
        }

        static int GetFrustumFarPlane(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto OuTPln = LuaObject::checkValue<FPlane*>(L, 2);
                if (!OuTPln) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OuTPlnRef = *OuTPln;
                auto ret = self->GetFrustumFarPlane(OuTPlnRef);
                LuaObject::push(L, ret);
                LuaObject::push<FPlane>(L, "FPlane", OuTPln);
                return 2;
            }
            luaL_error(L, "call FMatrix::GetFrustumFarPlane error, argc=%d", argc);
            return 0;
        }

        static int GetFrustumLeftPlane(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto OuTPln = LuaObject::checkValue<FPlane*>(L, 2);
                if (!OuTPln) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OuTPlnRef = *OuTPln;
                auto ret = self->GetFrustumLeftPlane(OuTPlnRef);
                LuaObject::push(L, ret);
                LuaObject::push<FPlane>(L, "FPlane", OuTPln);
                return 2;
            }
            luaL_error(L, "call FMatrix::GetFrustumLeftPlane error, argc=%d", argc);
            return 0;
        }

        static int GetFrustumRightPlane(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto OuTPln = LuaObject::checkValue<FPlane*>(L, 2);
                if (!OuTPln) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OuTPlnRef = *OuTPln;
                auto ret = self->GetFrustumRightPlane(OuTPlnRef);
                LuaObject::push(L, ret);
                LuaObject::push<FPlane>(L, "FPlane", OuTPln);
                return 2;
            }
            luaL_error(L, "call FMatrix::GetFrustumRightPlane error, argc=%d", argc);
            return 0;
        }

        static int GetFrustumTopPlane(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto OuTPln = LuaObject::checkValue<FPlane*>(L, 2);
                if (!OuTPln) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OuTPlnRef = *OuTPln;
                auto ret = self->GetFrustumTopPlane(OuTPlnRef);
                LuaObject::push(L, ret);
                LuaObject::push<FPlane>(L, "FPlane", OuTPln);
                return 2;
            }
            luaL_error(L, "call FMatrix::GetFrustumTopPlane error, argc=%d", argc);
            return 0;
        }

        static int GetFrustumBottomPlane(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto OuTPln = LuaObject::checkValue<FPlane*>(L, 2);
                if (!OuTPln) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OuTPlnRef = *OuTPln;
                auto ret = self->GetFrustumBottomPlane(OuTPlnRef);
                LuaObject::push(L, ret);
                LuaObject::push<FPlane>(L, "FPlane", OuTPln);
                return 2;
            }
            luaL_error(L, "call FMatrix::GetFrustumBottomPlane error, argc=%d", argc);
            return 0;
        }

        static int Mirror(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FMatrix);
                auto MirrorAxis = LuaObject::checkValue<int>(L, 2);
                auto MirrorAxisVal = (EAxis::Type)MirrorAxis;
                auto FlipAxis = LuaObject::checkValue<int>(L, 3);
                auto FlipAxisVal = (EAxis::Type)FlipAxis;
                self->Mirror(MirrorAxisVal, FlipAxisVal);
                return 0;
            }
            luaL_error(L, "call FMatrix::Mirror error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FMatrix::ToString error, argc=%d", argc);
            return 0;
        }

        static int DebugPrint(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                self->DebugPrint();
                return 0;
            }
            luaL_error(L, "call FMatrix::DebugPrint error, argc=%d", argc);
            return 0;
        }

        static int ComputeHash(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = self->ComputeHash();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FMatrix::ComputeHash error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FMatrix");
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addField(L, "Identity", get_Identity, nullptr, false);
            LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
            LuaObject::addMethod(L, "SetIdentity", SetIdentity, true);
            LuaObject::addMethod(L, "InverseTransformPosition", InverseTransformPosition, true);
            LuaObject::addMethod(L, "InverseTransformVector", InverseTransformVector, true);
            LuaObject::addMethod(L, "GetTransposed", GetTransposed, true);
            LuaObject::addMethod(L, "InverseFast", InverseFast, true);
            LuaObject::addMethod(L, "Inverse", Inverse, true);
            LuaObject::addMethod(L, "TransposeAdjoint", TransposeAdjoint, true);
            LuaObject::addMethod(L, "RemoveTranslation", RemoveTranslation, true);
            LuaObject::addMethod(L, "ConcatTranslation", ConcatTranslation, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "ScaleTranslation", ScaleTranslation, true);
            LuaObject::addMethod(L, "GetOrigin", GetOrigin, true);
            LuaObject::addMethod(L, "GetScaledAxis", GetScaledAxis, true);
            LuaObject::addMethod(L, "GetScaledAxes", GetScaledAxes, true);
            LuaObject::addMethod(L, "GetUnitAxis", GetUnitAxis, true);
            LuaObject::addMethod(L, "GetUnitAxes", GetUnitAxes, true);
            LuaObject::addMethod(L, "SetAxis", SetAxis, true);
            LuaObject::addMethod(L, "SetOrigin", SetOrigin, true);
            LuaObject::addMethod(L, "GetColumn", GetColumn, true);
            LuaObject::addMethod(L, "SetColumn", SetColumn, true);
            LuaObject::addMethod(L, "ToQuat", ToQuat, true);
            LuaObject::addMethod(L, "GetFrustumNearPlane", GetFrustumNearPlane, true);
            LuaObject::addMethod(L, "GetFrustumFarPlane", GetFrustumFarPlane, true);
            LuaObject::addMethod(L, "GetFrustumLeftPlane", GetFrustumLeftPlane, true);
            LuaObject::addMethod(L, "GetFrustumRightPlane", GetFrustumRightPlane, true);
            LuaObject::addMethod(L, "GetFrustumTopPlane", GetFrustumTopPlane, true);
            LuaObject::addMethod(L, "GetFrustumBottomPlane", GetFrustumBottomPlane, true);
            LuaObject::addMethod(L, "Mirror", Mirror, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "DebugPrint", DebugPrint, true);
            LuaObject::addMethod(L, "ComputeHash", ComputeHash, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FMatrix", __ctor, __gc);
        }

    };

    struct FSoftObjectPathWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FSoftObjectPath();
                LuaObject::push<FSoftObjectPath>(L, "FSoftObjectPath", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto Other = LuaObject::checkValue<FSoftObjectPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto self = new FSoftObjectPath(OtherRef);
                LuaObject::push<FSoftObjectPath>(L, "FSoftObjectPath", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InAssetPath = LuaObject::checkValue<FTopLevelAssetPath*>(L, 2);
                auto InAssetPathVal = *InAssetPath;
                auto InSubPathString = LuaObject::checkValue<FString>(L, 3);
                auto self = new FSoftObjectPath(InAssetPathVal, InSubPathString);
                LuaObject::push<FSoftObjectPath>(L, "FSoftObjectPath", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FSoftObjectPath);
            auto ret = __newFSoftObjectPath();
            *ret = *self;
            LuaObject::push<FSoftObjectPath>(L, "FSoftObjectPath", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FSoftObjectPath);
            SLUA_GCSTRUCT(FSoftObjectPath);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FSoftObjectPath);
            if (LuaObject::matchType(L, 2, "FSoftObjectPath")) {
                auto Other = LuaObject::checkValue<FSoftObjectPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = (*self == OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            LuaObject::push(L, false);
            return 1;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::ToString error, argc=%d", argc);
            return 0;
        }

        static int AppendString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FSoftObjectPath);
                auto Builder = LuaObject::checkValue<FString>(L, 2);
                self->AppendString(Builder);
                LuaObject::push(L, Builder);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::AppendString error, argc=%d", argc);
            return 0;
        }

        static int GetAssetPath(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = __newFTopLevelAssetPath();
                *ret = self->GetAssetPath();
                LuaObject::push<FTopLevelAssetPath>(L, "FTopLevelAssetPath", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::GetAssetPath error, argc=%d", argc);
            return 0;
        }

        static int GetWithoutSubPath(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = __newFSoftObjectPath();
                *ret = self->GetWithoutSubPath();
                LuaObject::push<FSoftObjectPath>(L, "FSoftObjectPath", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::GetWithoutSubPath error, argc=%d", argc);
            return 0;
        }

        static int GetAssetPathString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->GetAssetPathString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::GetAssetPathString error, argc=%d", argc);
            return 0;
        }

        static int GetSubPathString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->GetSubPathString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::GetSubPathString error, argc=%d", argc);
            return 0;
        }

        static int SetSubPathString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FSoftObjectPath);
                auto InSubPathString = LuaObject::checkValue<FString>(L, 2);
                self->SetSubPathString(InSubPathString);
                return 0;
            }
            luaL_error(L, "call FSoftObjectPath::SetSubPathString error, argc=%d", argc);
            return 0;
        }

        static int GetLongPackageName(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->GetLongPackageName();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::GetLongPackageName error, argc=%d", argc);
            return 0;
        }

        static int GetAssetName(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->GetAssetName();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::GetAssetName error, argc=%d", argc);
            return 0;
        }

        static int SetPath(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FSoftObjectPath);
                auto Path = LuaObject::checkValue<FString>(L, 2);
                self->SetPath(Path);
                return 0;
            }
            if (argc == 3) {
                CheckSelf(FSoftObjectPath);
                auto InAssetPath = LuaObject::checkValue<FTopLevelAssetPath*>(L, 2);
                if (!InAssetPath) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InAssetPathRef = *InAssetPath;
                auto InSubPathString = LuaObject::checkValue<FString>(L, 3);
                self->SetPath(InAssetPathRef, InSubPathString);
                return 0;
            }
            luaL_error(L, "call FSoftObjectPath::SetPath error, argc=%d", argc);
            return 0;
        }

        static int Reset(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                self->Reset();
                return 0;
            }
            luaL_error(L, "call FSoftObjectPath::Reset error, argc=%d", argc);
            return 0;
        }

        static int IsValid(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->IsValid();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::IsValid error, argc=%d", argc);
            return 0;
        }

        static int IsNull(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->IsNull();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::IsNull error, argc=%d", argc);
            return 0;
        }

        static int IsAsset(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->IsAsset();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::IsAsset error, argc=%d", argc);
            return 0;
        }

        static int IsSubobject(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->IsSubobject();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::IsSubobject error, argc=%d", argc);
            return 0;
        }

        static int LexicalLess(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FSoftObjectPath);
                auto Other = LuaObject::checkValue<FSoftObjectPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = self->LexicalLess(OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::LexicalLess error, argc=%d", argc);
            return 0;
        }

        static int FastLess(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FSoftObjectPath);
                auto Other = LuaObject::checkValue<FSoftObjectPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = self->FastLess(OtherRef);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::FastLess error, argc=%d", argc);
            return 0;
        }

        static int FixupCoreRedirects(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPath);
                auto ret = self->FixupCoreRedirects();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::FixupCoreRedirects error, argc=%d", argc);
            return 0;
        }

        static int GetCurrentTag(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = FSoftObjectPath::GetCurrentTag();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::GetCurrentTag error, argc=%d", argc);
            return 0;
        }

        static int InvalidateTag(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = FSoftObjectPath::InvalidateTag();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPath::InvalidateTag error, argc=%d", argc);
            return 0;
        }

        static int ClearPIEPackageNames(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                FSoftObjectPath::ClearPIEPackageNames();
                return 0;
            }
            luaL_error(L, "call FSoftObjectPath::ClearPIEPackageNames error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FSoftObjectPath");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "AppendString", AppendString, true);
            LuaObject::addMethod(L, "GetAssetPath", GetAssetPath, true);
            LuaObject::addMethod(L, "GetWithoutSubPath", GetWithoutSubPath, true);
            LuaObject::addMethod(L, "GetAssetPathString", GetAssetPathString, true);
            LuaObject::addMethod(L, "GetSubPathString", GetSubPathString, true);
            LuaObject::addMethod(L, "SetSubPathString", SetSubPathString, true);
            LuaObject::addMethod(L, "GetLongPackageName", GetLongPackageName, true);
            LuaObject::addMethod(L, "GetAssetName", GetAssetName, true);
            LuaObject::addMethod(L, "SetPath", SetPath, true);
            LuaObject::addMethod(L, "Reset", Reset, true);
            LuaObject::addMethod(L, "IsValid", IsValid, true);
            LuaObject::addMethod(L, "IsNull", IsNull, true);
            LuaObject::addMethod(L, "IsAsset", IsAsset, true);
            LuaObject::addMethod(L, "IsSubobject", IsSubobject, true);
            LuaObject::addMethod(L, "LexicalLess", LexicalLess, true);
            LuaObject::addMethod(L, "FastLess", FastLess, true);
            LuaObject::addMethod(L, "FixupCoreRedirects", FixupCoreRedirects, true);
            LuaObject::addMethod(L, "GetCurrentTag", GetCurrentTag, false);
            LuaObject::addMethod(L, "InvalidateTag", InvalidateTag, false);
            LuaObject::addMethod(L, "ClearPIEPackageNames", ClearPIEPackageNames, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FSoftObjectPath", __ctor, __gc);
        }

    };

    struct FSoftClassPathWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FSoftClassPath();
                LuaObject::push<FSoftClassPath>(L, "FSoftClassPath", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto Other = LuaObject::checkValue<FSoftClassPath*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto self = new FSoftClassPath(OtherRef);
                LuaObject::push<FSoftClassPath>(L, "FSoftClassPath", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSoftClassPath() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FSoftClassPath);
            auto ret = __newFSoftClassPath();
            *ret = *self;
            LuaObject::push<FSoftClassPath>(L, "FSoftClassPath", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FSoftClassPath);
            SLUA_GCSTRUCT(FSoftClassPath);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newTypeWithBase(L, "FSoftClassPath", std::initializer_list<const char*>{ "FSoftObjectPath" });
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FSoftClassPath", __ctor, __gc);
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

    void* LuaWrapper::checkValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms, int i) {
        auto vptr = _checkStructMap.Find(uss);
        if (vptr != nullptr) {
            return (*vptr)(L, p, parms, i);
        } else {
            return nullptr;
        }
    }

    void LuaWrapper::init(lua_State* L) {
        AutoStack autoStack(L);
        FIntPointStruct = StaticGetBaseStructureInternal(TEXT("IntPoint"));
        if (FIntPointStruct) {
            _pushStructMap.Add(FIntPointStruct, __pushFIntPoint);
            _checkStructMap.Add(FIntPointStruct, __checkFIntPoint);
            FIntPointWrapper::bind(L);
        }

        FLinearColorStruct = StaticGetBaseStructureInternal(TEXT("LinearColor"));
        if (FLinearColorStruct) {
            _pushStructMap.Add(FLinearColorStruct, __pushFLinearColor);
            _checkStructMap.Add(FLinearColorStruct, __checkFLinearColor);
            FLinearColorWrapper::bind(L);
        }

        FColorStruct = StaticGetBaseStructureInternal(TEXT("Color"));
        if (FColorStruct) {
            _pushStructMap.Add(FColorStruct, __pushFColor);
            _checkStructMap.Add(FColorStruct, __checkFColor);
            FColorWrapper::bind(L);
        }

        FRandomStreamStruct = StaticGetBaseStructureInternal(TEXT("RandomStream"));
        if (FRandomStreamStruct) {
            _pushStructMap.Add(FRandomStreamStruct, __pushFRandomStream);
            _checkStructMap.Add(FRandomStreamStruct, __checkFRandomStream);
            FRandomStreamWrapper::bind(L);
        }

        FGuidStruct = StaticGetBaseStructureInternal(TEXT("Guid"));
        if (FGuidStruct) {
            _pushStructMap.Add(FGuidStruct, __pushFGuid);
            _checkStructMap.Add(FGuidStruct, __checkFGuid);
            FGuidWrapper::bind(L);
        }

        FInterpCurvePointVector2DStruct = StaticGetBaseStructureInternal(TEXT("InterpCurvePointVector2D"));
        if (FInterpCurvePointVector2DStruct) {
            _pushStructMap.Add(FInterpCurvePointVector2DStruct, __pushFInterpCurvePointVector2D);
            _checkStructMap.Add(FInterpCurvePointVector2DStruct, __checkFInterpCurvePointVector2D);
            FInterpCurvePointVector2DWrapper::bind(L);
        }

        FInterpCurvePointVectorStruct = StaticGetBaseStructureInternal(TEXT("InterpCurvePointVector"));
        if (FInterpCurvePointVectorStruct) {
            _pushStructMap.Add(FInterpCurvePointVectorStruct, __pushFInterpCurvePointVector);
            _checkStructMap.Add(FInterpCurvePointVectorStruct, __checkFInterpCurvePointVector);
            FInterpCurvePointVectorWrapper::bind(L);
        }

        FInterpCurvePointQuatStruct = StaticGetBaseStructureInternal(TEXT("InterpCurvePointQuat"));
        if (FInterpCurvePointQuatStruct) {
            _pushStructMap.Add(FInterpCurvePointQuatStruct, __pushFInterpCurvePointQuat);
            _checkStructMap.Add(FInterpCurvePointQuatStruct, __checkFInterpCurvePointQuat);
            FInterpCurvePointQuatWrapper::bind(L);
        }

        FInterpCurvePointTwoVectorsStruct = StaticGetBaseStructureInternal(TEXT("InterpCurvePointTwoVectors"));
        if (FInterpCurvePointTwoVectorsStruct) {
            _pushStructMap.Add(FInterpCurvePointTwoVectorsStruct, __pushFInterpCurvePointTwoVectors);
            _checkStructMap.Add(FInterpCurvePointTwoVectorsStruct, __checkFInterpCurvePointTwoVectors);
            FInterpCurvePointTwoVectorsWrapper::bind(L);
        }

        FInterpCurvePointLinearColorStruct = StaticGetBaseStructureInternal(TEXT("InterpCurvePointLinearColor"));
        if (FInterpCurvePointLinearColorStruct) {
            _pushStructMap.Add(FInterpCurvePointLinearColorStruct, __pushFInterpCurvePointLinearColor);
            _checkStructMap.Add(FInterpCurvePointLinearColorStruct, __checkFInterpCurvePointLinearColor);
            FInterpCurvePointLinearColorWrapper::bind(L);
        }

        FFloatRangeBoundStruct = StaticGetBaseStructureInternal(TEXT("FloatRangeBound"));
        if (FFloatRangeBoundStruct) {
            _pushStructMap.Add(FFloatRangeBoundStruct, __pushFFloatRangeBound);
            _checkStructMap.Add(FFloatRangeBoundStruct, __checkFFloatRangeBound);
            FFloatRangeBoundWrapper::bind(L);
        }

        FFloatRangeStruct = StaticGetBaseStructureInternal(TEXT("FloatRange"));
        if (FFloatRangeStruct) {
            _pushStructMap.Add(FFloatRangeStruct, __pushFFloatRange);
            _checkStructMap.Add(FFloatRangeStruct, __checkFFloatRange);
            FFloatRangeWrapper::bind(L);
        }

        FDoubleRangeBoundStruct = StaticGetBaseStructureInternal(TEXT("DoubleRangeBound"));
        if (FDoubleRangeBoundStruct) {
            _pushStructMap.Add(FDoubleRangeBoundStruct, __pushFDoubleRangeBound);
            _checkStructMap.Add(FDoubleRangeBoundStruct, __checkFDoubleRangeBound);
            FDoubleRangeBoundWrapper::bind(L);
        }

        FDoubleRangeStruct = StaticGetBaseStructureInternal(TEXT("DoubleRange"));
        if (FDoubleRangeStruct) {
            _pushStructMap.Add(FDoubleRangeStruct, __pushFDoubleRange);
            _checkStructMap.Add(FDoubleRangeStruct, __checkFDoubleRange);
            FDoubleRangeWrapper::bind(L);
        }

        FInt32RangeBoundStruct = StaticGetBaseStructureInternal(TEXT("Int32RangeBound"));
        if (FInt32RangeBoundStruct) {
            _pushStructMap.Add(FInt32RangeBoundStruct, __pushFInt32RangeBound);
            _checkStructMap.Add(FInt32RangeBoundStruct, __checkFInt32RangeBound);
            FInt32RangeBoundWrapper::bind(L);
        }

        FInt32RangeStruct = StaticGetBaseStructureInternal(TEXT("Int32Range"));
        if (FInt32RangeStruct) {
            _pushStructMap.Add(FInt32RangeStruct, __pushFInt32Range);
            _checkStructMap.Add(FInt32RangeStruct, __checkFInt32Range);
            FInt32RangeWrapper::bind(L);
        }

        FFloatIntervalStruct = StaticGetBaseStructureInternal(TEXT("FloatInterval"));
        if (FFloatIntervalStruct) {
            _pushStructMap.Add(FFloatIntervalStruct, __pushFFloatInterval);
            _checkStructMap.Add(FFloatIntervalStruct, __checkFFloatInterval);
            FFloatIntervalWrapper::bind(L);
        }

        FDoubleIntervalStruct = StaticGetBaseStructureInternal(TEXT("DoubleInterval"));
        if (FDoubleIntervalStruct) {
            _pushStructMap.Add(FDoubleIntervalStruct, __pushFDoubleInterval);
            _checkStructMap.Add(FDoubleIntervalStruct, __checkFDoubleInterval);
            FDoubleIntervalWrapper::bind(L);
        }

        FInt32IntervalStruct = StaticGetBaseStructureInternal(TEXT("Int32Interval"));
        if (FInt32IntervalStruct) {
            _pushStructMap.Add(FInt32IntervalStruct, __pushFInt32Interval);
            _checkStructMap.Add(FInt32IntervalStruct, __checkFInt32Interval);
            FInt32IntervalWrapper::bind(L);
        }

        FFrameNumberStruct = StaticGetBaseStructureInternal(TEXT("FrameNumber"));
        if (FFrameNumberStruct) {
            _pushStructMap.Add(FFrameNumberStruct, __pushFFrameNumber);
            _checkStructMap.Add(FFrameNumberStruct, __checkFFrameNumber);
            FFrameNumberWrapper::bind(L);
        }

        FPrimaryAssetTypeStruct = StaticGetBaseStructureInternal(TEXT("PrimaryAssetType"));
        if (FPrimaryAssetTypeStruct) {
            _pushStructMap.Add(FPrimaryAssetTypeStruct, __pushFPrimaryAssetType);
            _checkStructMap.Add(FPrimaryAssetTypeStruct, __checkFPrimaryAssetType);
            FPrimaryAssetTypeWrapper::bind(L);
        }

        FPrimaryAssetIdStruct = StaticGetBaseStructureInternal(TEXT("PrimaryAssetId"));
        if (FPrimaryAssetIdStruct) {
            _pushStructMap.Add(FPrimaryAssetIdStruct, __pushFPrimaryAssetId);
            _checkStructMap.Add(FPrimaryAssetIdStruct, __checkFPrimaryAssetId);
            FPrimaryAssetIdWrapper::bind(L);
        }

        FDateTimeStruct = StaticGetBaseStructureInternal(TEXT("DateTime"));
        if (FDateTimeStruct) {
            _pushStructMap.Add(FDateTimeStruct, __pushFDateTime);
            _checkStructMap.Add(FDateTimeStruct, __checkFDateTime);
            FDateTimeWrapper::bind(L);
        }

        FTestUninitializedScriptStructMembersTestStruct = StaticGetBaseStructureInternal(TEXT("TestUninitializedScriptStructMembersTest"));
        if (FTestUninitializedScriptStructMembersTestStruct) {
            _pushStructMap.Add(FTestUninitializedScriptStructMembersTestStruct, __pushFTestUninitializedScriptStructMembersTest);
            _checkStructMap.Add(FTestUninitializedScriptStructMembersTestStruct, __checkFTestUninitializedScriptStructMembersTest);
            FTestUninitializedScriptStructMembersTestWrapper::bind(L);
        }

        FTopLevelAssetPathStruct = StaticGetBaseStructureInternal(TEXT("TopLevelAssetPath"));
        if (FTopLevelAssetPathStruct) {
            _pushStructMap.Add(FTopLevelAssetPathStruct, __pushFTopLevelAssetPath);
            _checkStructMap.Add(FTopLevelAssetPathStruct, __checkFTopLevelAssetPath);
            FTopLevelAssetPathWrapper::bind(L);
        }

        FVectorStruct = StaticGetBaseStructureInternal(TEXT("Vector"));
        if (FVectorStruct) {
            _pushStructMap.Add(FVectorStruct, __pushFVector);
            _checkStructMap.Add(FVectorStruct, __checkFVector);
            FVectorWrapper::bind(L);
        }

        FPlaneStruct = StaticGetBaseStructureInternal(TEXT("Plane"));
        if (FPlaneStruct) {
            _pushStructMap.Add(FPlaneStruct, __pushFPlane);
            _checkStructMap.Add(FPlaneStruct, __checkFPlane);
            FPlaneWrapper::bind(L);
        }

        FQuatStruct = StaticGetBaseStructureInternal(TEXT("Quat"));
        if (FQuatStruct) {
            _pushStructMap.Add(FQuatStruct, __pushFQuat);
            _checkStructMap.Add(FQuatStruct, __checkFQuat);
            FQuatWrapper::bind(L);
        }

        FTransformStruct = StaticGetBaseStructureInternal(TEXT("Transform"));
        if (FTransformStruct) {
            _pushStructMap.Add(FTransformStruct, __pushFTransform);
            _checkStructMap.Add(FTransformStruct, __checkFTransform);
            FTransformWrapper::bind(L);
        }

        FMatrixStruct = StaticGetBaseStructureInternal(TEXT("Matrix"));
        if (FMatrixStruct) {
            _pushStructMap.Add(FMatrixStruct, __pushFMatrix);
            _checkStructMap.Add(FMatrixStruct, __checkFMatrix);
            FMatrixWrapper::bind(L);
        }

        FSoftObjectPathStruct = StaticGetBaseStructureInternal(TEXT("SoftObjectPath"));
        if (FSoftObjectPathStruct) {
            _pushStructMap.Add(FSoftObjectPathStruct, __pushFSoftObjectPath);
            _checkStructMap.Add(FSoftObjectPathStruct, __checkFSoftObjectPath);
            FSoftObjectPathWrapper::bind(L);
        }

        FSoftClassPathStruct = StaticGetBaseStructureInternal(TEXT("SoftClassPath"));
        if (FSoftClassPathStruct) {
            _pushStructMap.Add(FSoftClassPathStruct, __pushFSoftClassPath);
            _checkStructMap.Add(FSoftClassPathStruct, __checkFSoftClassPath);
            FSoftClassPathWrapper::bind(L);
        }
    }
