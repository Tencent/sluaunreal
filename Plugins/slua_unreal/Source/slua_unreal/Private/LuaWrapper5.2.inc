
    static UScriptStruct* FIntPointStruct = nullptr;
    static UScriptStruct* FIntVectorStruct = nullptr;
    static UScriptStruct* FIntVector4Struct = nullptr;
    static UScriptStruct* FLinearColorStruct = nullptr;
    static UScriptStruct* FColorStruct = nullptr;
    static UScriptStruct* FRandomStreamStruct = nullptr;
    static UScriptStruct* FGuidStruct = nullptr;
    static UScriptStruct* FFallbackStructStruct = nullptr;
    static UScriptStruct* FInterpCurvePointFloatStruct = nullptr;
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
    static UScriptStruct* FFrameTimeStruct = nullptr;
    static UScriptStruct* FSoftObjectPathStruct = nullptr;
    static UScriptStruct* FSoftClassPathStruct = nullptr;
    static UScriptStruct* FPrimaryAssetTypeStruct = nullptr;
    static UScriptStruct* FPrimaryAssetIdStruct = nullptr;
    static UScriptStruct* FDateTimeStruct = nullptr;
    static UScriptStruct* FTopLevelAssetPathStruct = nullptr;
    static UScriptStruct* FVector2DStruct = nullptr;
    static UScriptStruct* FVectorStruct = nullptr;
    static UScriptStruct* FVector4Struct = nullptr;
    static UScriptStruct* FPlaneStruct = nullptr;
    static UScriptStruct* FQuatStruct = nullptr;
    static UScriptStruct* FRotatorStruct = nullptr;
    static UScriptStruct* FTransformStruct = nullptr;
    static UScriptStruct* FMatrixStruct = nullptr;
    static UScriptStruct* FBox2DStruct = nullptr;
    static UScriptStruct* FRayStruct = nullptr;
    static UScriptStruct* FSphereStruct = nullptr;

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

    static inline FIntVector* __newFIntVector() {
        return new FIntVector();
    }

    static void __pushFIntVector(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFIntVector();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FIntVector>(L, "FIntVector", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFIntVector(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FIntVector*>(L, i);
        if (!v) {
            luaL_error(L, "check FIntVector nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FIntVector4* __newFIntVector4() {
        return new FIntVector4();
    }

    static void __pushFIntVector4(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFIntVector4();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FIntVector4>(L, "FIntVector4", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFIntVector4(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FIntVector4*>(L, i);
        if (!v) {
            luaL_error(L, "check FIntVector4 nil value");
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

    static inline FFallbackStruct* __newFFallbackStruct() {
        return new FFallbackStruct();
    }

    static void __pushFFallbackStruct(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFFallbackStruct();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FFallbackStruct>(L, "FFallbackStruct", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFFallbackStruct(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FFallbackStruct*>(L, i);
        if (!v) {
            luaL_error(L, "check FFallbackStruct nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FInterpCurvePointFloat* __newFInterpCurvePointFloat() {
        return new FInterpCurvePointFloat();
    }

    static void __pushFInterpCurvePointFloat(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFInterpCurvePointFloat();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FInterpCurvePointFloat>(L, "FInterpCurvePointFloat", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFInterpCurvePointFloat(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FInterpCurvePointFloat*>(L, i);
        if (!v) {
            luaL_error(L, "check FInterpCurvePointFloat nil value");
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

    static inline FFrameTime* __newFFrameTime() {
        return new FFrameTime();
    }

    static void __pushFFrameTime(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFFrameTime();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FFrameTime>(L, "FFrameTime", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFFrameTime(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FFrameTime*>(L, i);
        if (!v) {
            luaL_error(L, "check FFrameTime nil value");
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

    static inline FVector2D* __newFVector2D() {
        return new FVector2D();
    }

    static void __pushFVector2D(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFVector2D();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FVector2D>(L, "FVector2D", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFVector2D(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FVector2D*>(L, i);
        if (!v) {
            luaL_error(L, "check FVector2D nil value");
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

    static inline FVector4* __newFVector4() {
        return new FVector4();
    }

    static void __pushFVector4(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFVector4();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FVector4>(L, "FVector4", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFVector4(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FVector4*>(L, i);
        if (!v) {
            luaL_error(L, "check FVector4 nil value");
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

    static inline FRotator* __newFRotator() {
        return new FRotator();
    }

    static void __pushFRotator(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFRotator();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FRotator>(L, "FRotator", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFRotator(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FRotator*>(L, i);
        if (!v) {
            luaL_error(L, "check FRotator nil value");
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

    static inline FBox2D* __newFBox2D() {
        return new FBox2D();
    }

    static void __pushFBox2D(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFBox2D();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FBox2D>(L, "FBox2D", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFBox2D(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FBox2D*>(L, i);
        if (!v) {
            luaL_error(L, "check FBox2D nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FRay* __newFRay() {
        return new FRay();
    }

    static void __pushFRay(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFRay();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FRay>(L, "FRay", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFRay(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FRay*>(L, i);
        if (!v) {
            luaL_error(L, "check FRay nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    static inline FSphere* __newFSphere() {
        return new FSphere();
    }

    static void __pushFSphere(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFSphere();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FSphere>(L, "FSphere", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFSphere(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FSphere*>(L, i);
        if (!v) {
            luaL_error(L, "check FSphere nil value");
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
                auto InXY = LuaObject::checkValue<int>(L, 2);
                auto self = new FIntPoint(InXY);
                LuaObject::push<FIntPoint>(L, "FIntPoint", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InX = LuaObject::checkValue<int>(L, 2);
                auto InY = LuaObject::checkValue<int>(L, 3);
                auto self = new FIntPoint(InX, InY);
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

        static int __mul(lua_State* L) {
            CheckSelf(FIntPoint);
            if (lua_isnumber(L, 2)) {
                auto Scale = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntPoint();
                *ret = (*self * Scale);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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
            if (lua_isnumber(L, 2)) {
                auto Divisor = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntPoint();
                *ret = (*self / Divisor);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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

        static int get_X(lua_State* L) {
            CheckSelf(FIntPoint);
            auto& X = self->X;
            LuaObject::push(L, X);
            return 1;
        }

        static int set_X(lua_State* L) {
            CheckSelf(FIntPoint);
            auto& X = self->X;
            auto XIn = LuaObject::checkValue<int>(L, 2);
            X = XIn;
            LuaObject::push(L, XIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Y(lua_State* L) {
            CheckSelf(FIntPoint);
            auto& Y = self->Y;
            LuaObject::push(L, Y);
            return 1;
        }

        static int set_Y(lua_State* L) {
            CheckSelf(FIntPoint);
            auto& Y = self->Y;
            auto YIn = LuaObject::checkValue<int>(L, 2);
            Y = YIn;
            LuaObject::push(L, YIn);
            SLUA_MARK_NETPROP
            return 1;
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
                auto Divisor = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntPoint();
                *ret = FIntPoint::DivideAndRoundUp(lhsVal, Divisor);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntPoint::DivideAndRoundUp error, argc=%d", argc);
            return 0;
        }

        static int DivideAndRoundDown(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto lhs = LuaObject::checkValue<FIntPoint*>(L, 1);
                auto lhsVal = *lhs;
                auto Divisor = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntPoint();
                *ret = FIntPoint::DivideAndRoundDown(lhsVal, Divisor);
                LuaObject::push<FIntPoint>(L, "FIntPoint", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntPoint::DivideAndRoundDown error, argc=%d", argc);
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
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__div", __div);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addField(L, "X", get_X, set_X, true);
            LuaObject::addField(L, "Y", get_Y, set_Y, true);
            LuaObject::addField(L, "ZeroValue", get_ZeroValue, nullptr, false);
            LuaObject::addField(L, "NoneValue", get_NoneValue, nullptr, false);
            LuaObject::addMethod(L, "ComponentMin", ComponentMin, true);
            LuaObject::addMethod(L, "ComponentMax", ComponentMax, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "DivideAndRoundUp", DivideAndRoundUp, false);
            LuaObject::addMethod(L, "DivideAndRoundDown", DivideAndRoundDown, false);
            LuaObject::addMethod(L, "Num", Num, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FIntPoint", __ctor, __gc);
        }

    };

    struct FIntVectorWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FIntVector();
                LuaObject::push<FIntVector>(L, "FIntVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto InValue = LuaObject::checkValue<int>(L, 2);
                auto self = new FIntVector(InValue);
                LuaObject::push<FIntVector>(L, "FIntVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 4) {
                auto InX = LuaObject::checkValue<int>(L, 2);
                auto InY = LuaObject::checkValue<int>(L, 3);
                auto InZ = LuaObject::checkValue<int>(L, 4);
                auto self = new FIntVector(InX, InY, InZ);
                LuaObject::push<FIntVector>(L, "FIntVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntVector() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FIntVector);
            auto ret = __newFIntVector();
            *ret = *self;
            LuaObject::push<FIntVector>(L, "FIntVector", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FIntVector);
            SLUA_GCSTRUCT(FIntVector);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FIntVector);
            if (LuaObject::matchType(L, 2, "FIntVector")) {
                auto Other = LuaObject::checkValue<FIntVector*>(L, 2);
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

        static int __mul(lua_State* L) {
            CheckSelf(FIntVector);
            if (LuaObject::matchType(L, 2, "FIntVector")) {
                auto Other = LuaObject::checkValue<FIntVector*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntVector();
                *ret = (*self * OtherRef);
                LuaObject::push<FIntVector>(L, "FIntVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (lua_isnumber(L, 2)) {
                auto Scale = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntVector();
                *ret = (*self * Scale);
                LuaObject::push<FIntVector>(L, "FIntVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector operator__mul error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __div(lua_State* L) {
            CheckSelf(FIntVector);
            if (lua_isnumber(L, 2)) {
                auto Divisor = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntVector();
                *ret = (*self / Divisor);
                LuaObject::push<FIntVector>(L, "FIntVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector operator__div error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FIntVector);
            if (LuaObject::matchType(L, 2, "FIntVector")) {
                auto Other = LuaObject::checkValue<FIntVector*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntVector();
                *ret = (*self + OtherRef);
                LuaObject::push<FIntVector>(L, "FIntVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __sub(lua_State* L) {
            CheckSelf(FIntVector);
            if (LuaObject::matchType(L, 2, "FIntVector")) {
                auto Other = LuaObject::checkValue<FIntVector*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntVector();
                *ret = (*self - OtherRef);
                LuaObject::push<FIntVector>(L, "FIntVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int get_X(lua_State* L) {
            CheckSelf(FIntVector);
            auto& X = self->X;
            LuaObject::push(L, X);
            return 1;
        }

        static int set_X(lua_State* L) {
            CheckSelf(FIntVector);
            auto& X = self->X;
            auto XIn = LuaObject::checkValue<int>(L, 2);
            X = XIn;
            LuaObject::push(L, XIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Y(lua_State* L) {
            CheckSelf(FIntVector);
            auto& Y = self->Y;
            LuaObject::push(L, Y);
            return 1;
        }

        static int set_Y(lua_State* L) {
            CheckSelf(FIntVector);
            auto& Y = self->Y;
            auto YIn = LuaObject::checkValue<int>(L, 2);
            Y = YIn;
            LuaObject::push(L, YIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Z(lua_State* L) {
            CheckSelf(FIntVector);
            auto& Z = self->Z;
            LuaObject::push(L, Z);
            return 1;
        }

        static int set_Z(lua_State* L) {
            CheckSelf(FIntVector);
            auto& Z = self->Z;
            auto ZIn = LuaObject::checkValue<int>(L, 2);
            Z = ZIn;
            LuaObject::push(L, ZIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_ZeroValue(lua_State* L) {
            auto& ZeroValue = FIntVector::ZeroValue;
            LuaObject::push<FIntVector>(L, "FIntVector", &ZeroValue);
            return 1;
        }

        static int get_NoneValue(lua_State* L) {
            auto& NoneValue = FIntVector::NoneValue;
            LuaObject::push<FIntVector>(L, "FIntVector", &NoneValue);
            return 1;
        }

        static int IsZero(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FIntVector);
                auto ret = self->IsZero();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FIntVector::IsZero error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FIntVector);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FIntVector::ToString error, argc=%d", argc);
            return 0;
        }

        static int DivideAndRoundUp(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto lhs = LuaObject::checkValue<FIntVector*>(L, 1);
                auto lhsVal = *lhs;
                auto Divisor = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntVector();
                *ret = FIntVector::DivideAndRoundUp(lhsVal, Divisor);
                LuaObject::push<FIntVector>(L, "FIntVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntVector::DivideAndRoundUp error, argc=%d", argc);
            return 0;
        }

        static int Num(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = FIntVector::Num();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FIntVector::Num error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FIntVector");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__div", __div);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addField(L, "X", get_X, set_X, true);
            LuaObject::addField(L, "Y", get_Y, set_Y, true);
            LuaObject::addField(L, "Z", get_Z, set_Z, true);
            LuaObject::addField(L, "ZeroValue", get_ZeroValue, nullptr, false);
            LuaObject::addField(L, "NoneValue", get_NoneValue, nullptr, false);
            LuaObject::addMethod(L, "IsZero", IsZero, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "DivideAndRoundUp", DivideAndRoundUp, false);
            LuaObject::addMethod(L, "Num", Num, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FIntVector", __ctor, __gc);
        }

    };

    struct FIntVector4Wrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FIntVector4();
                LuaObject::push<FIntVector4>(L, "FIntVector4", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto InValue = LuaObject::checkValue<int>(L, 2);
                auto self = new FIntVector4(InValue);
                LuaObject::push<FIntVector4>(L, "FIntVector4", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InValue = LuaObject::checkValue<FIntVector3*>(L, 2);
                if (!InValue) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InValueRef = *InValue;
                auto InW = LuaObject::checkValue<int>(L, 3);
                auto self = new FIntVector4(InValueRef, InW);
                LuaObject::push<FIntVector4>(L, "FIntVector4", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 5) {
                auto InX = LuaObject::checkValue<int>(L, 2);
                auto InY = LuaObject::checkValue<int>(L, 3);
                auto InZ = LuaObject::checkValue<int>(L, 4);
                auto InW = LuaObject::checkValue<int>(L, 5);
                auto self = new FIntVector4(InX, InY, InZ, InW);
                LuaObject::push<FIntVector4>(L, "FIntVector4", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FIntVector4() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FIntVector4);
            auto ret = __newFIntVector4();
            *ret = *self;
            LuaObject::push<FIntVector4>(L, "FIntVector4", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FIntVector4);
            SLUA_GCSTRUCT(FIntVector4);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FIntVector4);
            if (LuaObject::matchType(L, 2, "FIntVector4")) {
                auto Other = LuaObject::checkValue<FIntVector4*>(L, 2);
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

        static int __mul(lua_State* L) {
            CheckSelf(FIntVector4);
            if (LuaObject::matchType(L, 2, "FIntVector4")) {
                auto Other = LuaObject::checkValue<FIntVector4*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntVector4();
                *ret = (*self * OtherRef);
                LuaObject::push<FIntVector4>(L, "FIntVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (lua_isnumber(L, 2)) {
                auto Scale = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntVector4();
                *ret = (*self * Scale);
                LuaObject::push<FIntVector4>(L, "FIntVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector4 operator__mul error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __div(lua_State* L) {
            CheckSelf(FIntVector4);
            if (lua_isnumber(L, 2)) {
                auto Divisor = LuaObject::checkValue<int>(L, 2);
                auto ret = __newFIntVector4();
                *ret = (*self / Divisor);
                LuaObject::push<FIntVector4>(L, "FIntVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector4 operator__div error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FIntVector4);
            if (LuaObject::matchType(L, 2, "FIntVector4")) {
                auto Other = LuaObject::checkValue<FIntVector4*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntVector4();
                *ret = (*self + OtherRef);
                LuaObject::push<FIntVector4>(L, "FIntVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector4 operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __sub(lua_State* L) {
            CheckSelf(FIntVector4);
            if (LuaObject::matchType(L, 2, "FIntVector4")) {
                auto Other = LuaObject::checkValue<FIntVector4*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFIntVector4();
                *ret = (*self - OtherRef);
                LuaObject::push<FIntVector4>(L, "FIntVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FIntVector4 operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int get_X(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& X = self->X;
            LuaObject::push(L, X);
            return 1;
        }

        static int set_X(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& X = self->X;
            auto XIn = LuaObject::checkValue<int>(L, 2);
            X = XIn;
            LuaObject::push(L, XIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Y(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& Y = self->Y;
            LuaObject::push(L, Y);
            return 1;
        }

        static int set_Y(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& Y = self->Y;
            auto YIn = LuaObject::checkValue<int>(L, 2);
            Y = YIn;
            LuaObject::push(L, YIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Z(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& Z = self->Z;
            LuaObject::push(L, Z);
            return 1;
        }

        static int set_Z(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& Z = self->Z;
            auto ZIn = LuaObject::checkValue<int>(L, 2);
            Z = ZIn;
            LuaObject::push(L, ZIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_W(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& W = self->W;
            LuaObject::push(L, W);
            return 1;
        }

        static int set_W(lua_State* L) {
            CheckSelf(FIntVector4);
            auto& W = self->W;
            auto WIn = LuaObject::checkValue<int>(L, 2);
            W = WIn;
            LuaObject::push(L, WIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FIntVector4");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__div", __div);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addField(L, "X", get_X, set_X, true);
            LuaObject::addField(L, "Y", get_Y, set_Y, true);
            LuaObject::addField(L, "Z", get_Z, set_Z, true);
            LuaObject::addField(L, "W", get_W, set_W, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FIntVector4", __ctor, __gc);
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
            SLUA_MARK_NETPROP
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
            SLUA_MARK_NETPROP
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
            SLUA_MARK_NETPROP
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
            SLUA_MARK_NETPROP
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
                auto HVal = (unsigned char)H;
                auto S = LuaObject::checkValue<int>(L, 2);
                auto SVal = (unsigned char)S;
                auto V = LuaObject::checkValue<int>(L, 3);
                auto VVal = (unsigned char)V;
                auto ret = __newFLinearColor();
                *ret = FLinearColor::MakeFromHSV8(HVal, SVal, VVal);
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

        static int get_B(lua_State* L) {
            CheckSelf(FColor);
            auto& B = self->B;
            LuaObject::push(L, B);
            return 1;
        }

        static int set_B(lua_State* L) {
            CheckSelf(FColor);
            auto& B = self->B;
            auto BIn = LuaObject::checkValue<uint8>(L, 2);
            B = BIn;
            LuaObject::push(L, BIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_G(lua_State* L) {
            CheckSelf(FColor);
            auto& G = self->G;
            LuaObject::push(L, G);
            return 1;
        }

        static int set_G(lua_State* L) {
            CheckSelf(FColor);
            auto& G = self->G;
            auto GIn = LuaObject::checkValue<uint8>(L, 2);
            G = GIn;
            LuaObject::push(L, GIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_R(lua_State* L) {
            CheckSelf(FColor);
            auto& R = self->R;
            LuaObject::push(L, R);
            return 1;
        }

        static int set_R(lua_State* L) {
            CheckSelf(FColor);
            auto& R = self->R;
            auto RIn = LuaObject::checkValue<uint8>(L, 2);
            R = RIn;
            LuaObject::push(L, RIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_A(lua_State* L) {
            CheckSelf(FColor);
            auto& A = self->A;
            LuaObject::push(L, A);
            return 1;
        }

        static int set_A(lua_State* L) {
            CheckSelf(FColor);
            auto& A = self->A;
            auto AIn = LuaObject::checkValue<uint8>(L, 2);
            A = AIn;
            LuaObject::push(L, AIn);
            SLUA_MARK_NETPROP
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
            LuaObject::addField(L, "B", get_B, set_B, true);
            LuaObject::addField(L, "G", get_G, set_G, true);
            LuaObject::addField(L, "R", get_R, set_R, true);
            LuaObject::addField(L, "A", get_A, set_A, true);
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
            SLUA_MARK_NETPROP
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
            SLUA_MARK_NETPROP
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
            SLUA_MARK_NETPROP
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
            SLUA_MARK_NETPROP
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

    struct FFallbackStructWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FFallbackStruct() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FFallbackStruct);
            auto ret = __newFFallbackStruct();
            *ret = *self;
            LuaObject::push<FFallbackStruct>(L, "FFallbackStruct", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FFallbackStruct);
            SLUA_GCSTRUCT(FFallbackStruct);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FFallbackStruct");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FFallbackStruct", __ctor, __gc);
        }

    };

    struct FInterpCurvePointFloatWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FInterpCurvePointFloat();
                LuaObject::push<FInterpCurvePointFloat>(L, "FInterpCurvePointFloat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FInterpCurvePointFloat(_a0Val);
                LuaObject::push<FInterpCurvePointFloat>(L, "FInterpCurvePointFloat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<float>(L, 3);
                auto self = new FInterpCurvePointFloat(In, Out);
                LuaObject::push<FInterpCurvePointFloat>(L, "FInterpCurvePointFloat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 6) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<float>(L, 3);
                auto InArriveTangent = LuaObject::checkValue<float>(L, 4);
                auto InLeaveTangent = LuaObject::checkValue<float>(L, 5);
                auto InInterpMode = LuaObject::checkValue<int>(L, 6);
                auto InInterpModeVal = (const EInterpCurveMode)InInterpMode;
                auto self = new FInterpCurvePointFloat(In, Out, InArriveTangent, InLeaveTangent, InInterpModeVal);
                LuaObject::push<FInterpCurvePointFloat>(L, "FInterpCurvePointFloat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FInterpCurvePointFloat() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto ret = __newFInterpCurvePointFloat();
            *ret = *self;
            LuaObject::push<FInterpCurvePointFloat>(L, "FInterpCurvePointFloat", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FInterpCurvePointFloat);
            SLUA_GCSTRUCT(FInterpCurvePointFloat);
            return 0;
        }

        static int get_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& InVal = self->InVal;
            LuaObject::push(L, InVal);
            return 1;
        }

        static int set_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& InVal = self->InVal;
            auto InValIn = LuaObject::checkValue<float>(L, 2);
            InVal = InValIn;
            LuaObject::push(L, InValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& OutVal = self->OutVal;
            LuaObject::push(L, OutVal);
            return 1;
        }

        static int set_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& OutVal = self->OutVal;
            auto OutValIn = LuaObject::checkValue<float>(L, 2);
            OutVal = OutValIn;
            LuaObject::push(L, OutValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& ArriveTangent = self->ArriveTangent;
            LuaObject::push(L, ArriveTangent);
            return 1;
        }

        static int set_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& ArriveTangent = self->ArriveTangent;
            auto ArriveTangentIn = LuaObject::checkValue<float>(L, 2);
            ArriveTangent = ArriveTangentIn;
            LuaObject::push(L, ArriveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& LeaveTangent = self->LeaveTangent;
            LuaObject::push(L, LeaveTangent);
            return 1;
        }

        static int set_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointFloat);
            auto& LeaveTangent = self->LeaveTangent;
            auto LeaveTangentIn = LuaObject::checkValue<float>(L, 2);
            LeaveTangent = LeaveTangentIn;
            LuaObject::push(L, LeaveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int IsCurveKey(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FInterpCurvePointFloat);
                auto ret = self->IsCurveKey();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FInterpCurvePointFloat::IsCurveKey error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointFloat");
            LuaObject::addField(L, "InVal", get_InVal, set_InVal, true);
            LuaObject::addField(L, "OutVal", get_OutVal, set_OutVal, true);
            LuaObject::addField(L, "ArriveTangent", get_ArriveTangent, set_ArriveTangent, true);
            LuaObject::addField(L, "LeaveTangent", get_LeaveTangent, set_LeaveTangent, true);
            LuaObject::addMethod(L, "IsCurveKey", IsCurveKey, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointFloat", __ctor, __gc);
        }

    };

    struct FInterpCurvePointVector2DWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FInterpCurvePointVector2D();
                LuaObject::push<FInterpCurvePointVector2D>(L, "FInterpCurvePointVector2D", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FInterpCurvePointVector2D(_a0Val);
                LuaObject::push<FInterpCurvePointVector2D>(L, "FInterpCurvePointVector2D", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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

        static int get_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointVector2D);
            auto& InVal = self->InVal;
            LuaObject::push(L, InVal);
            return 1;
        }

        static int set_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointVector2D);
            auto& InVal = self->InVal;
            auto InValIn = LuaObject::checkValue<float>(L, 2);
            InVal = InValIn;
            LuaObject::push(L, InValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int IsCurveKey(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FInterpCurvePointVector2D);
                auto ret = self->IsCurveKey();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FInterpCurvePointVector2D::IsCurveKey error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointVector2D");
            LuaObject::addField(L, "InVal", get_InVal, set_InVal, true);
            LuaObject::addMethod(L, "IsCurveKey", IsCurveKey, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointVector2D", __ctor, __gc);
        }

    };

    struct FInterpCurvePointVectorWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FInterpCurvePointVector();
                LuaObject::push<FInterpCurvePointVector>(L, "FInterpCurvePointVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FInterpCurvePointVector(_a0Val);
                LuaObject::push<FInterpCurvePointVector>(L, "FInterpCurvePointVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<FVector*>(L, 3);
                auto OutVal = *Out;
                auto self = new FInterpCurvePointVector(In, OutVal);
                LuaObject::push<FInterpCurvePointVector>(L, "FInterpCurvePointVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 6) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<FVector*>(L, 3);
                auto OutVal = *Out;
                auto InArriveTangent = LuaObject::checkValue<FVector*>(L, 4);
                auto InArriveTangentVal = *InArriveTangent;
                auto InLeaveTangent = LuaObject::checkValue<FVector*>(L, 5);
                auto InLeaveTangentVal = *InLeaveTangent;
                auto InInterpMode = LuaObject::checkValue<int>(L, 6);
                auto InInterpModeVal = (const EInterpCurveMode)InInterpMode;
                auto self = new FInterpCurvePointVector(In, OutVal, InArriveTangentVal, InLeaveTangentVal, InInterpModeVal);
                LuaObject::push<FInterpCurvePointVector>(L, "FInterpCurvePointVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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

        static int get_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& InVal = self->InVal;
            LuaObject::push(L, InVal);
            return 1;
        }

        static int set_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& InVal = self->InVal;
            auto InValIn = LuaObject::checkValue<float>(L, 2);
            InVal = InValIn;
            LuaObject::push(L, InValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& OutVal = self->OutVal;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FVector>(L, udptr->parent ? udptr->parent : self, "FVector", &OutVal, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& OutVal = self->OutVal;
            auto OutValIn = LuaObject::checkValue<FVector*>(L, 2);
            OutVal = *OutValIn;
            LuaObject::push<FVector>(L, "FVector", OutValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& ArriveTangent = self->ArriveTangent;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FVector>(L, udptr->parent ? udptr->parent : self, "FVector", &ArriveTangent, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& ArriveTangent = self->ArriveTangent;
            auto ArriveTangentIn = LuaObject::checkValue<FVector*>(L, 2);
            ArriveTangent = *ArriveTangentIn;
            LuaObject::push<FVector>(L, "FVector", ArriveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& LeaveTangent = self->LeaveTangent;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FVector>(L, udptr->parent ? udptr->parent : self, "FVector", &LeaveTangent, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointVector);
            auto& LeaveTangent = self->LeaveTangent;
            auto LeaveTangentIn = LuaObject::checkValue<FVector*>(L, 2);
            LeaveTangent = *LeaveTangentIn;
            LuaObject::push<FVector>(L, "FVector", LeaveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int IsCurveKey(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FInterpCurvePointVector);
                auto ret = self->IsCurveKey();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FInterpCurvePointVector::IsCurveKey error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointVector");
            LuaObject::addField(L, "InVal", get_InVal, set_InVal, true);
            LuaObject::addField(L, "OutVal", get_OutVal, set_OutVal, true);
            LuaObject::addField(L, "ArriveTangent", get_ArriveTangent, set_ArriveTangent, true);
            LuaObject::addField(L, "LeaveTangent", get_LeaveTangent, set_LeaveTangent, true);
            LuaObject::addMethod(L, "IsCurveKey", IsCurveKey, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointVector", __ctor, __gc);
        }

    };

    struct FInterpCurvePointQuatWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FInterpCurvePointQuat();
                LuaObject::push<FInterpCurvePointQuat>(L, "FInterpCurvePointQuat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FInterpCurvePointQuat(_a0Val);
                LuaObject::push<FInterpCurvePointQuat>(L, "FInterpCurvePointQuat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<FQuat*>(L, 3);
                auto OutVal = *Out;
                auto self = new FInterpCurvePointQuat(In, OutVal);
                LuaObject::push<FInterpCurvePointQuat>(L, "FInterpCurvePointQuat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 6) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<FQuat*>(L, 3);
                auto OutVal = *Out;
                auto InArriveTangent = LuaObject::checkValue<FQuat*>(L, 4);
                auto InArriveTangentVal = *InArriveTangent;
                auto InLeaveTangent = LuaObject::checkValue<FQuat*>(L, 5);
                auto InLeaveTangentVal = *InLeaveTangent;
                auto InInterpMode = LuaObject::checkValue<int>(L, 6);
                auto InInterpModeVal = (const EInterpCurveMode)InInterpMode;
                auto self = new FInterpCurvePointQuat(In, OutVal, InArriveTangentVal, InLeaveTangentVal, InInterpModeVal);
                LuaObject::push<FInterpCurvePointQuat>(L, "FInterpCurvePointQuat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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

        static int get_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& InVal = self->InVal;
            LuaObject::push(L, InVal);
            return 1;
        }

        static int set_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& InVal = self->InVal;
            auto InValIn = LuaObject::checkValue<float>(L, 2);
            InVal = InValIn;
            LuaObject::push(L, InValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& OutVal = self->OutVal;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FQuat>(L, udptr->parent ? udptr->parent : self, "FQuat", &OutVal, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& OutVal = self->OutVal;
            auto OutValIn = LuaObject::checkValue<FQuat*>(L, 2);
            OutVal = *OutValIn;
            LuaObject::push<FQuat>(L, "FQuat", OutValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& ArriveTangent = self->ArriveTangent;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FQuat>(L, udptr->parent ? udptr->parent : self, "FQuat", &ArriveTangent, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& ArriveTangent = self->ArriveTangent;
            auto ArriveTangentIn = LuaObject::checkValue<FQuat*>(L, 2);
            ArriveTangent = *ArriveTangentIn;
            LuaObject::push<FQuat>(L, "FQuat", ArriveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& LeaveTangent = self->LeaveTangent;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FQuat>(L, udptr->parent ? udptr->parent : self, "FQuat", &LeaveTangent, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointQuat);
            auto& LeaveTangent = self->LeaveTangent;
            auto LeaveTangentIn = LuaObject::checkValue<FQuat*>(L, 2);
            LeaveTangent = *LeaveTangentIn;
            LuaObject::push<FQuat>(L, "FQuat", LeaveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int IsCurveKey(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FInterpCurvePointQuat);
                auto ret = self->IsCurveKey();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FInterpCurvePointQuat::IsCurveKey error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointQuat");
            LuaObject::addField(L, "InVal", get_InVal, set_InVal, true);
            LuaObject::addField(L, "OutVal", get_OutVal, set_OutVal, true);
            LuaObject::addField(L, "ArriveTangent", get_ArriveTangent, set_ArriveTangent, true);
            LuaObject::addField(L, "LeaveTangent", get_LeaveTangent, set_LeaveTangent, true);
            LuaObject::addMethod(L, "IsCurveKey", IsCurveKey, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointQuat", __ctor, __gc);
        }

    };

    struct FInterpCurvePointTwoVectorsWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FInterpCurvePointTwoVectors();
                LuaObject::push<FInterpCurvePointTwoVectors>(L, "FInterpCurvePointTwoVectors", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FInterpCurvePointTwoVectors(_a0Val);
                LuaObject::push<FInterpCurvePointTwoVectors>(L, "FInterpCurvePointTwoVectors", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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

        static int get_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointTwoVectors);
            auto& InVal = self->InVal;
            LuaObject::push(L, InVal);
            return 1;
        }

        static int set_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointTwoVectors);
            auto& InVal = self->InVal;
            auto InValIn = LuaObject::checkValue<float>(L, 2);
            InVal = InValIn;
            LuaObject::push(L, InValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int IsCurveKey(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FInterpCurvePointTwoVectors);
                auto ret = self->IsCurveKey();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FInterpCurvePointTwoVectors::IsCurveKey error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointTwoVectors");
            LuaObject::addField(L, "InVal", get_InVal, set_InVal, true);
            LuaObject::addMethod(L, "IsCurveKey", IsCurveKey, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FInterpCurvePointTwoVectors", __ctor, __gc);
        }

    };

    struct FInterpCurvePointLinearColorWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FInterpCurvePointLinearColor();
                LuaObject::push<FInterpCurvePointLinearColor>(L, "FInterpCurvePointLinearColor", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FInterpCurvePointLinearColor(_a0Val);
                LuaObject::push<FInterpCurvePointLinearColor>(L, "FInterpCurvePointLinearColor", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<FLinearColor*>(L, 3);
                auto OutVal = *Out;
                auto self = new FInterpCurvePointLinearColor(In, OutVal);
                LuaObject::push<FInterpCurvePointLinearColor>(L, "FInterpCurvePointLinearColor", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 6) {
                auto In = LuaObject::checkValue<float>(L, 2);
                auto Out = LuaObject::checkValue<FLinearColor*>(L, 3);
                auto OutVal = *Out;
                auto InArriveTangent = LuaObject::checkValue<FLinearColor*>(L, 4);
                auto InArriveTangentVal = *InArriveTangent;
                auto InLeaveTangent = LuaObject::checkValue<FLinearColor*>(L, 5);
                auto InLeaveTangentVal = *InLeaveTangent;
                auto InInterpMode = LuaObject::checkValue<int>(L, 6);
                auto InInterpModeVal = (const EInterpCurveMode)InInterpMode;
                auto self = new FInterpCurvePointLinearColor(In, OutVal, InArriveTangentVal, InLeaveTangentVal, InInterpModeVal);
                LuaObject::push<FInterpCurvePointLinearColor>(L, "FInterpCurvePointLinearColor", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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

        static int get_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& InVal = self->InVal;
            LuaObject::push(L, InVal);
            return 1;
        }

        static int set_InVal(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& InVal = self->InVal;
            auto InValIn = LuaObject::checkValue<float>(L, 2);
            InVal = InValIn;
            LuaObject::push(L, InValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& OutVal = self->OutVal;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FLinearColor>(L, udptr->parent ? udptr->parent : self, "FLinearColor", &OutVal, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_OutVal(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& OutVal = self->OutVal;
            auto OutValIn = LuaObject::checkValue<FLinearColor*>(L, 2);
            OutVal = *OutValIn;
            LuaObject::push<FLinearColor>(L, "FLinearColor", OutValIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& ArriveTangent = self->ArriveTangent;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FLinearColor>(L, udptr->parent ? udptr->parent : self, "FLinearColor", &ArriveTangent, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_ArriveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& ArriveTangent = self->ArriveTangent;
            auto ArriveTangentIn = LuaObject::checkValue<FLinearColor*>(L, 2);
            ArriveTangent = *ArriveTangentIn;
            LuaObject::push<FLinearColor>(L, "FLinearColor", ArriveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& LeaveTangent = self->LeaveTangent;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FLinearColor>(L, udptr->parent ? udptr->parent : self, "FLinearColor", &LeaveTangent, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_LeaveTangent(lua_State* L) {
            CheckSelf(FInterpCurvePointLinearColor);
            auto& LeaveTangent = self->LeaveTangent;
            auto LeaveTangentIn = LuaObject::checkValue<FLinearColor*>(L, 2);
            LeaveTangent = *LeaveTangentIn;
            LuaObject::push<FLinearColor>(L, "FLinearColor", LeaveTangentIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int IsCurveKey(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FInterpCurvePointLinearColor);
                auto ret = self->IsCurveKey();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FInterpCurvePointLinearColor::IsCurveKey error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FInterpCurvePointLinearColor");
            LuaObject::addField(L, "InVal", get_InVal, set_InVal, true);
            LuaObject::addField(L, "OutVal", get_OutVal, set_OutVal, true);
            LuaObject::addField(L, "ArriveTangent", get_ArriveTangent, set_ArriveTangent, true);
            LuaObject::addField(L, "LeaveTangent", get_LeaveTangent, set_LeaveTangent, true);
            LuaObject::addMethod(L, "IsCurveKey", IsCurveKey, true);
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
                auto InValue = LuaObject::checkValue<double>(L, 2);
                auto self = new FDoubleRangeBound(InValue);
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
                auto Value = LuaObject::checkValue<double>(L, 1);
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
                auto Value = LuaObject::checkValue<double>(L, 1);
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
                auto A = LuaObject::checkValue<double>(L, 2);
                auto self = new FDoubleRange(A);
                LuaObject::push<FDoubleRange>(L, "FDoubleRange", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto A = LuaObject::checkValue<double>(L, 2);
                auto B = LuaObject::checkValue<double>(L, 3);
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
                auto Value = LuaObject::checkValue<double>(L, 1);
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
                auto Value = LuaObject::checkValue<double>(L, 1);
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
                auto InMin = LuaObject::checkValue<double>(L, 2);
                auto InMax = LuaObject::checkValue<double>(L, 3);
                auto self = new FDoubleInterval(InMin, InMax);
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
            SLUA_MARK_NETPROP
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

    struct FFrameTimeWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FFrameTime();
                LuaObject::push<FFrameTime>(L, "FFrameTime", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto InFrameNumber = LuaObject::checkValue<FFrameNumber*>(L, 2);
                auto InFrameNumberVal = *InFrameNumber;
                auto self = new FFrameTime(InFrameNumberVal);
                LuaObject::push<FFrameTime>(L, "FFrameTime", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InFrameNumber = LuaObject::checkValue<FFrameNumber*>(L, 2);
                auto InFrameNumberVal = *InFrameNumber;
                auto InSubFrame = LuaObject::checkValue<float>(L, 3);
                auto self = new FFrameTime(InFrameNumberVal, InSubFrame);
                LuaObject::push<FFrameTime>(L, "FFrameTime", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFrameTime() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FFrameTime);
            auto ret = __newFFrameTime();
            *ret = *self;
            LuaObject::push<FFrameTime>(L, "FFrameTime", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FFrameTime);
            SLUA_GCSTRUCT(FFrameTime);
            return 0;
        }

        static int get_FrameNumber(lua_State* L) {
            CheckSelf(FFrameTime);
            auto& FrameNumber = self->FrameNumber;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FFrameNumber>(L, udptr->parent ? udptr->parent : self, "FFrameNumber", &FrameNumber, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_FrameNumber(lua_State* L) {
            CheckSelf(FFrameTime);
            auto& FrameNumber = self->FrameNumber;
            auto FrameNumberIn = LuaObject::checkValue<FFrameNumber*>(L, 2);
            FrameNumber = *FrameNumberIn;
            LuaObject::push<FFrameNumber>(L, "FFrameNumber", FrameNumberIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_MaxSubframe(lua_State* L) {
            auto& MaxSubframe = FFrameTime::MaxSubframe;
            LuaObject::push(L, MaxSubframe);
            return 1;
        }

        static int GetFrame(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FFrameTime);
                auto ret = __newFFrameNumber();
                *ret = self->GetFrame();
                LuaObject::push<FFrameNumber>(L, "FFrameNumber", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFrameTime::GetFrame error, argc=%d", argc);
            return 0;
        }

        static int GetSubFrame(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FFrameTime);
                auto ret = self->GetSubFrame();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FFrameTime::GetSubFrame error, argc=%d", argc);
            return 0;
        }

        static int FloorToFrame(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FFrameTime);
                auto ret = __newFFrameNumber();
                *ret = self->FloorToFrame();
                LuaObject::push<FFrameNumber>(L, "FFrameNumber", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFrameTime::FloorToFrame error, argc=%d", argc);
            return 0;
        }

        static int CeilToFrame(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FFrameTime);
                auto ret = __newFFrameNumber();
                *ret = self->CeilToFrame();
                LuaObject::push<FFrameNumber>(L, "FFrameNumber", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFrameTime::CeilToFrame error, argc=%d", argc);
            return 0;
        }

        static int RoundToFrame(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FFrameTime);
                auto ret = __newFFrameNumber();
                *ret = self->RoundToFrame();
                LuaObject::push<FFrameNumber>(L, "FFrameNumber", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFrameTime::RoundToFrame error, argc=%d", argc);
            return 0;
        }

        static int AsDecimal(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FFrameTime);
                auto ret = self->AsDecimal();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FFrameTime::AsDecimal error, argc=%d", argc);
            return 0;
        }

        static int FromDecimal(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto InDecimalFrame = LuaObject::checkValue<double>(L, 1);
                auto ret = __newFFrameTime();
                *ret = FFrameTime::FromDecimal(InDecimalFrame);
                LuaObject::push<FFrameTime>(L, "FFrameTime", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FFrameTime::FromDecimal error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FFrameTime");
            LuaObject::addField(L, "FrameNumber", get_FrameNumber, set_FrameNumber, true);
            LuaObject::addField(L, "MaxSubframe", get_MaxSubframe, nullptr, false);
            LuaObject::addMethod(L, "GetFrame", GetFrame, true);
            LuaObject::addMethod(L, "GetSubFrame", GetSubFrame, true);
            LuaObject::addMethod(L, "FloorToFrame", FloorToFrame, true);
            LuaObject::addMethod(L, "CeilToFrame", CeilToFrame, true);
            LuaObject::addMethod(L, "RoundToFrame", RoundToFrame, true);
            LuaObject::addMethod(L, "AsDecimal", AsDecimal, true);
            LuaObject::addMethod(L, "FromDecimal", FromDecimal, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FFrameTime", __ctor, __gc);
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
                auto Path = LuaObject::checkValue<const char*>(L, 2);
                auto PathVal = FString(UTF8_TO_TCHAR(Path));
                self->SetPath(*PathVal);
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
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FPrimaryAssetType>(L, udptr->parent ? udptr->parent : self, "FPrimaryAssetType", &PrimaryAssetType, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_PrimaryAssetType(lua_State* L) {
            CheckSelf(FPrimaryAssetId);
            auto& PrimaryAssetType = self->PrimaryAssetType;
            auto PrimaryAssetTypeIn = LuaObject::checkValue<FPrimaryAssetType*>(L, 2);
            PrimaryAssetType = *PrimaryAssetTypeIn;
            LuaObject::push<FPrimaryAssetType>(L, "FPrimaryAssetType", PrimaryAssetTypeIn);
            SLUA_MARK_NETPROP
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
            if (argc == 2) {
                auto TypeAndName = LuaObject::checkValue<const char*>(L, 1);
                auto TypeAndNameVal = FString(UTF8_TO_TCHAR(TypeAndName));
                auto Len = LuaObject::checkValue<int>(L, 2);
                auto LenVal = (unsigned int)Len;
                auto ret = __newFPrimaryAssetId();
                *ret = FPrimaryAssetId::ParseTypeAndName(*TypeAndNameVal, LenVal);
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
                auto InTicksVal = (long long)InTicks;
                auto self = new FDateTime(InTicksVal);
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
            if (argc == 2) {
                CheckSelf(FDateTime);
                auto Format = LuaObject::checkValue<const char*>(L, 2);
                auto FormatVal = FString(UTF8_TO_TCHAR(Format));
                auto ret = self->ToString(*FormatVal);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::ToString error, argc=%d", argc);
            return 0;
        }

        static int ToFormattedString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FDateTime);
                auto Format = LuaObject::checkValue<const char*>(L, 2);
                auto FormatVal = FString(UTF8_TO_TCHAR(Format));
                auto ret = self->ToFormattedString(*FormatVal);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FDateTime::ToFormattedString error, argc=%d", argc);
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
                auto JulianDay = LuaObject::checkValue<double>(L, 1);
                auto ret = __newFDateTime();
                *ret = FDateTime::FromJulianDay(JulianDay);
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
                auto UnixTimeVal = (long long)UnixTime;
                auto ret = __newFDateTime();
                *ret = FDateTime::FromUnixTimestamp(UnixTimeVal);
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

        static int ParseIso8601(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto DateTimeString = LuaObject::checkValue<const char*>(L, 1);
                auto DateTimeStringVal = FString(UTF8_TO_TCHAR(DateTimeString));
                auto OutDateTime = LuaObject::checkValue<FDateTime*>(L, 2);
                if (!OutDateTime) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OutDateTimeRef = *OutDateTime;
                auto ret = FDateTime::ParseIso8601(*DateTimeStringVal, OutDateTimeRef);
                LuaObject::push(L, ret);
                LuaObject::push<FDateTime>(L, "FDateTime", OutDateTime);
                return 2;
            }
            luaL_error(L, "call FDateTime::ParseIso8601 error, argc=%d", argc);
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
            LuaObject::addMethod(L, "ToFormattedString", ToFormattedString, true);
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
            LuaObject::addMethod(L, "ParseIso8601", ParseIso8601, false);
            LuaObject::addMethod(L, "Today", Today, false);
            LuaObject::addMethod(L, "UtcNow", UtcNow, false);
            LuaObject::addMethod(L, "Validate", Validate, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FDateTime", __ctor, __gc);
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

    struct FVector2DWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FVector2D() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FVector2D);
            auto ret = __newFVector2D();
            *ret = *self;
            LuaObject::push<FVector2D>(L, "FVector2D", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FVector2D);
            SLUA_GCSTRUCT(FVector2D);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FVector2D");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FVector2D", __ctor, __gc);
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
                auto InF = LuaObject::checkValue<double>(L, 2);
                auto self = new FVector(InF);
                LuaObject::push<FVector>(L, "FVector", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 4) {
                auto InX = LuaObject::checkValue<double>(L, 2);
                auto InY = LuaObject::checkValue<double>(L, 3);
                auto InZ = LuaObject::checkValue<double>(L, 4);
                auto self = new FVector(InX, InY, InZ);
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

        static int get_X(lua_State* L) {
            CheckSelf(FVector);
            auto& X = self->X;
            LuaObject::push(L, X);
            return 1;
        }

        static int set_X(lua_State* L) {
            CheckSelf(FVector);
            auto& X = self->X;
            auto XIn = LuaObject::checkValue<double>(L, 2);
            X = XIn;
            LuaObject::push(L, XIn);
            SLUA_MARK_NETPROP
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
            auto YIn = LuaObject::checkValue<double>(L, 2);
            Y = YIn;
            LuaObject::push(L, YIn);
            SLUA_MARK_NETPROP
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
            auto ZIn = LuaObject::checkValue<double>(L, 2);
            Z = ZIn;
            LuaObject::push(L, ZIn);
            SLUA_MARK_NETPROP
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

        static int Equals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = self->AllComponentsEqual(Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector::AllComponentsEqual error, argc=%d", argc);
            return 0;
        }

        static int SetComponentForAxis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto Axis = LuaObject::checkValue<int>(L, 2);
                auto AxisVal = (EAxis::Type)Axis;
                auto Component = LuaObject::checkValue<double>(L, 3);
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
                auto InX = LuaObject::checkValue<double>(L, 2);
                auto InY = LuaObject::checkValue<double>(L, 3);
                auto InZ = LuaObject::checkValue<double>(L, 4);
                self->Set(InX, InY, InZ);
                return 0;
            }
            luaL_error(L, "call FVector::Set error, argc=%d", argc);
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

        static int IsNearlyZero(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
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

        static int IsUnit(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto LengthSquaredTolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = self->IsUnit(LengthSquaredTolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector::IsUnit error, argc=%d", argc);
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

        static int Normalize(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = self->Normalize(Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector::Normalize error, argc=%d", argc);
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

        static int GetSafeNormal(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ResultIfZero = LuaObject::checkValue<FVector*>(L, 3);
                if (!ResultIfZero) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ResultIfZeroRef = *ResultIfZero;
                auto ret = __newFVector();
                *ret = self->GetSafeNormal(Tolerance, ResultIfZeroRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::GetSafeNormal error, argc=%d", argc);
            return 0;
        }

        static int GetSafeNormal2D(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ResultIfZero = LuaObject::checkValue<FVector*>(L, 3);
                if (!ResultIfZero) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ResultIfZeroRef = *ResultIfZero;
                auto ret = __newFVector();
                *ret = self->GetSafeNormal2D(Tolerance, ResultIfZeroRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::GetSafeNormal2D error, argc=%d", argc);
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
                auto OutLength = LuaObject::checkValue<double>(L, 3);
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

        static int GridSnap(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector);
                auto GridSz = LuaObject::checkValue<double>(L, 2);
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
                auto Radius = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFVector();
                *ret = self->BoundToCube(Radius);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::BoundToCube error, argc=%d", argc);
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

        static int GetClampedToSize(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto Min = LuaObject::checkValue<double>(L, 2);
                auto Max = LuaObject::checkValue<double>(L, 3);
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
                auto Min = LuaObject::checkValue<double>(L, 2);
                auto Max = LuaObject::checkValue<double>(L, 3);
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
                auto MaxSize = LuaObject::checkValue<double>(L, 2);
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
                auto MaxSize = LuaObject::checkValue<double>(L, 2);
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto Radius = LuaObject::checkValue<double>(L, 3);
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
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
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

        static int RotateAngleAxis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto AngleDeg = LuaObject::checkValue<double>(L, 2);
                auto Axis = LuaObject::checkValue<FVector*>(L, 3);
                if (!Axis) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& AxisRef = *Axis;
                auto ret = __newFVector();
                *ret = self->RotateAngleAxis(AngleDeg, AxisRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::RotateAngleAxis error, argc=%d", argc);
            return 0;
        }

        static int RotateAngleAxisRad(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector);
                auto AngleRad = LuaObject::checkValue<double>(L, 2);
                auto Axis = LuaObject::checkValue<FVector*>(L, 3);
                if (!Axis) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& AxisRef = *Axis;
                auto ret = __newFVector();
                *ret = self->RotateAngleAxisRad(AngleRad, AxisRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector::RotateAngleAxisRad error, argc=%d", argc);
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

        static int SlerpVectorToDirection(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto V = LuaObject::checkValue<FVector*>(L, 1);
                if (!V) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto Direction = LuaObject::checkValue<FVector*>(L, 2);
                if (!Direction) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& DirectionRef = *Direction;
                auto Alpha = LuaObject::checkValue<double>(L, 3);
                auto ret = __newFVector();
                *ret = FVector::SlerpVectorToDirection(VRef, DirectionRef, Alpha);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                LuaObject::push<FVector>(L, "FVector", V);
                LuaObject::push<FVector>(L, "FVector", Direction);
                return 3;
            }
            luaL_error(L, "call FVector::SlerpVectorToDirection error, argc=%d", argc);
            return 0;
        }

        static int SlerpNormals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto NormalA = LuaObject::checkValue<FVector*>(L, 1);
                if (!NormalA) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NormalARef = *NormalA;
                auto NormalB = LuaObject::checkValue<FVector*>(L, 2);
                if (!NormalB) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NormalBRef = *NormalB;
                auto Alpha = LuaObject::checkValue<double>(L, 3);
                auto ret = __newFVector();
                *ret = FVector::SlerpNormals(NormalARef, NormalBRef, Alpha);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                LuaObject::push<FVector>(L, "FVector", NormalA);
                LuaObject::push<FVector>(L, "FVector", NormalB);
                return 3;
            }
            luaL_error(L, "call FVector::SlerpNormals error, argc=%d", argc);
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

        static int PointsAreNear(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto Point1 = LuaObject::checkValue<FVector*>(L, 1);
                if (!Point1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Point1Ref = *Point1;
                auto Point2 = LuaObject::checkValue<FVector*>(L, 2);
                if (!Point2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Point2Ref = *Point2;
                auto Dist = LuaObject::checkValue<double>(L, 3);
                auto ret = FVector::PointsAreNear(Point1Ref, Point2Ref, Dist);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector::PointsAreNear error, argc=%d", argc);
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

        static int Parallel(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
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
                auto ParallelCosineThreshold = LuaObject::checkValue<double>(L, 3);
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
                auto ParallelCosineThreshold = LuaObject::checkValue<double>(L, 3);
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
                auto OrthogonalCosineThreshold = LuaObject::checkValue<double>(L, 3);
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
                if (!Base1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Base1Ref = *Base1;
                auto Normal1 = LuaObject::checkValue<FVector*>(L, 2);
                if (!Normal1) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Normal1Ref = *Normal1;
                auto Base2 = LuaObject::checkValue<FVector*>(L, 3);
                if (!Base2) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Base2Ref = *Base2;
                auto Normal2 = LuaObject::checkValue<FVector*>(L, 4);
                if (!Normal2) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Normal2Ref = *Normal2;
                auto ParallelCosineThreshold = LuaObject::checkValue<double>(L, 5);
                auto ret = FVector::Coplanar(Base1Ref, Normal1Ref, Base2Ref, Normal2Ref, ParallelCosineThreshold);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector::Coplanar error, argc=%d", argc);
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
            LuaObject::addField(L, "X", get_X, set_X, true);
            LuaObject::addField(L, "Y", get_Y, set_Y, true);
            LuaObject::addField(L, "Z", get_Z, set_Z, true);
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
            LuaObject::addMethod(L, "Equals", Equals, true);
            LuaObject::addMethod(L, "AllComponentsEqual", AllComponentsEqual, true);
            LuaObject::addMethod(L, "SetComponentForAxis", SetComponentForAxis, true);
            LuaObject::addMethod(L, "Set", Set, true);
            LuaObject::addMethod(L, "ComponentMin", ComponentMin, true);
            LuaObject::addMethod(L, "ComponentMax", ComponentMax, true);
            LuaObject::addMethod(L, "GetAbs", GetAbs, true);
            LuaObject::addMethod(L, "IsNearlyZero", IsNearlyZero, true);
            LuaObject::addMethod(L, "IsZero", IsZero, true);
            LuaObject::addMethod(L, "IsUnit", IsUnit, true);
            LuaObject::addMethod(L, "IsNormalized", IsNormalized, true);
            LuaObject::addMethod(L, "Normalize", Normalize, true);
            LuaObject::addMethod(L, "GetUnsafeNormal", GetUnsafeNormal, true);
            LuaObject::addMethod(L, "GetSafeNormal", GetSafeNormal, true);
            LuaObject::addMethod(L, "GetSafeNormal2D", GetSafeNormal2D, true);
            LuaObject::addMethod(L, "ToDirectionAndLength", ToDirectionAndLength, true);
            LuaObject::addMethod(L, "GetSignVector", GetSignVector, true);
            LuaObject::addMethod(L, "Projection", Projection, true);
            LuaObject::addMethod(L, "GetUnsafeNormal2D", GetUnsafeNormal2D, true);
            LuaObject::addMethod(L, "GridSnap", GridSnap, true);
            LuaObject::addMethod(L, "BoundToCube", BoundToCube, true);
            LuaObject::addMethod(L, "BoundToBox", BoundToBox, true);
            LuaObject::addMethod(L, "GetClampedToSize", GetClampedToSize, true);
            LuaObject::addMethod(L, "GetClampedToSize2D", GetClampedToSize2D, true);
            LuaObject::addMethod(L, "GetClampedToMaxSize", GetClampedToMaxSize, true);
            LuaObject::addMethod(L, "GetClampedToMaxSize2D", GetClampedToMaxSize2D, true);
            LuaObject::addMethod(L, "AddBounded", AddBounded, true);
            LuaObject::addMethod(L, "Reciprocal", Reciprocal, true);
            LuaObject::addMethod(L, "IsUniform", IsUniform, true);
            LuaObject::addMethod(L, "MirrorByVector", MirrorByVector, true);
            LuaObject::addMethod(L, "MirrorByPlane", MirrorByPlane, true);
            LuaObject::addMethod(L, "RotateAngleAxis", RotateAngleAxis, true);
            LuaObject::addMethod(L, "RotateAngleAxisRad", RotateAngleAxisRad, true);
            LuaObject::addMethod(L, "ProjectOnTo", ProjectOnTo, true);
            LuaObject::addMethod(L, "ProjectOnToNormal", ProjectOnToNormal, true);
            LuaObject::addMethod(L, "ToOrientationRotator", ToOrientationRotator, true);
            LuaObject::addMethod(L, "ToOrientationQuat", ToOrientationQuat, true);
            LuaObject::addMethod(L, "Rotation", Rotation, true);
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
            LuaObject::addMethod(L, "SlerpVectorToDirection", SlerpVectorToDirection, false);
            LuaObject::addMethod(L, "SlerpNormals", SlerpNormals, false);
            LuaObject::addMethod(L, "CreateOrthonormalBasis", CreateOrthonormalBasis, false);
            LuaObject::addMethod(L, "PointsAreSame", PointsAreSame, false);
            LuaObject::addMethod(L, "PointsAreNear", PointsAreNear, false);
            LuaObject::addMethod(L, "PointPlaneProject", PointPlaneProject, false);
            LuaObject::addMethod(L, "VectorPlaneProject", VectorPlaneProject, false);
            LuaObject::addMethod(L, "Min", Min, false);
            LuaObject::addMethod(L, "Max", Max, false);
            LuaObject::addMethod(L, "Min3", Min3, false);
            LuaObject::addMethod(L, "Max3", Max3, false);
            LuaObject::addMethod(L, "Parallel", Parallel, false);
            LuaObject::addMethod(L, "Coincident", Coincident, false);
            LuaObject::addMethod(L, "Orthogonal", Orthogonal, false);
            LuaObject::addMethod(L, "Coplanar", Coplanar, false);
            LuaObject::addMethod(L, "RadiansToDegrees", RadiansToDegrees, false);
            LuaObject::addMethod(L, "DegreesToRadians", DegreesToRadians, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FVector", __ctor, __gc);
        }

    };

    struct FVector4Wrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto InVector = LuaObject::checkValue<FVector*>(L, 2);
                if (!InVector) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InVectorRef = *InVector;
                auto self = new FVector4(InVectorRef);
                LuaObject::push<FVector4>(L, "FVector4", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InColor = LuaObject::checkValue<FLinearColor*>(L, 2);
                if (!InColor) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InColorRef = *InColor;
                auto InOverrideW = LuaObject::checkValue<double>(L, 3);
                auto self = new FVector4(InColorRef, InOverrideW);
                LuaObject::push<FVector4>(L, "FVector4", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 5) {
                auto InX = LuaObject::checkValue<double>(L, 2);
                auto InY = LuaObject::checkValue<double>(L, 3);
                auto InZ = LuaObject::checkValue<double>(L, 4);
                auto InW = LuaObject::checkValue<double>(L, 5);
                auto self = new FVector4(InX, InY, InZ, InW);
                LuaObject::push<FVector4>(L, "FVector4", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FVector4);
            auto ret = __newFVector4();
            *ret = *self;
            LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FVector4);
            SLUA_GCSTRUCT(FVector4);
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FVector4);
            if (LuaObject::matchType(L, 2, "FVector4")) {
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = (*self + VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FVector4 operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __sub(lua_State* L) {
            CheckSelf(FVector4);
            if (LuaObject::matchType(L, 2, "FVector4")) {
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = (*self - VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FVector4 operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __div(lua_State* L) {
            CheckSelf(FVector4);
            if (LuaObject::matchType(L, 2, "FVector4")) {
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = (*self / VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FVector4 operator__div error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __mul(lua_State* L) {
            CheckSelf(FVector4);
            if (LuaObject::matchType(L, 2, "FVector4")) {
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = (*self * VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FVector4 operator__mul error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FVector4);
            if (LuaObject::matchType(L, 2, "FVector4")) {
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
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

        static int get_X(lua_State* L) {
            CheckSelf(FVector4);
            auto& X = self->X;
            LuaObject::push(L, X);
            return 1;
        }

        static int set_X(lua_State* L) {
            CheckSelf(FVector4);
            auto& X = self->X;
            auto XIn = LuaObject::checkValue<double>(L, 2);
            X = XIn;
            LuaObject::push(L, XIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Y(lua_State* L) {
            CheckSelf(FVector4);
            auto& Y = self->Y;
            LuaObject::push(L, Y);
            return 1;
        }

        static int set_Y(lua_State* L) {
            CheckSelf(FVector4);
            auto& Y = self->Y;
            auto YIn = LuaObject::checkValue<double>(L, 2);
            Y = YIn;
            LuaObject::push(L, YIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Z(lua_State* L) {
            CheckSelf(FVector4);
            auto& Z = self->Z;
            LuaObject::push(L, Z);
            return 1;
        }

        static int set_Z(lua_State* L) {
            CheckSelf(FVector4);
            auto& Z = self->Z;
            auto ZIn = LuaObject::checkValue<double>(L, 2);
            Z = ZIn;
            LuaObject::push(L, ZIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_W(lua_State* L) {
            CheckSelf(FVector4);
            auto& W = self->W;
            LuaObject::push(L, W);
            return 1;
        }

        static int set_W(lua_State* L) {
            CheckSelf(FVector4);
            auto& W = self->W;
            auto WIn = LuaObject::checkValue<double>(L, 2);
            W = WIn;
            LuaObject::push(L, WIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int Equals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector4);
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->Equals(VRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector4::Equals error, argc=%d", argc);
            return 0;
        }

        static int IsUnit3(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector4);
                auto LengthSquaredTolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = self->IsUnit3(LengthSquaredTolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector4::IsUnit3 error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector4);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector4::ToString error, argc=%d", argc);
            return 0;
        }

        static int InitFromString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector4);
                auto InSourceString = LuaObject::checkValue<FString>(L, 2);
                auto ret = self->InitFromString(InSourceString);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector4::InitFromString error, argc=%d", argc);
            return 0;
        }

        static int GetSafeNormal(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector4);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFVector4();
                *ret = self->GetSafeNormal(Tolerance);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::GetSafeNormal error, argc=%d", argc);
            return 0;
        }

        static int GetUnsafeNormal3(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector4);
                auto ret = __newFVector4();
                *ret = self->GetUnsafeNormal3();
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::GetUnsafeNormal3 error, argc=%d", argc);
            return 0;
        }

        static int ToOrientationRotator(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector4);
                auto ret = __newFRotator();
                *ret = self->ToOrientationRotator();
                LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::ToOrientationRotator error, argc=%d", argc);
            return 0;
        }

        static int ToOrientationQuat(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector4);
                auto ret = __newFQuat();
                *ret = self->ToOrientationQuat();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::ToOrientationQuat error, argc=%d", argc);
            return 0;
        }

        static int Rotation(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector4);
                auto ret = __newFRotator();
                *ret = self->Rotation();
                LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::Rotation error, argc=%d", argc);
            return 0;
        }

        static int Set(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 5) {
                CheckSelf(FVector4);
                auto InX = LuaObject::checkValue<double>(L, 2);
                auto InY = LuaObject::checkValue<double>(L, 3);
                auto InZ = LuaObject::checkValue<double>(L, 4);
                auto InW = LuaObject::checkValue<double>(L, 5);
                self->Set(InX, InY, InZ, InW);
                return 0;
            }
            luaL_error(L, "call FVector4::Set error, argc=%d", argc);
            return 0;
        }

        static int ContainsNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector4);
                auto ret = self->ContainsNaN();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector4::ContainsNaN error, argc=%d", argc);
            return 0;
        }

        static int IsNearlyZero3(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector4);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = self->IsNearlyZero3(Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FVector4::IsNearlyZero3 error, argc=%d", argc);
            return 0;
        }

        static int Reflect3(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FVector4);
                auto Normal = LuaObject::checkValue<FVector4*>(L, 2);
                if (!Normal) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NormalRef = *Normal;
                auto ret = __newFVector4();
                *ret = self->Reflect3(NormalRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::Reflect3 error, argc=%d", argc);
            return 0;
        }

        static int FindBestAxisVectors3(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FVector4);
                auto Axis1 = LuaObject::checkValue<FVector4*>(L, 2);
                if (!Axis1) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Axis1Ref = *Axis1;
                auto Axis2 = LuaObject::checkValue<FVector4*>(L, 3);
                if (!Axis2) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Axis2Ref = *Axis2;
                self->FindBestAxisVectors3(Axis1Ref, Axis2Ref);
                LuaObject::push<FVector4>(L, "FVector4", Axis1);
                LuaObject::push<FVector4>(L, "FVector4", Axis2);
                return 2;
            }
            luaL_error(L, "call FVector4::FindBestAxisVectors3 error, argc=%d", argc);
            return 0;
        }

        static int DiagnosticCheckNaN(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FVector4);
                self->DiagnosticCheckNaN();
                return 0;
            }
            luaL_error(L, "call FVector4::DiagnosticCheckNaN error, argc=%d", argc);
            return 0;
        }

        static int Zero(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFVector4();
                *ret = FVector4::Zero();
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::Zero error, argc=%d", argc);
            return 0;
        }

        static int One(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 0) {
                auto ret = __newFVector4();
                *ret = FVector4::One();
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FVector4::One error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FVector4");
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addOperator(L, "__div", __div);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addField(L, "X", get_X, set_X, true);
            LuaObject::addField(L, "Y", get_Y, set_Y, true);
            LuaObject::addField(L, "Z", get_Z, set_Z, true);
            LuaObject::addField(L, "W", get_W, set_W, true);
            LuaObject::addMethod(L, "Equals", Equals, true);
            LuaObject::addMethod(L, "IsUnit3", IsUnit3, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "InitFromString", InitFromString, true);
            LuaObject::addMethod(L, "GetSafeNormal", GetSafeNormal, true);
            LuaObject::addMethod(L, "GetUnsafeNormal3", GetUnsafeNormal3, true);
            LuaObject::addMethod(L, "ToOrientationRotator", ToOrientationRotator, true);
            LuaObject::addMethod(L, "ToOrientationQuat", ToOrientationQuat, true);
            LuaObject::addMethod(L, "Rotation", Rotation, true);
            LuaObject::addMethod(L, "Set", Set, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "IsNearlyZero3", IsNearlyZero3, true);
            LuaObject::addMethod(L, "Reflect3", Reflect3, true);
            LuaObject::addMethod(L, "FindBestAxisVectors3", FindBestAxisVectors3, true);
            LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
            LuaObject::addMethod(L, "Zero", Zero, false);
            LuaObject::addMethod(L, "One", One, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FVector4", __ctor, __gc);
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
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto self = new FPlane(VRef);
                LuaObject::push<FPlane>(L, "FPlane", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InNormal = LuaObject::checkValue<FVector*>(L, 2);
                auto InNormalVal = *InNormal;
                auto InW = LuaObject::checkValue<double>(L, 3);
                auto self = new FPlane(InNormalVal, InW);
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
            if (argc == 5) {
                auto InX = LuaObject::checkValue<double>(L, 2);
                auto InY = LuaObject::checkValue<double>(L, 3);
                auto InZ = LuaObject::checkValue<double>(L, 4);
                auto InW = LuaObject::checkValue<double>(L, 5);
                auto self = new FPlane(InX, InY, InZ, InW);
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

        static int __div(lua_State* L) {
            CheckSelf(FPlane);
            if (lua_isnumber(L, 2)) {
                auto Scale = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFPlane();
                *ret = (*self / Scale);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FPlane operator__div error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __mul(lua_State* L) {
            CheckSelf(FPlane);
            if (lua_isnumber(L, 2)) {
                auto Scale = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFPlane();
                *ret = (*self * Scale);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
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

        static int get_W(lua_State* L) {
            CheckSelf(FPlane);
            auto& W = self->W;
            LuaObject::push(L, W);
            return 1;
        }

        static int set_W(lua_State* L) {
            CheckSelf(FPlane);
            auto& W = self->W;
            auto WIn = LuaObject::checkValue<double>(L, 2);
            W = WIn;
            LuaObject::push(L, WIn);
            SLUA_MARK_NETPROP
            return 1;
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

        static int Normalize(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FPlane);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = self->Normalize(Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FPlane::Normalize error, argc=%d", argc);
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

        static int TransformByUsingAdjointT(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 4) {
                CheckSelf(FPlane);
                auto M = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!M) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MRef = *M;
                auto DetM = LuaObject::checkValue<double>(L, 3);
                auto TA = LuaObject::checkValue<FMatrix*>(L, 4);
                if (!TA) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& TARef = *TA;
                auto ret = __newFPlane();
                *ret = self->TransformByUsingAdjointT(MRef, DetM, TARef);
                LuaObject::push<FPlane>(L, "FPlane", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FPlane::TransformByUsingAdjointT error, argc=%d", argc);
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

        static int Equals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FPlane);
                auto V = LuaObject::checkValue<FPlane*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->Equals(VRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FPlane::Equals error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newTypeWithBase(L, "FPlane", std::initializer_list<const char*>{ "TVector" });
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addOperator(L, "__div", __div);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addField(L, "W", get_W, set_W, true);
            LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
            LuaObject::addMethod(L, "IsValid", IsValid, true);
            LuaObject::addMethod(L, "GetOrigin", GetOrigin, true);
            LuaObject::addMethod(L, "GetNormal", GetNormal, true);
            LuaObject::addMethod(L, "Normalize", Normalize, true);
            LuaObject::addMethod(L, "Flip", Flip, true);
            LuaObject::addMethod(L, "TransformBy", TransformBy, true);
            LuaObject::addMethod(L, "TransformByUsingAdjointT", TransformByUsingAdjointT, true);
            LuaObject::addMethod(L, "TranslateBy", TranslateBy, true);
            LuaObject::addMethod(L, "Equals", Equals, true);
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
            if (argc == 3) {
                auto Axis = LuaObject::checkValue<FVector*>(L, 2);
                auto AxisVal = *Axis;
                auto AngleRad = LuaObject::checkValue<double>(L, 3);
                auto self = new FQuat(AxisVal, AngleRad);
                LuaObject::push<FQuat>(L, "FQuat", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 5) {
                auto InX = LuaObject::checkValue<double>(L, 2);
                auto InY = LuaObject::checkValue<double>(L, 3);
                auto InZ = LuaObject::checkValue<double>(L, 4);
                auto InW = LuaObject::checkValue<double>(L, 5);
                auto self = new FQuat(InX, InY, InZ, InW);
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

        static int get_X(lua_State* L) {
            CheckSelf(FQuat);
            auto& X = self->X;
            LuaObject::push(L, X);
            return 1;
        }

        static int set_X(lua_State* L) {
            CheckSelf(FQuat);
            auto& X = self->X;
            auto XIn = LuaObject::checkValue<double>(L, 2);
            X = XIn;
            LuaObject::push(L, XIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Y(lua_State* L) {
            CheckSelf(FQuat);
            auto& Y = self->Y;
            LuaObject::push(L, Y);
            return 1;
        }

        static int set_Y(lua_State* L) {
            CheckSelf(FQuat);
            auto& Y = self->Y;
            auto YIn = LuaObject::checkValue<double>(L, 2);
            Y = YIn;
            LuaObject::push(L, YIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Z(lua_State* L) {
            CheckSelf(FQuat);
            auto& Z = self->Z;
            LuaObject::push(L, Z);
            return 1;
        }

        static int set_Z(lua_State* L) {
            CheckSelf(FQuat);
            auto& Z = self->Z;
            auto ZIn = LuaObject::checkValue<double>(L, 2);
            Z = ZIn;
            LuaObject::push(L, ZIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_W(lua_State* L) {
            CheckSelf(FQuat);
            auto& W = self->W;
            LuaObject::push(L, W);
            return 1;
        }

        static int set_W(lua_State* L) {
            CheckSelf(FQuat);
            auto& W = self->W;
            auto WIn = LuaObject::checkValue<double>(L, 2);
            W = WIn;
            LuaObject::push(L, WIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Identity(lua_State* L) {
            auto& Identity = FQuat::Identity;
            LuaObject::push<FQuat>(L, "FQuat", &Identity);
            return 1;
        }

        static int Equals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FQuat);
                auto Q = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Q) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& QRef = *Q;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->Equals(QRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FQuat::Equals error, argc=%d", argc);
            return 0;
        }

        static int IsIdentity(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FQuat);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = self->IsIdentity(Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FQuat::IsIdentity error, argc=%d", argc);
            return 0;
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

        static int Normalize(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FQuat);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                self->Normalize(Tolerance);
                return 0;
            }
            luaL_error(L, "call FQuat::Normalize error, argc=%d", argc);
            return 0;
        }

        static int GetNormalized(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FQuat);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFQuat();
                *ret = self->GetNormalized(Tolerance);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::GetNormalized error, argc=%d", argc);
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

        static int Rotator(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FQuat);
                auto ret = __newFRotator();
                *ret = self->Rotator();
                LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Rotator error, argc=%d", argc);
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
            if (argc == 2) {
                CheckSelf(FQuat);
                auto Message = LuaObject::checkValue<const char*>(L, 2);
                auto MessageVal = FString(UTF8_TO_TCHAR(Message));
                self->DiagnosticCheckNaN(*MessageVal);
                return 0;
            }
            luaL_error(L, "call FQuat::DiagnosticCheckNaN error, argc=%d", argc);
            return 0;
        }

        static int MakeFromRotator(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto R = LuaObject::checkValue<FRotator*>(L, 1);
                if (!R) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& RRef = *R;
                auto ret = __newFQuat();
                *ret = FQuat::MakeFromRotator(RRef);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::MakeFromRotator error, argc=%d", argc);
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

        static int FastLerp(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto A = LuaObject::checkValue<FQuat*>(L, 1);
                if (!A) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& ARef = *A;
                auto B = LuaObject::checkValue<FQuat*>(L, 2);
                if (!B) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& BRef = *B;
                auto Alpha = LuaObject::checkValue<double>(L, 3);
                auto ret = __newFQuat();
                *ret = FQuat::FastLerp(ARef, BRef, Alpha);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::FastLerp error, argc=%d", argc);
            return 0;
        }

        static int FastBilerp(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 6) {
                auto P00 = LuaObject::checkValue<FQuat*>(L, 1);
                if (!P00) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& P00Ref = *P00;
                auto P10 = LuaObject::checkValue<FQuat*>(L, 2);
                if (!P10) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& P10Ref = *P10;
                auto P01 = LuaObject::checkValue<FQuat*>(L, 3);
                if (!P01) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& P01Ref = *P01;
                auto P11 = LuaObject::checkValue<FQuat*>(L, 4);
                if (!P11) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& P11Ref = *P11;
                auto FracX = LuaObject::checkValue<double>(L, 5);
                auto FracY = LuaObject::checkValue<double>(L, 6);
                auto ret = __newFQuat();
                *ret = FQuat::FastBilerp(P00Ref, P10Ref, P01Ref, P11Ref, FracX, FracY);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::FastBilerp error, argc=%d", argc);
            return 0;
        }

        static int Slerp_NotNormalized(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto Quat1 = LuaObject::checkValue<FQuat*>(L, 1);
                if (!Quat1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Quat1Ref = *Quat1;
                auto Quat2 = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Quat2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Quat2Ref = *Quat2;
                auto Slerp = LuaObject::checkValue<double>(L, 3);
                auto ret = __newFQuat();
                *ret = FQuat::Slerp_NotNormalized(Quat1Ref, Quat2Ref, Slerp);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Slerp_NotNormalized error, argc=%d", argc);
            return 0;
        }

        static int Slerp(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto Quat1 = LuaObject::checkValue<FQuat*>(L, 1);
                if (!Quat1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Quat1Ref = *Quat1;
                auto Quat2 = LuaObject::checkValue<FQuat*>(L, 2);
                if (!Quat2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& Quat2Ref = *Quat2;
                auto Slerp = LuaObject::checkValue<double>(L, 3);
                auto ret = __newFQuat();
                *ret = FQuat::Slerp(Quat1Ref, Quat2Ref, Slerp);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Slerp error, argc=%d", argc);
            return 0;
        }

        static int SlerpFullPath_NotNormalized(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto quat1 = LuaObject::checkValue<FQuat*>(L, 1);
                if (!quat1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat1Ref = *quat1;
                auto quat2 = LuaObject::checkValue<FQuat*>(L, 2);
                if (!quat2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat2Ref = *quat2;
                auto Alpha = LuaObject::checkValue<double>(L, 3);
                auto ret = __newFQuat();
                *ret = FQuat::SlerpFullPath_NotNormalized(quat1Ref, quat2Ref, Alpha);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::SlerpFullPath_NotNormalized error, argc=%d", argc);
            return 0;
        }

        static int SlerpFullPath(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                auto quat1 = LuaObject::checkValue<FQuat*>(L, 1);
                if (!quat1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat1Ref = *quat1;
                auto quat2 = LuaObject::checkValue<FQuat*>(L, 2);
                if (!quat2) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat2Ref = *quat2;
                auto Alpha = LuaObject::checkValue<double>(L, 3);
                auto ret = __newFQuat();
                *ret = FQuat::SlerpFullPath(quat1Ref, quat2Ref, Alpha);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::SlerpFullPath error, argc=%d", argc);
            return 0;
        }

        static int Squad(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 5) {
                auto quat1 = LuaObject::checkValue<FQuat*>(L, 1);
                if (!quat1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat1Ref = *quat1;
                auto tang1 = LuaObject::checkValue<FQuat*>(L, 2);
                if (!tang1) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& tang1Ref = *tang1;
                auto quat2 = LuaObject::checkValue<FQuat*>(L, 3);
                if (!quat2) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat2Ref = *quat2;
                auto tang2 = LuaObject::checkValue<FQuat*>(L, 4);
                if (!tang2) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& tang2Ref = *tang2;
                auto Alpha = LuaObject::checkValue<double>(L, 5);
                auto ret = __newFQuat();
                *ret = FQuat::Squad(quat1Ref, tang1Ref, quat2Ref, tang2Ref, Alpha);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::Squad error, argc=%d", argc);
            return 0;
        }

        static int SquadFullPath(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 5) {
                auto quat1 = LuaObject::checkValue<FQuat*>(L, 1);
                if (!quat1) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat1Ref = *quat1;
                auto tang1 = LuaObject::checkValue<FQuat*>(L, 2);
                if (!tang1) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& tang1Ref = *tang1;
                auto quat2 = LuaObject::checkValue<FQuat*>(L, 3);
                if (!quat2) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& quat2Ref = *quat2;
                auto tang2 = LuaObject::checkValue<FQuat*>(L, 4);
                if (!tang2) {
                    luaL_error(L, "%s argument 4 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& tang2Ref = *tang2;
                auto Alpha = LuaObject::checkValue<double>(L, 5);
                auto ret = __newFQuat();
                *ret = FQuat::SquadFullPath(quat1Ref, tang1Ref, quat2Ref, tang2Ref, Alpha);
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FQuat::SquadFullPath error, argc=%d", argc);
            return 0;
        }

        static int CalcTangents(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 5) {
                auto PrevP = LuaObject::checkValue<FQuat*>(L, 1);
                if (!PrevP) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PrevPRef = *PrevP;
                auto P = LuaObject::checkValue<FQuat*>(L, 2);
                if (!P) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PRef = *P;
                auto NextP = LuaObject::checkValue<FQuat*>(L, 3);
                if (!NextP) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& NextPRef = *NextP;
                auto Tension = LuaObject::checkValue<double>(L, 4);
                auto OutTan = LuaObject::checkValue<FQuat*>(L, 5);
                if (!OutTan) {
                    luaL_error(L, "%s argument 5 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OutTanRef = *OutTan;
                FQuat::CalcTangents(PrevPRef, PRef, NextPRef, Tension, OutTanRef);
                LuaObject::push<FQuat>(L, "FQuat", OutTan);
                return 1;
            }
            luaL_error(L, "call FQuat::CalcTangents error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FQuat");
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addOperator(L, "__sub", __sub);
            LuaObject::addOperator(L, "__mul", __mul);
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addField(L, "X", get_X, set_X, true);
            LuaObject::addField(L, "Y", get_Y, set_Y, true);
            LuaObject::addField(L, "Z", get_Z, set_Z, true);
            LuaObject::addField(L, "W", get_W, set_W, true);
            LuaObject::addField(L, "Identity", get_Identity, nullptr, false);
            LuaObject::addMethod(L, "Equals", Equals, true);
            LuaObject::addMethod(L, "IsIdentity", IsIdentity, true);
            LuaObject::addMethod(L, "Euler", Euler, true);
            LuaObject::addMethod(L, "Normalize", Normalize, true);
            LuaObject::addMethod(L, "GetNormalized", GetNormalized, true);
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
            LuaObject::addMethod(L, "Rotator", Rotator, true);
            LuaObject::addMethod(L, "ToMatrix", ToMatrix, true);
            LuaObject::addMethod(L, "GetRotationAxis", GetRotationAxis, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "InitFromString", InitFromString, true);
            LuaObject::addMethod(L, "DiagnosticCheckNaN", DiagnosticCheckNaN, true);
            LuaObject::addMethod(L, "MakeFromRotator", MakeFromRotator, false);
            LuaObject::addMethod(L, "MakeFromEuler", MakeFromEuler, false);
            LuaObject::addMethod(L, "MakeFromRotationVector", MakeFromRotationVector, false);
            LuaObject::addMethod(L, "FindBetween", FindBetween, false);
            LuaObject::addMethod(L, "FindBetweenNormals", FindBetweenNormals, false);
            LuaObject::addMethod(L, "FindBetweenVectors", FindBetweenVectors, false);
            LuaObject::addMethod(L, "FastLerp", FastLerp, false);
            LuaObject::addMethod(L, "FastBilerp", FastBilerp, false);
            LuaObject::addMethod(L, "Slerp_NotNormalized", Slerp_NotNormalized, false);
            LuaObject::addMethod(L, "Slerp", Slerp, false);
            LuaObject::addMethod(L, "SlerpFullPath_NotNormalized", SlerpFullPath_NotNormalized, false);
            LuaObject::addMethod(L, "SlerpFullPath", SlerpFullPath, false);
            LuaObject::addMethod(L, "Squad", Squad, false);
            LuaObject::addMethod(L, "SquadFullPath", SquadFullPath, false);
            LuaObject::addMethod(L, "CalcTangents", CalcTangents, false);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FQuat", __ctor, __gc);
        }

    };

    struct FRotatorWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FRotator();
                LuaObject::push<FRotator>(L, "FRotator", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto InF = LuaObject::checkValue<double>(L, 2);
                auto self = new FRotator(InF);
                LuaObject::push<FRotator>(L, "FRotator", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 4) {
                auto InPitch = LuaObject::checkValue<double>(L, 2);
                auto InYaw = LuaObject::checkValue<double>(L, 3);
                auto InRoll = LuaObject::checkValue<double>(L, 4);
                auto self = new FRotator(InPitch, InYaw, InRoll);
                LuaObject::push<FRotator>(L, "FRotator", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FRotator() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FRotator);
            auto ret = __newFRotator();
            *ret = *self;
            LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FRotator);
            SLUA_GCSTRUCT(FRotator);
            return 0;
        }

        static int __add(lua_State* L) {
            CheckSelf(FRotator);
            if (LuaObject::matchType(L, 2, "FRotator")) {
                auto R = LuaObject::checkValue<FRotator*>(L, 2);
                if (!R) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!R) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& RRef = *R;
                auto ret = __newFRotator();
                *ret = (*self - RRef);
                LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FRotator operator__sub error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FRotator);
            if (LuaObject::matchType(L, 2, "FRotator")) {
                auto R = LuaObject::checkValue<FRotator*>(L, 2);
                if (!R) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
            auto PitchIn = LuaObject::checkValue<double>(L, 2);
            Pitch = PitchIn;
            LuaObject::push(L, PitchIn);
            SLUA_MARK_NETPROP
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
            auto YawIn = LuaObject::checkValue<double>(L, 2);
            Yaw = YawIn;
            LuaObject::push(L, YawIn);
            SLUA_MARK_NETPROP
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
            auto RollIn = LuaObject::checkValue<double>(L, 2);
            Roll = RollIn;
            LuaObject::push(L, RollIn);
            SLUA_MARK_NETPROP
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
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
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
                if (!R) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& RRef = *R;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                auto DeltaPitch = LuaObject::checkValue<double>(L, 2);
                auto DeltaYaw = LuaObject::checkValue<double>(L, 3);
                auto DeltaRoll = LuaObject::checkValue<double>(L, 4);
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
                if (!RotGrid) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int Quaternion(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FRotator);
                auto ret = __newFQuat();
                *ret = self->Quaternion();
                LuaObject::push<FQuat>(L, "FQuat", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FRotator::Quaternion error, argc=%d", argc);
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
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

        static int SetComponentForAxis(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FRotator);
                auto Axis = LuaObject::checkValue<int>(L, 2);
                auto AxisVal = (EAxis::Type)Axis;
                auto Component = LuaObject::checkValue<double>(L, 3);
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
                if (!Winding) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& WindingRef = *Winding;
                auto Remainder = LuaObject::checkValue<FRotator*>(L, 3);
                if (!Remainder) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& RemainderRef = *Remainder;
                self->GetWindingAndRemainder(WindingRef, RemainderRef);
                LuaObject::push<FRotator>(L, "FRotator", Winding);
                LuaObject::push<FRotator>(L, "FRotator", Remainder);
                return 2;
            }
            luaL_error(L, "call FRotator::GetWindingAndRemainder error, argc=%d", argc);
            return 0;
        }

        static int GetEquivalentRotator(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FRotator);
                auto ret = __newFRotator();
                *ret = self->GetEquivalentRotator();
                LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FRotator::GetEquivalentRotator error, argc=%d", argc);
            return 0;
        }

        static int SetClosestToMe(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FRotator);
                auto MakeClosest = LuaObject::checkValue<FRotator*>(L, 2);
                if (!MakeClosest) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MakeClosestRef = *MakeClosest;
                self->SetClosestToMe(MakeClosestRef);
                LuaObject::push<FRotator>(L, "FRotator", MakeClosest);
                return 1;
            }
            luaL_error(L, "call FRotator::SetClosestToMe error, argc=%d", argc);
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

        static int CompressAxisToByte(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Angle = LuaObject::checkValue<double>(L, 1);
                auto ret = FRotator::CompressAxisToByte(Angle);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FRotator::CompressAxisToByte error, argc=%d", argc);
            return 0;
        }

        static int CompressAxisToShort(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto Angle = LuaObject::checkValue<double>(L, 1);
                auto ret = FRotator::CompressAxisToShort(Angle);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FRotator::CompressAxisToShort error, argc=%d", argc);
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
            LuaObject::addMethod(L, "Quaternion", Quaternion, true);
            LuaObject::addMethod(L, "Euler", Euler, true);
            LuaObject::addMethod(L, "RotateVector", RotateVector, true);
            LuaObject::addMethod(L, "UnrotateVector", UnrotateVector, true);
            LuaObject::addMethod(L, "Clamp", Clamp, true);
            LuaObject::addMethod(L, "GetNormalized", GetNormalized, true);
            LuaObject::addMethod(L, "GetDenormalized", GetDenormalized, true);
            LuaObject::addMethod(L, "SetComponentForAxis", SetComponentForAxis, true);
            LuaObject::addMethod(L, "Normalize", Normalize, true);
            LuaObject::addMethod(L, "GetWindingAndRemainder", GetWindingAndRemainder, true);
            LuaObject::addMethod(L, "GetEquivalentRotator", GetEquivalentRotator, true);
            LuaObject::addMethod(L, "SetClosestToMe", SetClosestToMe, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "ToCompactString", ToCompactString, true);
            LuaObject::addMethod(L, "InitFromString", InitFromString, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "CompressAxisToByte", CompressAxisToByte, false);
            LuaObject::addMethod(L, "CompressAxisToShort", CompressAxisToShort, false);
            LuaObject::addMethod(L, "MakeFromEuler", MakeFromEuler, false);
            LuaObject::addMethod(L, "clone", clone, true);
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

        static int RemoveScaling(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
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

        static int TransformFVector4(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = self->TransformFVector4(VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::TransformFVector4 error, argc=%d", argc);
            return 0;
        }

        static int TransformFVector4NoScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FTransform);
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = self->TransformFVector4NoScale(VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FTransform::TransformFVector4NoScale error, argc=%d", argc);
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
                auto Scale = LuaObject::checkValue<double>(L, 2);
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

        static int RotationEquals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FTransform);
                auto Other = LuaObject::checkValue<FTransform*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->EqualsNoScale(OtherRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FTransform::EqualsNoScale error, argc=%d", argc);
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

        static int GetSafeScaleReciprocal(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                auto InScale = LuaObject::checkValue<FVector*>(L, 1);
                if (!InScale) {
                    luaL_error(L, "%s argument 1 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& InScaleRef = *InScale;
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
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
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
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
            LuaObject::addMethod(L, "RemoveScaling", RemoveScaling, true);
            LuaObject::addMethod(L, "GetMaximumAxisScale", GetMaximumAxisScale, true);
            LuaObject::addMethod(L, "GetMinimumAxisScale", GetMinimumAxisScale, true);
            LuaObject::addMethod(L, "GetRelativeTransform", GetRelativeTransform, true);
            LuaObject::addMethod(L, "GetRelativeTransformReverse", GetRelativeTransformReverse, true);
            LuaObject::addMethod(L, "SetToRelativeTransform", SetToRelativeTransform, true);
            LuaObject::addMethod(L, "TransformFVector4", TransformFVector4, true);
            LuaObject::addMethod(L, "TransformFVector4NoScale", TransformFVector4NoScale, true);
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
            LuaObject::addMethod(L, "Rotator", Rotator, true);
            LuaObject::addMethod(L, "SetLocation", SetLocation, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "IsValid", IsValid, true);
            LuaObject::addMethod(L, "RotationEquals", RotationEquals, true);
            LuaObject::addMethod(L, "TranslationEquals", TranslationEquals, true);
            LuaObject::addMethod(L, "Scale3DEquals", Scale3DEquals, true);
            LuaObject::addMethod(L, "Equals", Equals, true);
            LuaObject::addMethod(L, "EqualsNoScale", EqualsNoScale, true);
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
            LuaObject::addMethod(L, "NormalizeRotation", NormalizeRotation, true);
            LuaObject::addMethod(L, "IsRotationNormalized", IsRotationNormalized, true);
            LuaObject::addMethod(L, "GetRotation", GetRotation, true);
            LuaObject::addMethod(L, "GetTranslation", GetTranslation, true);
            LuaObject::addMethod(L, "GetScale3D", GetScale3D, true);
            LuaObject::addMethod(L, "CopyRotationPart", CopyRotationPart, true);
            LuaObject::addMethod(L, "CopyTranslationAndScale3D", CopyTranslationAndScale3D, true);
            LuaObject::addMethod(L, "SetFromMatrix", SetFromMatrix, true);
            LuaObject::addMethod(L, "AnyHasNegativeScale", AnyHasNegativeScale, false);
            LuaObject::addMethod(L, "GetSafeScaleReciprocal", GetSafeScaleReciprocal, false);
            LuaObject::addMethod(L, "AreRotationsEqual", AreRotationsEqual, false);
            LuaObject::addMethod(L, "AreTranslationsEqual", AreTranslationsEqual, false);
            LuaObject::addMethod(L, "AreScale3DsEqual", AreScale3DsEqual, false);
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
            if (lua_isnumber(L, 2)) {
                auto Other = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFMatrix();
                *ret = (*self * Other);
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

        static int Equals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FMatrix);
                auto Other = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->Equals(OtherRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FMatrix::Equals error, argc=%d", argc);
            return 0;
        }

        static int TransformFVector4(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto V = LuaObject::checkValue<FVector4*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = self->TransformFVector4(VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::TransformFVector4 error, argc=%d", argc);
            return 0;
        }

        static int TransformPosition(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = self->TransformPosition(VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::TransformPosition error, argc=%d", argc);
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

        static int TransformVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto V = LuaObject::checkValue<FVector*>(L, 2);
                if (!V) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& VRef = *V;
                auto ret = __newFVector4();
                *ret = self->TransformVector(VRef);
                LuaObject::push<FVector4>(L, "FVector4", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::TransformVector error, argc=%d", argc);
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

        static int RemoveScaling(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                self->RemoveScaling(Tolerance);
                return 0;
            }
            luaL_error(L, "call FMatrix::RemoveScaling error, argc=%d", argc);
            return 0;
        }

        static int GetMatrixWithoutScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFMatrix();
                *ret = self->GetMatrixWithoutScale(Tolerance);
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::GetMatrixWithoutScale error, argc=%d", argc);
            return 0;
        }

        static int ExtractScaling(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFVector();
                *ret = self->ExtractScaling(Tolerance);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::ExtractScaling error, argc=%d", argc);
            return 0;
        }

        static int GetScaleVector(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Tolerance = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFVector();
                *ret = self->GetScaleVector(Tolerance);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::GetScaleVector error, argc=%d", argc);
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

        static int ApplyScale(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FMatrix);
                auto Scale = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFMatrix();
                *ret = self->ApplyScale(Scale);
                LuaObject::push<FMatrix>(L, "FMatrix", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::ApplyScale error, argc=%d", argc);
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

        static int Rotator(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FMatrix);
                auto ret = __newFRotator();
                *ret = self->Rotator();
                LuaObject::push<FRotator>(L, "FRotator", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FMatrix::Rotator error, argc=%d", argc);
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
            LuaObject::addMethod(L, "Equals", Equals, true);
            LuaObject::addMethod(L, "TransformFVector4", TransformFVector4, true);
            LuaObject::addMethod(L, "TransformPosition", TransformPosition, true);
            LuaObject::addMethod(L, "InverseTransformPosition", InverseTransformPosition, true);
            LuaObject::addMethod(L, "TransformVector", TransformVector, true);
            LuaObject::addMethod(L, "InverseTransformVector", InverseTransformVector, true);
            LuaObject::addMethod(L, "GetTransposed", GetTransposed, true);
            LuaObject::addMethod(L, "InverseFast", InverseFast, true);
            LuaObject::addMethod(L, "Inverse", Inverse, true);
            LuaObject::addMethod(L, "TransposeAdjoint", TransposeAdjoint, true);
            LuaObject::addMethod(L, "RemoveScaling", RemoveScaling, true);
            LuaObject::addMethod(L, "GetMatrixWithoutScale", GetMatrixWithoutScale, true);
            LuaObject::addMethod(L, "ExtractScaling", ExtractScaling, true);
            LuaObject::addMethod(L, "GetScaleVector", GetScaleVector, true);
            LuaObject::addMethod(L, "RemoveTranslation", RemoveTranslation, true);
            LuaObject::addMethod(L, "ConcatTranslation", ConcatTranslation, true);
            LuaObject::addMethod(L, "ContainsNaN", ContainsNaN, true);
            LuaObject::addMethod(L, "ScaleTranslation", ScaleTranslation, true);
            LuaObject::addMethod(L, "ApplyScale", ApplyScale, true);
            LuaObject::addMethod(L, "GetOrigin", GetOrigin, true);
            LuaObject::addMethod(L, "GetScaledAxis", GetScaledAxis, true);
            LuaObject::addMethod(L, "GetScaledAxes", GetScaledAxes, true);
            LuaObject::addMethod(L, "GetUnitAxis", GetUnitAxis, true);
            LuaObject::addMethod(L, "GetUnitAxes", GetUnitAxes, true);
            LuaObject::addMethod(L, "SetAxis", SetAxis, true);
            LuaObject::addMethod(L, "SetOrigin", SetOrigin, true);
            LuaObject::addMethod(L, "GetColumn", GetColumn, true);
            LuaObject::addMethod(L, "SetColumn", SetColumn, true);
            LuaObject::addMethod(L, "Rotator", Rotator, true);
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

    struct FBox2DWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            luaL_error(L, "call FBox2D() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FBox2D);
            auto ret = __newFBox2D();
            *ret = *self;
            LuaObject::push<FBox2D>(L, "FBox2D", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FBox2D);
            SLUA_GCSTRUCT(FBox2D);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FBox2D");
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FBox2D", __ctor, __gc);
        }

    };

    struct FRayWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FRay();
                LuaObject::push<FRay>(L, "FRay", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto _a0Val = (EForceInit)_a0;
                auto self = new FRay(_a0Val);
                LuaObject::push<FRay>(L, "FRay", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 4) {
                auto Origin = LuaObject::checkValue<FVector*>(L, 2);
                if (!Origin) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OriginRef = *Origin;
                auto Direction = LuaObject::checkValue<FVector*>(L, 3);
                if (!Direction) {
                    luaL_error(L, "%s argument 3 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& DirectionRef = *Direction;
                auto bDirectionIsNormalized = LuaObject::checkValue<bool>(L, 4);
                auto self = new FRay(OriginRef, DirectionRef, bDirectionIsNormalized);
                LuaObject::push<FRay>(L, "FRay", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FRay() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FRay);
            auto ret = __newFRay();
            *ret = *self;
            LuaObject::push<FRay>(L, "FRay", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FRay);
            SLUA_GCSTRUCT(FRay);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FRay);
            if (LuaObject::matchType(L, 2, "FRay")) {
                auto Other = LuaObject::checkValue<FRay*>(L, 2);
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

        static int get_Origin(lua_State* L) {
            CheckSelf(FRay);
            auto& Origin = self->Origin;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FVector>(L, udptr->parent ? udptr->parent : self, "FVector", &Origin, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_Origin(lua_State* L) {
            CheckSelf(FRay);
            auto& Origin = self->Origin;
            auto OriginIn = LuaObject::checkValue<FVector*>(L, 2);
            Origin = *OriginIn;
            LuaObject::push<FVector>(L, "FVector", OriginIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_Direction(lua_State* L) {
            CheckSelf(FRay);
            auto& Direction = self->Direction;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FVector>(L, udptr->parent ? udptr->parent : self, "FVector", &Direction, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_Direction(lua_State* L) {
            CheckSelf(FRay);
            auto& Direction = self->Direction;
            auto DirectionIn = LuaObject::checkValue<FVector*>(L, 2);
            Direction = *DirectionIn;
            LuaObject::push<FVector>(L, "FVector", DirectionIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int Init(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FRay);
                self->Init();
                return 0;
            }
            luaL_error(L, "call FRay::Init error, argc=%d", argc);
            return 0;
        }

        static int PointAt(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FRay);
                auto RayParameter = LuaObject::checkValue<double>(L, 2);
                auto ret = __newFVector();
                *ret = self->PointAt(RayParameter);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FRay::PointAt error, argc=%d", argc);
            return 0;
        }

        static int ClosestPoint(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FRay);
                auto Point = LuaObject::checkValue<FVector*>(L, 2);
                if (!Point) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& PointRef = *Point;
                auto ret = __newFVector();
                *ret = self->ClosestPoint(PointRef);
                LuaObject::push<FVector>(L, "FVector", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FRay::ClosestPoint error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FRay);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FRay::ToString error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FRay");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addField(L, "Origin", get_Origin, set_Origin, true);
            LuaObject::addField(L, "Direction", get_Direction, set_Direction, true);
            LuaObject::addMethod(L, "Init", Init, true);
            LuaObject::addMethod(L, "PointAt", PointAt, true);
            LuaObject::addMethod(L, "ClosestPoint", ClosestPoint, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FRay", __ctor, __gc);
        }

    };

    struct FSphereWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FSphere();
                LuaObject::push<FSphere>(L, "FSphere", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto _a0 = LuaObject::checkValue<int>(L, 2);
                auto self = new FSphere(_a0);
                LuaObject::push<FSphere>(L, "FSphere", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 3) {
                auto InV = LuaObject::checkValue<FVector*>(L, 2);
                auto InVVal = *InV;
                auto InW = LuaObject::checkValue<double>(L, 3);
                auto self = new FSphere(InVVal, InW);
                LuaObject::push<FSphere>(L, "FSphere", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSphere() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FSphere);
            auto ret = __newFSphere();
            *ret = *self;
            LuaObject::push<FSphere>(L, "FSphere", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FSphere);
            SLUA_GCSTRUCT(FSphere);
            return 0;
        }

        static int __eq(lua_State* L) {
            CheckSelf(FSphere);
            if (LuaObject::matchType(L, 2, "FSphere")) {
                auto Other = LuaObject::checkValue<FSphere*>(L, 2);
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
            CheckSelf(FSphere);
            if (LuaObject::matchType(L, 2, "FSphere")) {
                auto Other = LuaObject::checkValue<FSphere*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto ret = __newFSphere();
                *ret = (*self + OtherRef);
                LuaObject::push<FSphere>(L, "FSphere", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "FSphere operator__add error, arg=%d", lua_typename(L, 2));
            return 0;
        }

        static int get_Center(lua_State* L) {
            CheckSelf(FSphere);
            auto& Center = self->Center;
            SLUA_GET_NETINFO
            LuaObject::pushAndLink<FVector>(L, udptr->parent ? udptr->parent : self, "FVector", &Center, (void*)proxy, luaReplicatedIndex);
            return 1;
        }

        static int set_Center(lua_State* L) {
            CheckSelf(FSphere);
            auto& Center = self->Center;
            auto CenterIn = LuaObject::checkValue<FVector*>(L, 2);
            Center = *CenterIn;
            LuaObject::push<FVector>(L, "FVector", CenterIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int get_W(lua_State* L) {
            CheckSelf(FSphere);
            auto& W = self->W;
            LuaObject::push(L, W);
            return 1;
        }

        static int set_W(lua_State* L) {
            CheckSelf(FSphere);
            auto& W = self->W;
            auto WIn = LuaObject::checkValue<double>(L, 2);
            W = WIn;
            LuaObject::push(L, WIn);
            SLUA_MARK_NETPROP
            return 1;
        }

        static int Equals(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FSphere);
                auto Sphere = LuaObject::checkValue<FSphere*>(L, 2);
                if (!Sphere) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& SphereRef = *Sphere;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->Equals(SphereRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSphere::Equals error, argc=%d", argc);
            return 0;
        }

        static int IsInside(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FSphere);
                auto Other = LuaObject::checkValue<FSphere*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->IsInside(OtherRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSphere::IsInside error, argc=%d", argc);
            return 0;
        }

        static int Intersects(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 3) {
                CheckSelf(FSphere);
                auto Other = LuaObject::checkValue<FSphere*>(L, 2);
                if (!Other) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& OtherRef = *Other;
                auto Tolerance = LuaObject::checkValue<double>(L, 3);
                auto ret = self->Intersects(OtherRef, Tolerance);
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSphere::Intersects error, argc=%d", argc);
            return 0;
        }

        static int TransformBy(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 2) {
                CheckSelf(FSphere);
                auto M = LuaObject::checkValue<FMatrix*>(L, 2);
                if (!M) {
                    luaL_error(L, "%s argument 2 is nullptr", __FUNCTION__);
                    return 0;
                }
                auto& MRef = *M;
                auto ret = __newFSphere();
                *ret = self->TransformBy(MRef);
                LuaObject::push<FSphere>(L, "FSphere", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSphere::TransformBy error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FSphere");
            LuaObject::addOperator(L, "__eq", __eq);
            LuaObject::addOperator(L, "__add", __add);
            LuaObject::addField(L, "Center", get_Center, set_Center, true);
            LuaObject::addField(L, "W", get_W, set_W, true);
            LuaObject::addMethod(L, "Equals", Equals, true);
            LuaObject::addMethod(L, "IsInside", IsInside, true);
            LuaObject::addMethod(L, "Intersects", Intersects, true);
            LuaObject::addMethod(L, "TransformBy", TransformBy, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FSphere", __ctor, __gc);
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

        FIntVectorStruct = StaticGetBaseStructureInternal(TEXT("IntVector"));
        if (FIntVectorStruct) {
            _pushStructMap.Add(FIntVectorStruct, __pushFIntVector);
            _checkStructMap.Add(FIntVectorStruct, __checkFIntVector);
            FIntVectorWrapper::bind(L);
        }

        FIntVector4Struct = StaticGetBaseStructureInternal(TEXT("IntVector4"));
        if (FIntVector4Struct) {
            _pushStructMap.Add(FIntVector4Struct, __pushFIntVector4);
            _checkStructMap.Add(FIntVector4Struct, __checkFIntVector4);
            FIntVector4Wrapper::bind(L);
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

        FFallbackStructStruct = StaticGetBaseStructureInternal(TEXT("FallbackStruct"));
        if (FFallbackStructStruct) {
            _pushStructMap.Add(FFallbackStructStruct, __pushFFallbackStruct);
            _checkStructMap.Add(FFallbackStructStruct, __checkFFallbackStruct);
            FFallbackStructWrapper::bind(L);
        }

        FInterpCurvePointFloatStruct = StaticGetBaseStructureInternal(TEXT("InterpCurvePointFloat"));
        if (FInterpCurvePointFloatStruct) {
            _pushStructMap.Add(FInterpCurvePointFloatStruct, __pushFInterpCurvePointFloat);
            _checkStructMap.Add(FInterpCurvePointFloatStruct, __checkFInterpCurvePointFloat);
            FInterpCurvePointFloatWrapper::bind(L);
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

        FFrameTimeStruct = StaticGetBaseStructureInternal(TEXT("FrameTime"));
        if (FFrameTimeStruct) {
            _pushStructMap.Add(FFrameTimeStruct, __pushFFrameTime);
            _checkStructMap.Add(FFrameTimeStruct, __checkFFrameTime);
            FFrameTimeWrapper::bind(L);
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

        FTopLevelAssetPathStruct = StaticGetBaseStructureInternal(TEXT("TopLevelAssetPath"));
        if (FTopLevelAssetPathStruct) {
            _pushStructMap.Add(FTopLevelAssetPathStruct, __pushFTopLevelAssetPath);
            _checkStructMap.Add(FTopLevelAssetPathStruct, __checkFTopLevelAssetPath);
            FTopLevelAssetPathWrapper::bind(L);
        }

        FVector2DStruct = StaticGetBaseStructureInternal(TEXT("Vector2D"));
        if (FVector2DStruct) {
            _pushStructMap.Add(FVector2DStruct, __pushFVector2D);
            _checkStructMap.Add(FVector2DStruct, __checkFVector2D);
            FVector2DWrapper::bind(L);
        }

        FVectorStruct = StaticGetBaseStructureInternal(TEXT("Vector"));
        if (FVectorStruct) {
            _pushStructMap.Add(FVectorStruct, __pushFVector);
            _checkStructMap.Add(FVectorStruct, __checkFVector);
            FVectorWrapper::bind(L);
        }

        FVector4Struct = StaticGetBaseStructureInternal(TEXT("Vector4"));
        if (FVector4Struct) {
            _pushStructMap.Add(FVector4Struct, __pushFVector4);
            _checkStructMap.Add(FVector4Struct, __checkFVector4);
            FVector4Wrapper::bind(L);
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

        FRotatorStruct = StaticGetBaseStructureInternal(TEXT("Rotator"));
        if (FRotatorStruct) {
            _pushStructMap.Add(FRotatorStruct, __pushFRotator);
            _checkStructMap.Add(FRotatorStruct, __checkFRotator);
            FRotatorWrapper::bind(L);
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

        FBox2DStruct = StaticGetBaseStructureInternal(TEXT("Box2D"));
        if (FBox2DStruct) {
            _pushStructMap.Add(FBox2DStruct, __pushFBox2D);
            _checkStructMap.Add(FBox2DStruct, __checkFBox2D);
            FBox2DWrapper::bind(L);
        }

        FRayStruct = StaticGetBaseStructureInternal(TEXT("Ray"));
        if (FRayStruct) {
            _pushStructMap.Add(FRayStruct, __pushFRay);
            _checkStructMap.Add(FRayStruct, __checkFRay);
            FRayWrapper::bind(L);
        }

        FSphereStruct = StaticGetBaseStructureInternal(TEXT("Sphere"));
        if (FSphereStruct) {
            _pushStructMap.Add(FSphereStruct, __pushFSphere);
            _checkStructMap.Add(FSphereStruct, __checkFSphere);
            FSphereWrapper::bind(L);
        }
    }
