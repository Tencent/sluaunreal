// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

{
char s[] = 

"UEnums = {}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EForceInit = {"
    "ForceInit = 0,"
    "ForceInitToZero = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENoInit = {"
    "NoInit = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConvertibleLaptopMode = {"
    "NotSupported = 0,"
    "Laptop = 1,"
    "Tablet = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDeviceScreenOrientation = {"
    "Unknown = 0,"
    "Portrait = 1,"
    "PortraitUpsideDown = 2,"
    "LandscapeLeft = 3,"
    "LandscapeRight = 4,"
    "FaceUp = 5,"
    "FaceDown = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMemoryAllocatorToUse = {"
    "Ansi = 0,"
    "Stomp = 1,"
    "TBB = 2,"
    "Jemalloc = 3,"
    "Binned = 4,"
    "Binned2 = 5,"
    "Platform = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESharedMemoryAccess = {"
    "Read = 2,"
    "Write = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ErrorCodes = {"
    "SUCCEEDED = 0,"
    "ERROR_UNKNOWNVERSION = 1,"
    "ERROR_GETPRODUCTINFO_FAILED = 2,"
    "ERROR_GETVERSIONEX_FAILED = 4,"
    "ERROR_GETWINDOWSGT62VERSIONS_FAILED = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECompressionFlags = {"
    "COMPRESS_None = 0,"
    "COMPRESS_ZLIB = 1,"
    "COMPRESS_GZIP = 2,"
    "COMPRESS_BiasMemory = 16,"
    "COMPRESS_BiasSpeed = 32,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVersionComponent = {"
    "Major = 0,"
    "Minor = 1,"
    "Patch = 2,"
    "Changelist = 3,"
    "Branch = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVersionComparison = {"
    "Neither = 0,"
    "First = 1,"
    "Second = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EName = {"
    "NAME_None = 0,"
    "NAME_ByteProperty = 1,"
    "NAME_IntProperty = 2,"
    "NAME_BoolProperty = 3,"
    "NAME_FloatProperty = 4,"
    "NAME_ObjectProperty = 5,"
    "NAME_NameProperty = 6,"
    "NAME_DelegateProperty = 7,"
    "NAME_DoubleProperty = 8,"
    "NAME_ArrayProperty = 9,"
    "NAME_StructProperty = 10,"
    "NAME_VectorProperty = 11,"
    "NAME_RotatorProperty = 12,"
    "NAME_StrProperty = 13,"
    "NAME_TextProperty = 14,"
    "NAME_InterfaceProperty = 15,"
    "NAME_MulticastDelegateProperty = 16,"
    "NAME_LazyObjectProperty = 18,"
    "NAME_SoftObjectProperty = 19,"
    "NAME_UInt64Property = 20,"
    "NAME_UInt32Property = 21,"
    "NAME_UInt16Property = 22,"
    "NAME_Int64Property = 23,"
    "NAME_Int16Property = 25,"
    "NAME_Int8Property = 26,"
    "NAME_MapProperty = 28,"
    "NAME_SetProperty = 29,"
    "NAME_Core = 30,"
    "NAME_Engine = 31,"
    "NAME_Editor = 32,"
    "NAME_CoreUObject = 33,"
    "NAME_EnumProperty = 34,"
    "NAME_Cylinder = 50,"
    "NAME_BoxSphereBounds = 51,"
    "NAME_Sphere = 52,"
    "NAME_Box = 53,"
    "NAME_Vector2D = 54,"
    "NAME_IntRect = 55,"
    "NAME_IntPoint = 56,"
    "NAME_Vector4 = 57,"
    "NAME_Name = 58,"
    "NAME_Vector = 59,"
    "NAME_Rotator = 60,"
    "NAME_SHVector = 61,"
    "NAME_Color = 62,"
    "NAME_Plane = 63,"
    "NAME_Matrix = 64,"
    "NAME_LinearColor = 65,"
    "NAME_AdvanceFrame = 66,"
    "NAME_Pointer = 67,"
    "NAME_Double = 68,"
    "NAME_Quat = 69,"
    "NAME_Self = 70,"
    "NAME_Transform = 71,"
    "NAME_Object = 100,"
    "NAME_Camera = 101,"
    "NAME_Actor = 102,"
    "NAME_ObjectRedirector = 103,"
    "NAME_ObjectArchetype = 104,"
    "NAME_Class = 105,"
    "NAME_ScriptStruct = 106,"
    "NAME_Function = 107,"
    "NAME_State = 200,"
    "NAME_TRUE = 201,"
    "NAME_FALSE = 202,"
    "NAME_Enum = 203,"
    "NAME_Default = 204,"
    "NAME_Skip = 205,"
    "NAME_Input = 206,"
    "NAME_Package = 207,"
    "NAME_Groups = 208,"
    "NAME_Interface = 209,"
    "NAME_Components = 210,"
    "NAME_Global = 211,"
    "NAME_Super = 212,"
    "NAME_Outer = 213,"
    "NAME_Map = 214,"
    "NAME_Role = 215,"
    "NAME_RemoteRole = 216,"
    "NAME_PersistentLevel = 217,"
    "NAME_TheWorld = 218,"
    "NAME_PackageMetaData = 219,"
    "NAME_InitialState = 220,"
    "NAME_Game = 221,"
    "NAME_SelectionColor = 222,"
    "NAME_UI = 223,"
    "NAME_ExecuteUbergraph = 224,"
    "NAME_DeviceID = 225,"
    "NAME_RootStat = 226,"
    "NAME_MoveActor = 227,"
    "NAME_All = 230,"
    "NAME_MeshEmitterVertexColor = 231,"
    "NAME_TextureOffsetParameter = 232,"
    "NAME_TextureScaleParameter = 233,"
    "NAME_ImpactVel = 234,"
    "NAME_SlideVel = 235,"
    "NAME_TextureOffset1Parameter = 236,"
    "NAME_MeshEmitterDynamicParameter = 237,"
    "NAME_ExpressionInput = 238,"
    "NAME_Untitled = 239,"
    "NAME_Timer = 240,"
    "NAME_Team = 241,"
    "NAME_Low = 242,"
    "NAME_High = 243,"
    "NAME_NetworkGUID = 244,"
    "NAME_GameThread = 245,"
    "NAME_RenderThread = 246,"
    "NAME_OtherChildren = 247,"
    "NAME_Location = 248,"
    "NAME_Rotation = 249,"
    "NAME_BSP = 250,"
    "NAME_EditorSettings = 251,"
    "NAME_AudioThread = 252,"
    "NAME_ID = 253,"
    "NAME_DGram = 280,"
    "NAME_Stream = 281,"
    "NAME_GameNetDriver = 282,"
    "NAME_PendingNetDriver = 283,"
    "NAME_BeaconNetDriver = 284,"
    "NAME_FlushNetDormancy = 285,"
    "NAME_DemoNetDriver = 286,"
    "NAME_GameSession = 287,"
    "NAME_PartySession = 288,"
    "NAME_GamePort = 289,"
    "NAME_BeaconPort = 290,"
    "NAME_Linear = 300,"
    "NAME_Point = 301,"
    "NAME_Aniso = 302,"
    "NAME_LightMapResolution = 303,"
    "NAME_UnGrouped = 311,"
    "NAME_VoiceChat = 312,"
    "NAME_Playing = 320,"
    "NAME_Spectating = 322,"
    "NAME_Inactive = 325,"
    "NAME_PerfWarning = 350,"
    "NAME_Info = 351,"
    "NAME_Init = 352,"
    "NAME_Exit = 353,"
    "NAME_Cmd = 354,"
    "NAME_Warning = 355,"
    "NAME_Error = 356,"
    "NAME_FontCharacter = 400,"
    "NAME_InitChild2StartBone = 401,"
    "NAME_SoundCueLocalized = 402,"
    "NAME_SoundCue = 403,"
    "NAME_RawDistributionFloat = 404,"
    "NAME_RawDistributionVector = 405,"
    "NAME_InterpCurveFloat = 406,"
    "NAME_InterpCurveVector2D = 407,"
    "NAME_InterpCurveVector = 408,"
    "NAME_InterpCurveTwoVectors = 409,"
    "NAME_InterpCurveQuat = 410,"
    "NAME_AI = 450,"
    "NAME_NavMesh = 451,"
    "NAME_PerformanceCapture = 500,"
    "NAME_EditorLayout = 600,"
    "NAME_EditorKeyBindings = 601,"
    "NAME_MaxHardcodedNameIndex = 602,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENameCase = {"
    "CaseSensitive = 0,"
    "IgnoreCase = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELinkerNameTableConstructor = {"
    "ENAME_LinkerConstructor = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFindName = {"
    "FNAME_Find = 0,"
    "FNAME_Add = 1,"
    "FNAME_Replace_Not_Safe_For_Threading = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGammaSpace = {"
    "Linear = 0,"
    "Pow22 = 1,"
    "sRGB = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESPMode = {"
    "NotThreadSafe = 0,"
    "Fast = 0,"
    "ThreadSafe = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGenerateNewHandleType = {"
    "GenerateNewHandle = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStringTableLoadingPolicy = {"
    "Find = 0,"
    "FindOrLoad = 1,"
    "FindOrFullyLoad = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextPluralType = {"
    "Cardinal = 0,"
    "Ordinal = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextPluralForm = {"
    "Zero = 0,"
    "One = 1,"
    "Two = 2,"
    "Few = 3,"
    "Many = 4,"
    "Other = 5,"
    "Count = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextGender = {"
    "Masculine = 0,"
    "Feminine = 1,"
    "Neuter = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERoundingMode = {"
    "HalfToEven = 0,"
    "HalfFromZero = 1,"
    "HalfToZero = 2,"
    "FromZero = 3,"
    "ToZero = 4,"
    "ToNegativeInfinity = 5,"
    "ToPositiveInfinity = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EExpressionType = {"
    "Invalid = 0,"
    "Simple = 1,"
    "Complex = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInitToEmptyString = {"
    "Value = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextDirection = {"
    "LeftToRight = 0,"
    "RightToLeft = 1,"
    "Mixed = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUnrealEngineObjectUE4Version = {"
    "VER_UE4_OLDEST_LOADABLE_PACKAGE = 214,"
    "VER_UE4_BLUEPRINT_VARS_NOT_READ_ONLY = 215,"
    "VER_UE4_STATIC_MESH_STORE_NAV_COLLISION = 216,"
    "VER_UE4_ATMOSPHERIC_FOG_DECAY_NAME_CHANGE = 217,"
    "VER_UE4_SCENECOMP_TRANSLATION_TO_LOCATION = 218,"
    "VER_UE4_MATERIAL_ATTRIBUTES_REORDERING = 219,"
    "VER_UE4_COLLISION_PROFILE_SETTING = 220,"
    "VER_UE4_BLUEPRINT_SKEL_TEMPORARY_TRANSIENT = 221,"
    "VER_UE4_BLUEPRINT_SKEL_SERIALIZED_AGAIN = 222,"
    "VER_UE4_BLUEPRINT_SETS_REPLICATION = 223,"
    "VER_UE4_WORLD_LEVEL_INFO = 224,"
    "VER_UE4_AFTER_CAPSULE_HALF_HEIGHT_CHANGE = 225,"
    "VER_UE4_ADDED_NAMESPACE_AND_KEY_DATA_TO_FTEXT = 226,"
    "VER_UE4_ATTENUATION_SHAPES = 227,"
    "VER_UE4_LIGHTCOMPONENT_USE_IES_TEXTURE_MULTIPLIER_ON_NON_IES_BRIGHTNESS = 228,"
    "VER_UE4_REMOVE_INPUT_COMPONENTS_FROM_BLUEPRINTS = 229,"
    "VER_UE4_VARK2NODE_USE_MEMBERREFSTRUCT = 230,"
    "VER_UE4_REFACTOR_MATERIAL_EXPRESSION_SCENECOLOR_AND_SCENEDEPTH_INPUTS = 231,"
    "VER_UE4_SPLINE_MESH_ORIENTATION = 232,"
    "VER_UE4_REVERB_EFFECT_ASSET_TYPE = 233,"
    "VER_UE4_MAX_TEXCOORD_INCREASED = 234,"
    "VER_UE4_SPEEDTREE_STATICMESH = 235,"
    "VER_UE4_LANDSCAPE_COMPONENT_LAZY_REFERENCES = 236,"
    "VER_UE4_SWITCH_CALL_NODE_TO_USE_MEMBER_REFERENCE = 237,"
    "VER_UE4_ADDED_SKELETON_ARCHIVER_REMOVAL = 238,"
    "VER_UE4_ADDED_SKELETON_ARCHIVER_REMOVAL_SECOND_TIME = 239,"
    "VER_UE4_BLUEPRINT_SKEL_CLASS_TRANSIENT_AGAIN = 240,"
    "VER_UE4_ADD_COOKED_TO_UCLASS = 241,"
    "VER_UE4_DEPRECATED_STATIC_MESH_THUMBNAIL_PROPERTIES_REMOVED = 242,"
    "VER_UE4_COLLECTIONS_IN_SHADERMAPID = 243,"
    "VER_UE4_REFACTOR_MOVEMENT_COMPONENT_HIERARCHY = 244,"
    "VER_UE4_FIX_TERRAIN_LAYER_SWITCH_ORDER = 245,"
    "VER_UE4_ALL_PROPS_TO_CONSTRAINTINSTANCE = 246,"
    "VER_UE4_LOW_QUALITY_DIRECTIONAL_LIGHTMAPS = 247,"
    "VER_UE4_ADDED_NOISE_EMITTER_COMPONENT = 248,"
    "VER_UE4_ADD_TEXT_COMPONENT_VERTICAL_ALIGNMENT = 249,"
    "VER_UE4_ADDED_FBX_ASSET_IMPORT_DATA = 250,"
    "VER_UE4_REMOVE_LEVELBODYSETUP = 251,"
    "VER_UE4_REFACTOR_CHARACTER_CROUCH = 252,"
    "VER_UE4_SMALLER_DEBUG_MATERIALSHADER_UNIFORM_EXPRESSIONS = 253,"
    "VER_UE4_APEX_CLOTH = 254,"
    "VER_UE4_SAVE_COLLISIONRESPONSE_PER_CHANNEL = 255,"
    "VER_UE4_ADDED_LANDSCAPE_SPLINE_EDITOR_MESH = 256,"
    "VER_UE4_CHANGED_MATERIAL_REFACTION_TYPE = 257,"
    "VER_UE4_REFACTOR_PROJECTILE_MOVEMENT = 258,"
    "VER_UE4_REMOVE_PHYSICALMATERIALPROPERTY = 259,"
    "VER_UE4_PURGED_FMATERIAL_COMPILE_OUTPUTS = 260,"
    "VER_UE4_ADD_COOKED_TO_LANDSCAPE = 261,"
    "VER_UE4_CONSUME_INPUT_PER_BIND = 262,"
    "VER_UE4_SOUND_CLASS_GRAPH_EDITOR = 263,"
    "VER_UE4_FIXUP_TERRAIN_LAYER_NODES = 264,"
    "VER_UE4_RETROFIT_CLAMP_EXPRESSIONS_SWAP = 265,"
    "VER_UE4_REMOVE_LIGHT_MOBILITY_CLASSES = 266,"
    "VER_UE4_REFACTOR_PHYSICS_BLENDING = 267,"
    "VER_UE4_WORLD_LEVEL_INFO_UPDATED = 268,"
    "VER_UE4_STATIC_SKELETAL_MESH_SERIALIZATION_FIX = 269,"
    "VER_UE4_REMOVE_STATICMESH_MOBILITY_CLASSES = 270,"
    "VER_UE4_REFACTOR_PHYSICS_TRANSFORMS = 271,"
    "VER_UE4_REMOVE_ZERO_TRIANGLE_SECTIONS = 272,"
    "VER_UE4_CHARACTER_MOVEMENT_DECELERATION = 273,"
    "VER_UE4_CAMERA_ACTOR_USING_CAMERA_COMPONENT = 274,"
    "VER_UE4_CHARACTER_MOVEMENT_DEPRECATE_PITCH_ROLL = 275,"
    "VER_UE4_REBUILD_TEXTURE_STREAMING_DATA_ON_LOAD = 276,"
    "VER_UE4_SUPPORT_32BIT_STATIC_MESH_INDICES = 277,"
    "VER_UE4_ADDED_CHUNKID_TO_ASSETDATA_AND_UPACKAGE = 278,"
    "VER_UE4_CHARACTER_DEFAULT_MOVEMENT_BINDINGS = 279,"
    "VER_UE4_APEX_CLOTH_LOD = 280,"
    "VER_UE4_ATMOSPHERIC_FOG_CACHE_DATA = 281,"
    "VAR_UE4_ARRAY_PROPERTY_INNER_TAGS = 282,"
    "VER_UE4_KEEP_SKEL_MESH_INDEX_DATA = 283,"
    "VER_UE4_BODYSETUP_COLLISION_CONVERSION = 284,"
    "VER_UE4_REFLECTION_CAPTURE_COOKING = 285,"
    "VER_UE4_REMOVE_DYNAMIC_VOLUME_CLASSES = 286,"
    "VER_UE4_STORE_HASCOOKEDDATA_FOR_BODYSETUP = 287,"
    "VER_UE4_REFRACTION_BIAS_TO_REFRACTION_DEPTH_BIAS = 288,"
    "VER_UE4_REMOVE_SKELETALPHYSICSACTOR = 289,"
    "VER_UE4_PC_ROTATION_INPUT_REFACTOR = 290,"
    "VER_UE4_LANDSCAPE_PLATFORMDATA_COOKING = 291,"
    "VER_UE4_CREATEEXPORTS_CLASS_LINKING_FOR_BLUEPRINTS = 292,"
    "VER_UE4_REMOVE_NATIVE_COMPONENTS_FROM_BLUEPRINT_SCS = 293,"
    "VER_UE4_REMOVE_SINGLENODEINSTANCE = 294,"
    "VER_UE4_CHARACTER_BRAKING_REFACTOR = 295,"
    "VER_UE4_VOLUME_SAMPLE_LOW_QUALITY_SUPPORT = 296,"
    "VER_UE4_SPLIT_TOUCH_AND_CLICK_ENABLES = 297,"
    "VER_UE4_HEALTH_DEATH_REFACTOR = 298,"
    "VER_UE4_SOUND_NODE_ENVELOPER_CURVE_CHANGE = 299,"
    "VER_UE4_POINT_LIGHT_SOURCE_RADIUS = 300,"
    "VER_UE4_SCENE_CAPTURE_CAMERA_CHANGE = 301,"
    "VER_UE4_MOVE_SKELETALMESH_SHADOWCASTING = 302,"
    "VER_UE4_CHANGE_SETARRAY_BYTECODE = 303,"
    "VER_UE4_MATERIAL_INSTANCE_BASE_PROPERTY_OVERRIDES = 304,"
    "VER_UE4_COMBINED_LIGHTMAP_TEXTURES = 305,"
    "VER_UE4_BUMPED_MATERIAL_EXPORT_GUIDS = 306,"
    "VER_UE4_BLUEPRINT_INPUT_BINDING_OVERRIDES = 307,"
    "VER_UE4_FIXUP_BODYSETUP_INVALID_CONVEX_TRANSFORM = 308,"
    "VER_UE4_FIXUP_STIFFNESS_AND_DAMPING_SCALE = 309,"
    "VER_UE4_REFERENCE_SKELETON_REFACTOR = 310,"
    "VER_UE4_K2NODE_REFERENCEGUIDS = 311,"
    "VER_UE4_FIXUP_ROOTBONE_PARENT = 312,"
    "VER_UE4_TEXT_RENDER_COMPONENTS_WORLD_SPACE_SIZING = 313,"
    "VER_UE4_MATERIAL_INSTANCE_BASE_PROPERTY_OVERRIDES_PHASE_2 = 314,"
    "VER_UE4_CLASS_NOTPLACEABLE_ADDED = 315,"
    "VER_UE4_WORLD_LEVEL_INFO_LOD_LIST = 316,"
    "VER_UE4_CHARACTER_MOVEMENT_VARIABLE_RENAMING_1 = 317,"
    "VER_UE4_FSLATESOUND_CONVERSION = 318,"
    "VER_UE4_WORLD_LEVEL_INFO_ZORDER = 319,"
    "VER_UE4_PACKAGE_REQUIRES_LOCALIZATION_GATHER_FLAGGING = 320,"
    "VER_UE4_BP_ACTOR_VARIABLE_DEFAULT_PREVENTING = 321,"
    "VER_UE4_TEST_ANIMCOMP_CHANGE = 322,"
    "VER_UE4_EDITORONLY_BLUEPRINTS = 323,"
    "VER_UE4_EDGRAPHPINTYPE_SERIALIZATION = 324,"
    "VER_UE4_NO_MIRROR_BRUSH_MODEL_COLLISION = 325,"
    "VER_UE4_CHANGED_CHUNKID_TO_BE_AN_ARRAY_OF_CHUNKIDS = 326,"
    "VER_UE4_WORLD_NAMED_AFTER_PACKAGE = 327,"
    "VER_UE4_SKY_LIGHT_COMPONENT = 328,"
    "VER_UE4_WORLD_LAYER_ENABLE_DISTANCE_STREAMING = 329,"
    "VER_UE4_REMOVE_ZONES_FROM_MODEL = 330,"
    "VER_UE4_FIX_ANIMATIONBASEPOSE_SERIALIZATION = 331,"
    "VER_UE4_SUPPORT_8_BONE_INFLUENCES_SKELETAL_MESHES = 332,"
    "VER_UE4_ADD_OVERRIDE_GRAVITY_FLAG = 333,"
    "VER_UE4_SUPPORT_GPUSKINNING_8_BONE_INFLUENCES = 334,"
    "VER_UE4_ANIM_SUPPORT_NONUNIFORM_SCALE_ANIMATION = 335,"
    "VER_UE4_ENGINE_VERSION_OBJECT = 336,"
    "VER_UE4_PUBLIC_WORLDS = 337,"
    "VER_UE4_SKELETON_GUID_SERIALIZATION = 338,"
    "VER_UE4_CHARACTER_MOVEMENT_WALKABLE_FLOOR_REFACTOR = 339,"
    "VER_UE4_INVERSE_SQUARED_LIGHTS_DEFAULT = 340,"
    "VER_UE4_DISABLED_SCRIPT_LIMIT_BYTECODE = 341,"
    "VER_UE4_PRIVATE_REMOTE_ROLE = 342,"
    "VER_UE4_FOLIAGE_STATIC_MOBILITY = 343,"
    "VER_UE4_BUILD_SCALE_VECTOR = 344,"
    "VER_UE4_FOLIAGE_COLLISION = 345,"
    "VER_UE4_SKY_BENT_NORMAL = 346,"
    "VER_UE4_LANDSCAPE_COLLISION_DATA_COOKING = 347,"
    "VER_UE4_MORPHTARGET_CPU_TANGENTZDELTA_FORMATCHANGE = 348,"
    "VER_UE4_SOFT_CONSTRAINTS_USE_MASS = 349,"
    "VER_UE4_REFLECTION_DATA_IN_PACKAGES = 350,"
    "VER_UE4_FOLIAGE_MOVABLE_MOBILITY = 351,"
    "VER_UE4_UNDO_BREAK_MATERIALATTRIBUTES_CHANGE = 352,"
    "VER_UE4_ADD_CUSTOMPROFILENAME_CHANGE = 353,"
    "VER_UE4_FLIP_MATERIAL_COORDS = 354,"
    "VER_UE4_MEMBERREFERENCE_IN_PINTYPE = 355,"
    "VER_UE4_VEHICLES_UNIT_CHANGE = 356,"
    "VER_UE4_ANIMATION_REMOVE_NANS = 357,"
    "VER_UE4_SKELETON_ASSET_PROPERTY_TYPE_CHANGE = 358,"
    "VER_UE4_FIX_BLUEPRINT_VARIABLE_FLAGS = 359,"
    "VER_UE4_VEHICLES_UNIT_CHANGE2 = 360,"
    "VER_UE4_UCLASS_SERIALIZE_INTERFACES_AFTER_LINKING = 361,"
    "VER_UE4_STATIC_MESH_SCREEN_SIZE_LODS = 362,"
    "VER_UE4_FIX_MATERIAL_COORDS = 363,"
    "VER_UE4_SPEEDTREE_WIND_V7 = 364,"
    "VER_UE4_LOAD_FOR_EDITOR_GAME = 365,"
    "VER_UE4_SERIALIZE_RICH_CURVE_KEY = 366,"
    "VER_UE4_MOVE_LANDSCAPE_MICS_AND_TEXTURES_WITHIN_LEVEL = 367,"
    "VER_UE4_FTEXT_HISTORY = 368,"
    "VER_UE4_FIX_MATERIAL_COMMENTS = 369,"
    "VER_UE4_STORE_BONE_EXPORT_NAMES = 370,"
    "VER_UE4_MESH_EMITTER_INITIAL_ORIENTATION_DISTRIBUTION = 371,"
    "VER_UE4_DISALLOW_FOLIAGE_ON_BLUEPRINTS = 372,"
    "VER_UE4_FIXUP_MOTOR_UNITS = 373,"
    "VER_UE4_DEPRECATED_MOVEMENTCOMPONENT_MODIFIED_SPEEDS = 374,"
    "VER_UE4_RENAME_CANBECHARACTERBASE = 375,"
    "VER_UE4_GAMEPLAY_TAG_CONTAINER_TAG_TYPE_CHANGE = 376,"
    "VER_UE4_FOLIAGE_SETTINGS_TYPE = 377,"
    "VER_UE4_STATIC_SHADOW_DEPTH_MAPS = 378,"
    "VER_UE4_ADD_TRANSACTIONAL_TO_DATA_ASSETS = 379,"
    "VER_UE4_ADD_LB_WEIGHTBLEND = 380,"
    "VER_UE4_ADD_ROOTCOMPONENT_TO_FOLIAGEACTOR = 381,"
    "VER_UE4_FIX_MATERIAL_PROPERTY_OVERRIDE_SERIALIZE = 382,"
    "VER_UE4_ADD_LINEAR_COLOR_SAMPLER = 383,"
    "VER_UE4_ADD_STRING_ASSET_REFERENCES_MAP = 384,"
    "VER_UE4_BLUEPRINT_USE_SCS_ROOTCOMPONENT_SCALE = 385,"
    "VER_UE4_LEVEL_STREAMING_DRAW_COLOR_TYPE_CHANGE = 386,"
    "VER_UE4_CLEAR_NOTIFY_TRIGGERS = 387,"
    "VER_UE4_SKELETON_ADD_SMARTNAMES = 388,"
    "VER_UE4_ADDED_CURRENCY_CODE_TO_FTEXT = 389,"
    "VER_UE4_ENUM_CLASS_SUPPORT = 390,"
    "VER_UE4_FIXUP_WIDGET_ANIMATION_CLASS = 391,"
    "VER_UE4_SOUND_COMPRESSION_TYPE_ADDED = 392,"
    "VER_UE4_AUTO_WELDING = 393,"
    "VER_UE4_RENAME_CROUCHMOVESCHARACTERDOWN = 394,"
    "VER_UE4_LIGHTMAP_MESH_BUILD_SETTINGS = 395,"
    "VER_UE4_RENAME_SM3_TO_ES3_1 = 396,"
    "VER_UE4_DEPRECATE_UMG_STYLE_ASSETS = 397,"
    "VER_UE4_POST_DUPLICATE_NODE_GUID = 398,"
    "VER_UE4_RENAME_CAMERA_COMPONENT_VIEW_ROTATION = 399,"
    "VER_UE4_CASE_PRESERVING_FNAME = 400,"
    "VER_UE4_RENAME_CAMERA_COMPONENT_CONTROL_ROTATION = 401,"
    "VER_UE4_FIX_REFRACTION_INPUT_MASKING = 402,"
    "VER_UE4_GLOBAL_EMITTER_SPAWN_RATE_SCALE = 403,"
    "VER_UE4_CLEAN_DESTRUCTIBLE_SETTINGS = 404,"
    "VER_UE4_CHARACTER_MOVEMENT_UPPER_IMPACT_BEHAVIOR = 405,"
    "VER_UE4_BP_MATH_VECTOR_EQUALITY_USES_EPSILON = 406,"
    "VER_UE4_FOLIAGE_STATIC_LIGHTING_SUPPORT = 407,"
    "VER_UE4_SLATE_COMPOSITE_FONTS = 408,"
    "VER_UE4_REMOVE_SAVEGAMESUMMARY = 409,"
    "VER_UE4_REMOVE_SKELETALMESH_COMPONENT_BODYSETUP_SERIALIZATION = 410,"
    "VER_UE4_SLATE_BULK_FONT_DATA = 411,"
    "VER_UE4_ADD_PROJECTILE_FRICTION_BEHAVIOR = 412,"
    "VER_UE4_MOVEMENTCOMPONENT_AXIS_SETTINGS = 413,"
    "VER_UE4_GRAPH_INTERACTIVE_COMMENTBUBBLES = 414,"
    "VER_UE4_LANDSCAPE_SERIALIZE_PHYSICS_MATERIALS = 415,"
    "VER_UE4_RENAME_WIDGET_VISIBILITY = 416,"
    "VER_UE4_ANIMATION_ADD_TRACKCURVES = 417,"
    "VER_UE4_MONTAGE_BRANCHING_POINT_REMOVAL = 418,"
    "VER_UE4_BLUEPRINT_ENFORCE_CONST_IN_FUNCTION_OVERRIDES = 419,"
    "VER_UE4_ADD_PIVOT_TO_WIDGET_COMPONENT = 420,"
    "VER_UE4_PAWN_AUTO_POSSESS_AI = 421,"
    "VER_UE4_FTEXT_HISTORY_DATE_TIMEZONE = 422,"
    "VER_UE4_SORT_ACTIVE_BONE_INDICES = 423,"
    "VER_UE4_PERFRAME_MATERIAL_UNIFORM_EXPRESSIONS = 424,"
    "VER_UE4_MIKKTSPACE_IS_DEFAULT = 425,"
    "VER_UE4_LANDSCAPE_GRASS_COOKING = 426,"
    "VER_UE4_FIX_SKEL_VERT_ORIENT_MESH_PARTICLES = 427,"
    "VER_UE4_LANDSCAPE_STATIC_SECTION_OFFSET = 428,"
    "VER_UE4_ADD_MODIFIERS_RUNTIME_GENERATION = 429,"
    "VER_UE4_MATERIAL_MASKED_BLENDMODE_TIDY = 430,"
    "VER_UE4_MERGED_ADD_MODIFIERS_RUNTIME_GENERATION_TO_4_7_DEPRECATED = 431,"
    "VER_UE4_AFTER_MERGED_ADD_MODIFIERS_RUNTIME_GENERATION_TO_4_7_DEPRECATED = 432,"
    "VER_UE4_MERGED_ADD_MODIFIERS_RUNTIME_GENERATION_TO_4_7 = 433,"
    "VER_UE4_AFTER_MERGING_ADD_MODIFIERS_RUNTIME_GENERATION_TO_4_7 = 434,"
    "VER_UE4_SERIALIZE_LANDSCAPE_GRASS_DATA = 435,"
    "VER_UE4_OPTIONALLY_CLEAR_GPU_EMITTERS_ON_INIT = 436,"
    "VER_UE4_SERIALIZE_LANDSCAPE_GRASS_DATA_MATERIAL_GUID = 437,"
    "VER_UE4_BLUEPRINT_GENERATED_CLASS_COMPONENT_TEMPLATES_PUBLIC = 438,"
    "VER_UE4_ACTOR_COMPONENT_CREATION_METHOD = 439,"
    "VER_UE4_K2NODE_EVENT_MEMBER_REFERENCE = 440,"
    "VER_UE4_STRUCT_GUID_IN_PROPERTY_TAG = 441,"
    "VER_UE4_REMOVE_UNUSED_UPOLYS_FROM_UMODEL = 442,"
    "VER_UE4_REBUILD_HIERARCHICAL_INSTANCE_TREES = 443,"
    "VER_UE4_PACKAGE_SUMMARY_HAS_COMPATIBLE_ENGINE_VERSION = 444,"
    "VER_UE4_TRACK_UCS_MODIFIED_PROPERTIES = 445,"
    "VER_UE4_LANDSCAPE_SPLINE_CROSS_LEVEL_MESHES = 446,"
    "VER_UE4_DEPRECATE_USER_WIDGET_DESIGN_SIZE = 447,"
    "VER_UE4_ADD_EDITOR_VIEWS = 448,"
    "VER_UE4_FOLIAGE_WITH_ASSET_OR_CLASS = 449,"
    "VER_UE4_BODYINSTANCE_BINARY_SERIALIZATION = 450,"
    "VER_UE4_SERIALIZE_BLUEPRINT_EVENTGRAPH_FASTCALLS_IN_UFUNCTION = 451,"
    "VER_UE4_INTERPCURVE_SUPPORTS_LOOPING = 452,"
    "VER_UE4_MATERIAL_INSTANCE_BASE_PROPERTY_OVERRIDES_DITHERED_LOD_TRANSITION = 453,"
    "VER_UE4_SERIALIZE_LANDSCAPE_ES2_TEXTURES = 454,"
    "VER_UE4_CONSTRAINT_INSTANCE_MOTOR_FLAGS = 455,"
    "VER_UE4_SERIALIZE_PINTYPE_CONST = 456,"
    "VER_UE4_LIBRARY_CATEGORIES_AS_FTEXT = 457,"
    "VER_UE4_SKIP_DUPLICATE_EXPORTS_ON_SAVE_PACKAGE = 458,"
    "VER_UE4_SERIALIZE_TEXT_IN_PACKAGES = 459,"
    "VER_UE4_ADD_BLEND_MODE_TO_WIDGET_COMPONENT = 460,"
    "VER_UE4_NEW_LIGHTMASS_PRIMITIVE_SETTING = 461,"
    "VER_UE4_REPLACE_SPRING_NOZ_PROPERTY = 462,"
    "VER_UE4_TIGHTLY_PACKED_ENUMS = 463,"
    "VER_UE4_ASSET_IMPORT_DATA_AS_JSON = 464,"
    "VER_UE4_TEXTURE_LEGACY_GAMMA = 465,"
    "VER_UE4_ADDED_NATIVE_SERIALIZATION_FOR_IMMUTABLE_STRUCTURES = 466,"
    "VER_UE4_DEPRECATE_UMG_STYLE_OVERRIDES = 467,"
    "VER_UE4_STATIC_SHADOWMAP_PENUMBRA_SIZE = 468,"
    "VER_UE4_NIAGARA_DATA_OBJECT_DEV_UI_FIX = 469,"
    "VER_UE4_FIXED_DEFAULT_ORIENTATION_OF_WIDGET_COMPONENT = 470,"
    "VER_UE4_REMOVED_MATERIAL_USED_WITH_UI_FLAG = 471,"
    "VER_UE4_CHARACTER_MOVEMENT_ADD_BRAKING_FRICTION = 472,"
    "VER_UE4_BSP_UNDO_FIX = 473,"
    "VER_UE4_DYNAMIC_PARAMETER_DEFAULT_VALUE = 474,"
    "VER_UE4_STATIC_MESH_EXTENDED_BOUNDS = 475,"
    "VER_UE4_ADDED_NON_LINEAR_TRANSITION_BLENDS = 476,"
    "VER_UE4_AO_MATERIAL_MASK = 477,"
    "VER_UE4_NAVIGATION_AGENT_SELECTOR = 478,"
    "VER_UE4_MESH_PARTICLE_COLLISIONS_CONSIDER_PARTICLE_SIZE = 479,"
    "VER_UE4_BUILD_MESH_ADJ_BUFFER_FLAG_EXPOSED = 480,"
    "VER_UE4_MAX_ANGULAR_VELOCITY_DEFAULT = 481,"
    "VER_UE4_APEX_CLOTH_TESSELLATION = 482,"
    "VER_UE4_DECAL_SIZE = 483,"
    "VER_UE4_KEEP_ONLY_PACKAGE_NAMES_IN_STRING_ASSET_REFERENCES_MAP = 484,"
    "VER_UE4_COOKED_ASSETS_IN_EDITOR_SUPPORT = 485,"
    "VER_UE4_DIALOGUE_WAVE_NAMESPACE_AND_CONTEXT_CHANGES = 486,"
    "VER_UE4_MAKE_ROT_RENAME_AND_REORDER = 487,"
    "VER_UE4_K2NODE_VAR_REFERENCEGUIDS = 488,"
    "VER_UE4_SOUND_CONCURRENCY_PACKAGE = 489,"
    "VER_UE4_USERWIDGET_DEFAULT_FOCUSABLE_FALSE = 490,"
    "VER_UE4_BLUEPRINT_CUSTOM_EVENT_CONST_INPUT = 491,"
    "VER_UE4_USE_LOW_PASS_FILTER_FREQ = 492,"
    "VER_UE4_NO_ANIM_BP_CLASS_IN_GAMEPLAY_CODE = 493,"
    "VER_UE4_SCS_STORES_ALLNODES_ARRAY = 494,"
    "VER_UE4_FBX_IMPORT_DATA_RANGE_ENCAPSULATION = 495,"
    "VER_UE4_CAMERA_COMPONENT_ATTACH_TO_ROOT = 496,"
    "VER_UE4_INSTANCED_STEREO_UNIFORM_UPDATE = 497,"
    "VER_UE4_STREAMABLE_TEXTURE_MIN_MAX_DISTANCE = 498,"
    "VER_UE4_INJECT_BLUEPRINT_STRUCT_PIN_CONVERSION_NODES = 499,"
    "VER_UE4_INNER_ARRAY_TAG_INFO = 500,"
    "VER_UE4_FIX_SLOT_NAME_DUPLICATION = 501,"
    "VER_UE4_STREAMABLE_TEXTURE_AABB = 502,"
    "VER_UE4_PROPERTY_GUID_IN_PROPERTY_TAG = 503,"
    "VER_UE4_NAME_HASHES_SERIALIZED = 504,"
    "VER_UE4_INSTANCED_STEREO_UNIFORM_REFACTOR = 505,"
    "VER_UE4_COMPRESSED_SHADER_RESOURCES = 506,"
    "VER_UE4_PRELOAD_DEPENDENCIES_IN_COOKED_EXPORTS = 507,"
    "VER_UE4_TemplateIndex_IN_COOKED_EXPORTS = 508,"
    "VER_UE4_PROPERTY_TAG_SET_MAP_SUPPORT = 509,"
    "VER_UE4_ADDED_SEARCHABLE_NAMES = 510,"
    "VER_UE4_64BIT_EXPORTMAP_SERIALSIZES = 511,"
    "VER_UE4_SKYLIGHT_MOBILE_IRRADIANCE_MAP = 512,"
    "VER_UE4_ADDED_SWEEP_WHILE_WALKING_FLAG = 513,"
    "VER_UE4_ADDED_SOFT_OBJECT_PATH = 514,"
    "VER_UE4_AUTOMATIC_VERSION_PLUS_ONE = 515,"
    "VER_UE4_AUTOMATIC_VERSION = 514,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUnrealEngineObjectLicenseeUE4Version = {"
    "VER_LIC_NONE = 0,"
    "VER_LIC_AUTOMATIC_VERSION_PLUS_ONE = 1,"
    "VER_LIC_AUTOMATIC_VERSION = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDayOfWeek = {"
    "Monday = 0,"
    "Tuesday = 1,"
    "Wednesday = 2,"
    "Thursday = 3,"
    "Friday = 4,"
    "Saturday = 5,"
    "Sunday = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMonthOfYear = {"
    "January = 1,"
    "February = 2,"
    "March = 3,"
    "April = 4,"
    "May = 5,"
    "June = 6,"
    "July = 7,"
    "August = 8,"
    "September = 9,"
    "October = 10,"
    "November = 11,"
    "December = 12,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAutomationEventType = {"
    "Info = 0,"
    "Warning = 1,"
    "Error = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInterpCurveMode = {"
    "CIM_Linear = 0,"
    "CIM_CurveAuto = 1,"
    "CIM_Constant = 2,"
    "CIM_CurveUser = 3,"
    "CIM_CurveBreak = 4,"
    "CIM_CurveAutoClamped = 5,"
    "CIM_Unknown = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EState = {"
    "State_Uninitialized = 0,"
    "State_Created = 1,"
    "State_Connecting = 2,"
    "State_ReadyForRW = 3,"
    "State_WaitingForRW = 4,"
    "State_ErrorPipeClosedUnexpectedly = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWaitAndForkResult = {"
    "Error = 0,"
    "Parent = 1,"
    "Child = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAsyncIOPriority = {"
    "AIOP_MIN = 0,"
    "AIOP_Precache = 0,"
    "AIOP_Low = 1,"
    "AIOP_BelowNormal = 2,"
    "AIOP_Normal = 3,"
    "AIOP_High = 4,"
    "AIOP_CriticalPath = 5,"
    "AIOP_MAX = 5,"
    "AIOP_NUM = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPlatformFileRead = {"
    "None = 0,"
    "AllowWrite = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPlatformFileWrite = {"
    "None = 0,"
    "AllowRead = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EThreadPriority = {"
    "TPri_Normal = 0,"
    "TPri_AboveNormal = 1,"
    "TPri_BelowNormal = 2,"
    "TPri_Highest = 3,"
    "TPri_Lowest = 4,"
    "TPri_SlightlyBelowNormal = 5,"
    "TPri_TimeCritical = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFileWrite = {"
    "FILEWRITE_None = 0,"
    "FILEWRITE_NoFail = 1,"
    "FILEWRITE_NoReplaceExisting = 2,"
    "FILEWRITE_EvenIfReadOnly = 4,"
    "FILEWRITE_Append = 8,"
    "FILEWRITE_AllowRead = 16,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFileRead = {"
    "FILEREAD_None = 0,"
    "FILEREAD_NoFail = 1,"
    "FILEREAD_Silent = 2,"
    "FILEREAD_AllowWrite = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECopyResult = {"
    "COPY_OK = 0,"
    "COPY_Fail = 1,"
    "COPY_Canceled = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFileOpenFlags = {"
    "IO_READ = 1,"
    "IO_WRITE = 2,"
    "IO_APPEND = 64,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EHashOptions = {"
    "None = 0,"
    "EnableVerify = 1,"
    "ErrorMissingHash = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EEncodingOptions = {"
    "AutoDetect = 0,"
    "ForceAnsi = 1,"
    "ForceUnicode = 2,"
    "ForceUTF8 = 3,"
    "ForceUTF8WithoutBOM = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBulkDataType = {"
    "Default = 0,"
    "MediaTexture = 1,"
    "VREyeBuffer = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EResourceAlignment = {"
    "VERTEXBUFFER_ALIGNMENT = 0,"
    "INDEXBUFFER_ALIGNMENT = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGuidFormats = {"
    "Digits = 0,"
    "DigitsWithHyphens = 1,"
    "DigitsWithHyphensInBraces = 2,"
    "DigitsWithHyphensInParentheses = 3,"
    "HexValuesInBraces = 4,"
    "UniqueObjectGuid = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EByteOrderMark = {"
    "UTF8 = 0,"
    "Unspecified = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EScopeLogTimeUnits = {"
    "ScopeLog_Milliseconds = 0,"
    "ScopeLog_Seconds = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStatType = {"
    "STATTYPE_CycleCounter = 0,"
    "STATTYPE_AccumulatorFLOAT = 1,"
    "STATTYPE_AccumulatorDWORD = 2,"
    "STATTYPE_CounterFLOAT = 3,"
    "STATTYPE_CounterDWORD = 4,"
    "STATTYPE_MemoryCounter = 5,"
    "STATTYPE_Error = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMemoryOperation = {"
    "Invalid = 0,"
    "Alloc = 1,"
    "Free = 2,"
    "Realloc = 3,"
    "Num = 4,"
    "Mask = 7,"
    "NumBits = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConstructor = {"
    "FOR_POOL = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMemZeroed = {"
    "MEM_Zeroed = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMemOned = {"
    "MEM_Oned = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELargeMemoryReaderFlags = {"
    "None = 0,"
    "TakeOwnership = 1,"
    "Persistent = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EQueueMode = {"
    "Mpsc = 0,"
    "Spsc = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStreamingStatus = {"
    "LEVEL_Unloaded = 0,"
    "LEVEL_UnloadedButStillAround = 1,"
    "LEVEL_Loading = 2,"
    "LEVEL_Loaded = 3,"
    "LEVEL_MakingVisible = 4,"
    "LEVEL_Visible = 5,"
    "LEVEL_Preloading = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConfigFileHierarchy = {"
    "AbsoluteBase = 0,"
    "EngineDirBase = 1,"
    "EngineDir_BasePlatform = 2,"
    "EngineDirBase_NotForLicensees = 3,"
    "EngineDirBase_NoRedist = 4,"
    "GameDirDefault = 5,"
    "GameDirDedicatedServer = 6,"
    "GameDirDefault_NotForLicensees = 7,"
    "GameDirDefault_NoRedist = 8,"
    "EngineDir_Platform = 9,"
    "EngineDir_Platform_NotForLicensees = 10,"
    "EngineDir_Platform_NoRedist = 11,"
    "GameDir_Platform = 12,"
    "GameDir_Platform_NotForLicensees = 13,"
    "GameDir_Platform_NoRedist = 14,"
    "UserSettingsDir_EngineDir_User = 15,"
    "UserDir_User = 16,"
    "GameDir_User = 17,"
    "NumHierarchyFiles = 18,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConfigCacheType = {"
    "DiskBacked = 0,"
    "Temporary = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConsoleVariableFlags = {"
    "ECVF_Default = 0,"
    "ECVF_Cheat = 1,"
    "ECVF_ReadOnly = 4,"
    "ECVF_Unregistered = 8,"
    "ECVF_CreatedFromIni = 16,"
    "ECVF_RenderThreadSafe = 32,"
    "ECVF_Scalability = 64,"
    "ECVF_ScalabilityGroup = 128,"
    "ECVF_SetByMask = -16777216,"
    "ECVF_SetByConstructor = 0,"
    "ECVF_SetByScalability = 16777216,"
    "ECVF_SetByGameSetting = 33554432,"
    "ECVF_SetByProjectSetting = 50331648,"
    "ECVF_SetByDeviceProfile = 67108864,"
    "ECVF_SetBySystemSettingsIni = 83886080,"
    "ECVF_SetByConsoleVariablesIni = 100663296,"
    "ECVF_SetByCommandline = 117440512,"
    "ECVF_SetByCode = 134217728,"
    "ECVF_SetByConsole = 150994944,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlowTaskVisibility = {"
    "Default = 0,"
    "ForceVisible = 1,"
    "Invisible = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELifeStage = {"
    "LS_BaseContructed = 0,"
    "LS_Contructed = 1,"
    "LS_ThreadSet = 2,"
    "LS_PrequisitesSetup = 3,"
    "LS_Queued = 4,"
    "LS_Executing = 5,"
    "LS_Deconstucted = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAsyncExecution = {"
    "TaskGraph = 0,"
    "Thread = 1,"
    "ThreadPool = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.MatchType = {"
    "Exact = 0,"
    "Contains = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOnScreenMessageSeverity = {"
    "Info = 0,"
    "Warning = 1,"
    "Error = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EModuleLoadResult = {"
    "Success = 0,"
    "FileNotFound = 1,"
    "FileIncompatible = 2,"
    "CouldNotBeLoadedByOS = 3,"
    "FailedToInitialize = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EModuleChangeReason = {"
    "ModuleLoaded = 0,"
    "ModuleUnloaded = 1,"
    "PluginDirectoryChanged = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECheckModuleCompatibilityFlags = {"
    "None = 0,"
    "DisplayUpToDateModules = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFunctionFlags = {"
    "FUNC_None = 0,"
    "FUNC_Final = 1,"
    "FUNC_RequiredAPI = 2,"
    "FUNC_BlueprintAuthorityOnly = 4,"
    "FUNC_BlueprintCosmetic = 8,"
    "FUNC_Net = 64,"
    "FUNC_NetReliable = 128,"
    "FUNC_NetRequest = 256,"
    "FUNC_Exec = 512,"
    "FUNC_Native = 1024,"
    "FUNC_Event = 2048,"
    "FUNC_NetResponse = 4096,"
    "FUNC_Static = 8192,"
    "FUNC_NetMulticast = 16384,"
    "FUNC_MulticastDelegate = 65536,"
    "FUNC_Public = 131072,"
    "FUNC_Private = 262144,"
    "FUNC_Protected = 524288,"
    "FUNC_Delegate = 1048576,"
    "FUNC_NetServer = 2097152,"
    "FUNC_HasOutParms = 4194304,"
    "FUNC_HasDefaults = 8388608,"
    "FUNC_NetClient = 16777216,"
    "FUNC_DLLImport = 33554432,"
    "FUNC_BlueprintCallable = 67108864,"
    "FUNC_BlueprintEvent = 134217728,"
    "FUNC_BlueprintPure = 268435456,"
    "FUNC_EditorOnly = 536870912,"
    "FUNC_Const = 1073741824,"
    "FUNC_NetValidate = -2147483648,"
    "FUNC_AllFlags = -1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EExprToken = {"
    "EX_LocalVariable = 0,"
    "EX_InstanceVariable = 1,"
    "EX_DefaultVariable = 2,"
    "EX_Return = 4,"
    "EX_Jump = 6,"
    "EX_JumpIfNot = 7,"
    "EX_Assert = 9,"
    "EX_Nothing = 11,"
    "EX_Let = 15,"
    "EX_ClassContext = 18,"
    "EX_MetaCast = 19,"
    "EX_LetBool = 20,"
    "EX_EndParmValue = 21,"
    "EX_EndFunctionParms = 22,"
    "EX_Self = 23,"
    "EX_Skip = 24,"
    "EX_Context = 25,"
    "EX_Context_FailSilent = 26,"
    "EX_VirtualFunction = 27,"
    "EX_FinalFunction = 28,"
    "EX_IntConst = 29,"
    "EX_FloatConst = 30,"
    "EX_StringConst = 31,"
    "EX_ObjectConst = 32,"
    "EX_NameConst = 33,"
    "EX_RotationConst = 34,"
    "EX_VectorConst = 35,"
    "EX_ByteConst = 36,"
    "EX_IntZero = 37,"
    "EX_IntOne = 38,"
    "EX_True = 39,"
    "EX_False = 40,"
    "EX_TextConst = 41,"
    "EX_NoObject = 42,"
    "EX_TransformConst = 43,"
    "EX_IntConstByte = 44,"
    "EX_NoInterface = 45,"
    "EX_DynamicCast = 46,"
    "EX_StructConst = 47,"
    "EX_EndStructConst = 48,"
    "EX_SetArray = 49,"
    "EX_EndArray = 50,"
    "EX_UnicodeStringConst = 52,"
    "EX_Int64Const = 53,"
    "EX_UInt64Const = 54,"
    "EX_PrimitiveCast = 56,"
    "EX_SetSet = 57,"
    "EX_EndSet = 58,"
    "EX_SetMap = 59,"
    "EX_EndMap = 60,"
    "EX_SetConst = 61,"
    "EX_EndSetConst = 62,"
    "EX_MapConst = 63,"
    "EX_EndMapConst = 64,"
    "EX_StructMemberContext = 66,"
    "EX_LetMulticastDelegate = 67,"
    "EX_LetDelegate = 68,"
    "EX_LocalOutVariable = 72,"
    "EX_DeprecatedOp4A = 74,"
    "EX_InstanceDelegate = 75,"
    "EX_PushExecutionFlow = 76,"
    "EX_PopExecutionFlow = 77,"
    "EX_ComputedJump = 78,"
    "EX_PopExecutionFlowIfNot = 79,"
    "EX_Breakpoint = 80,"
    "EX_InterfaceContext = 81,"
    "EX_ObjToInterfaceCast = 82,"
    "EX_EndOfScript = 83,"
    "EX_CrossInterfaceCast = 84,"
    "EX_InterfaceToObjCast = 85,"
    "EX_WireTracepoint = 90,"
    "EX_SkipOffsetConst = 91,"
    "EX_AddMulticastDelegate = 92,"
    "EX_ClearMulticastDelegate = 93,"
    "EX_Tracepoint = 94,"
    "EX_LetObj = 95,"
    "EX_LetWeakObjPtr = 96,"
    "EX_BindDelegate = 97,"
    "EX_RemoveMulticastDelegate = 98,"
    "EX_CallMulticastDelegate = 99,"
    "EX_LetValueOnPersistentFrame = 100,"
    "EX_ArrayConst = 101,"
    "EX_EndArrayConst = 102,"
    "EX_SoftObjectConst = 103,"
    "EX_CallMath = 104,"
    "EX_SwitchValue = 105,"
    "EX_InstrumentationEvent = 106,"
    "EX_ArrayGetByRef = 107,"
    "EX_Max = 256,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECastToken = {"
    "CST_ObjectToInterface = 70,"
    "CST_ObjectToBool = 71,"
    "CST_InterfaceToBool = 73,"
    "CST_Max = 255,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlueprintTextLiteralType = {"
    "Empty = 0,"
    "LocalizedText = 1,"
    "InvariantText = 2,"
    "LiteralString = 3,"
    "StringTableEntry = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELoadFlags = {"
    "LOAD_None = 0,"
    "LOAD_Async = 1,"
    "LOAD_NoWarn = 2,"
    "LOAD_EditorOnly = 4,"
    "LOAD_ResolvingDeferredExports = 8,"
    "LOAD_Verify = 16,"
    "LOAD_AllowDll = 32,"
    "LOAD_NoVerify = 128,"
    "LOAD_IsVerifying = 256,"
    "LOAD_DisableDependencyPreloading = 4096,"
    "LOAD_Quiet = 8192,"
    "LOAD_FindIfFail = 16384,"
    "LOAD_MemoryReader = 32768,"
    "LOAD_NoRedirects = 65536,"
    "LOAD_ForDiff = 131072,"
    "LOAD_PackageForPIE = 524288,"
    "LOAD_DeferDependencyLoads = 1048576,"
    "LOAD_ForFileDiff = 2097152,"
    "LOAD_DisableCompileOnLoad = 4194304,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESaveFlags = {"
    "SAVE_None = 0,"
    "SAVE_NoError = 1,"
    "SAVE_FromAutosave = 2,"
    "SAVE_KeepDirty = 4,"
    "SAVE_KeepGUID = 8,"
    "SAVE_Async = 16,"
    "SAVE_Unversioned = 32,"
    "SAVE_CutdownPackage = 64,"
    "SAVE_KeepEditorOnlyCookedPackages = 128,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPackageFlags = {"
    "PKG_None = 0,"
    "PKG_NewlyCreated = 1,"
    "PKG_ClientOptional = 2,"
    "PKG_ServerSideOnly = 4,"
    "PKG_CompiledIn = 16,"
    "PKG_ForDiffing = 32,"
    "PKG_EditorOnly = 64,"
    "PKG_Developer = 128,"
    "PKG_ContainsMapData = 16384,"
    "PKG_Need = 32768,"
    "PKG_Compiling = 65536,"
    "PKG_ContainsMap = 131072,"
    "PKG_RequiresLocalizationGather = 262144,"
    "PKG_DisallowLazyLoading = 524288,"
    "PKG_PlayInEditor = 1048576,"
    "PKG_ContainsScript = 2097152,"
    "PKG_ReloadingForCooker = 1073741824,"
    "PKG_FilterEditorOnly = -2147483648,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStaticConstructor = {"
    "EC_StaticConstructor = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInternal = {"
    "EC_InternalUseOnlyConstructor = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECppProperty = {"
    "EC_CppProperty = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EClassFlags = {"
    "CLASS_None = 0,"
    "CLASS_Abstract = 1,"
    "CLASS_DefaultConfig = 2,"
    "CLASS_Config = 4,"
    "CLASS_Transient = 8,"
    "CLASS_Parsed = 16,"
    "CLASS_AdvancedDisplay = 64,"
    "CLASS_Native = 128,"
    "CLASS_NoExport = 256,"
    "CLASS_NotPlaceable = 512,"
    "CLASS_PerObjectConfig = 1024,"
    "CLASS_EditInlineNew = 4096,"
    "CLASS_CollapseCategories = 8192,"
    "CLASS_Interface = 16384,"
    "CLASS_CustomConstructor = 32768,"
    "CLASS_Const = 65536,"
    "CLASS_CompiledFromBlueprint = 262144,"
    "CLASS_MinimalAPI = 524288,"
    "CLASS_RequiredAPI = 1048576,"
    "CLASS_DefaultToInstanced = 2097152,"
    "CLASS_TokenStreamAssembled = 4194304,"
    "CLASS_HasInstancedReference = 8388608,"
    "CLASS_Hidden = 16777216,"
    "CLASS_Deprecated = 33554432,"
    "CLASS_HideDropDown = 67108864,"
    "CLASS_GlobalUserConfig = 134217728,"
    "CLASS_Intrinsic = 268435456,"
    "CLASS_Constructed = 536870912,"
    "CLASS_ConfigDoNotCheckDefaults = 1073741824,"
    "CLASS_NewerVersionExists = -2147483648,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EObjectFlags = {"
    "RF_NoFlags = 0,"
    "RF_Public = 1,"
    "RF_Standalone = 2,"
    "RF_MarkAsNative = 4,"
    "RF_Transactional = 8,"
    "RF_ClassDefaultObject = 16,"
    "RF_ArchetypeObject = 32,"
    "RF_Transient = 64,"
    "RF_MarkAsRootSet = 128,"
    "RF_TagGarbageTemp = 256,"
    "RF_NeedInitialization = 512,"
    "RF_NeedLoad = 1024,"
    "RF_KeepForCooker = 2048,"
    "RF_NeedPostLoad = 4096,"
    "RF_NeedPostLoadSubobjects = 8192,"
    "RF_NewerVersionExists = 16384,"
    "RF_BeginDestroyed = 32768,"
    "RF_FinishDestroyed = 65536,"
    "RF_BeingRegenerated = 131072,"
    "RF_DefaultSubObject = 262144,"
    "RF_WasLoaded = 524288,"
    "RF_TextExportTransient = 1048576,"
    "RF_LoadCompleted = 2097152,"
    "RF_InheritableComponentTemplate = 4194304,"
    "RF_DuplicateTransient = 8388608,"
    "RF_StrongRefOnFrame = 16777216,"
    "RF_NonPIEDuplicateTransient = 33554432,"
    "RF_Dynamic = 67108864,"
    "RF_WillBeLoaded = 134217728,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInternalObjectFlags = {"
    "None = 0,"
    "ReachableInCluster = 8388608,"
    "ClusterRoot = 16777216,"
    "Native = 33554432,"
    "Async = 67108864,"
    "AsyncLoading = 134217728,"
    "Unreachable = 268435456,"
    "PendingKill = 536870912,"
    "RootSet = 1073741824,"
    "GarbageCollectionKeepFlags = 234881024,"
    "AllFlags = 2139095040,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELoadConfigPropagationFlags = {"
    "LCPF_None = 0,"
    "LCPF_ReadParentSections = 1,"
    "LCPF_PropagateToChildDefaultObjects = 2,"
    "LCPF_PropagateToInstances = 4,"
    "LCPF_ReloadingConfigData = 8,"
    "LCPF_PersistentFlags = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInvalidPtr = {"
    "InvalidPtrValue = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConstructDynamicType = {"
    "OnlyAllocateClassObject = 0,"
    "CallZConstructor = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPropertyClass = {"
    "Byte = 0,"
    "Int8 = 1,"
    "Int16 = 2,"
    "Int = 3,"
    "Int64 = 4,"
    "UInt16 = 5,"
    "UInt32 = 6,"
    "UInt64 = 7,"
    "UnsizedInt = 8,"
    "UnsizedUInt = 9,"
    "Float = 10,"
    "Double = 11,"
    "Bool = 12,"
    "SoftClass = 13,"
    "WeakObject = 14,"
    "LazyObject = 15,"
    "SoftObject = 16,"
    "Class = 17,"
    "Object = 18,"
    "Interface = 19,"
    "Name = 20,"
    "Str = 21,"
    "Array = 22,"
    "Map = 23,"
    "Set = 24,"
    "Struct = 25,"
    "Delegate = 26,"
    "MulticastDelegate = 27,"
    "Text = 28,"
    "Enum = 29,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENativeBool = {"
    "NotNative = 0,"
    "Native = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESerialNumberConstants = {"
    "START_SERIAL_NUMBER = 1000,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EObjectMark = {"
    "OBJECTMARK_NOMARKS = 0,"
    "OBJECTMARK_Saved = 4,"
    "OBJECTMARK_TagImp = 8,"
    "OBJECTMARK_TagExp = 16,"
    "OBJECTMARK_NotForClient = 32,"
    "OBJECTMARK_NotForServer = 64,"
    "OBJECTMARK_NotAlwaysLoadedForEditorGame = 128,"
    "OBJECTMARK_EditorOnly = 256,"
    "OBJECTMARK_ALLMARKS = -1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETagType = {"
    "TT_Hidden = 0,"
    "TT_Alphabetical = 1,"
    "TT_Numerical = 2,"
    "TT_Dimensional = 3,"
    "TT_Chronological = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETagDisplay = {"
    "TD_None = 0,"
    "TD_Date = 1,"
    "TD_Time = 2,"
    "TD_InvariantTz = 4,"
    "TD_Memory = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGCReferenceType = {"
    "GCRT_None = 0,"
    "GCRT_Object = 1,"
    "GCRT_PersistentObject = 2,"
    "GCRT_ArrayObject = 3,"
    "GCRT_ArrayStruct = 4,"
    "GCRT_FixedArray = 5,"
    "GCRT_AddStructReferencedObjects = 6,"
    "GCRT_AddReferencedObjects = 7,"
    "GCRT_AddTMapReferencedObjects = 8,"
    "GCRT_AddTSetReferencedObjects = 9,"
    "GCRT_EndOfPointer = 10,"
    "GCRT_EndOfStream = 11,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGCArrayInfoPlaceholder = {"
    "E_GCSkipIndexPlaceholder = -559039810,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStructFlags = {"
    "STRUCT_NoFlags = 0,"
    "STRUCT_Native = 1,"
    "STRUCT_IdenticalNative = 2,"
    "STRUCT_HasInstancedReference = 4,"
    "STRUCT_NoExport = 8,"
    "STRUCT_Atomic = 16,"
    "STRUCT_Immutable = 32,"
    "STRUCT_AddStructReferencedObjects = 64,"
    "STRUCT_RequiredAPI = 512,"
    "STRUCT_NetSerializeNative = 1024,"
    "STRUCT_SerializeNative = 2048,"
    "STRUCT_CopyNative = 4096,"
    "STRUCT_IsPlainOldData = 8192,"
    "STRUCT_NoDestructor = 16384,"
    "STRUCT_ZeroConstructor = 32768,"
    "STRUCT_ExportTextItemNative = 65536,"
    "STRUCT_ImportTextItemNative = 131072,"
    "STRUCT_PostSerializeNative = 262144,"
    "STRUCT_SerializeFromMismatchedTag = 524288,"
    "STRUCT_NetDeltaSerializeNative = 1048576,"
    "STRUCT_Inherit = 20,"
    "STRUCT_ComputedFlags = 2096194,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGetByNameFlags = {"
    "None = 0,"
    "ErrorIfNotFound = 1,"
    "CaseSensitive = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECppForm = {"
    "Regular = 0,"
    "Namespaced = 1,"
    "EnumClass = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECastType = {"
    "UObjectToUObject = 0,"
    "InterfaceToUObject = 1,"
    "UObjectToInterface = 2,"
    "InterfaceToInterface = 3,"
    "FromCastFlags = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELifetimeCondition = {"
    "COND_None = 0,"
    "COND_InitialOnly = 1,"
    "COND_OwnerOnly = 2,"
    "COND_SkipOwner = 3,"
    "COND_SimulatedOnly = 4,"
    "COND_AutonomousOnly = 5,"
    "COND_SimulatedOrPhysics = 6,"
    "COND_InitialOrOwner = 7,"
    "COND_Custom = 8,"
    "COND_ReplayOrOwner = 9,"
    "COND_ReplayOnly = 10,"
    "COND_SimulatedOnlyNoReplay = 11,"
    "COND_SimulatedOrPhysicsNoReplay = 12,"
    "COND_SkipReplay = 13,"
    "COND_Max = 14,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELifetimeRepNotifyCondition = {"
    "REPNOTIFY_OnChanged = 0,"
    "REPNOTIFY_Always = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESoftObjectPathCollectType = {"
    "NeverCollect = 0,"
    "EditorOnlyCollect = 1,"
    "AlwaysCollect = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPropertyExportCPPFlags = {"
    "CPPF_None = 0,"
    "CPPF_OptionalValue = 1,"
    "CPPF_ArgumentOrReturnValue = 2,"
    "CPPF_Implementation = 4,"
    "CPPF_CustomTypeName = 8,"
    "CPPF_NoConst = 16,"
    "CPPF_NoRef = 32,"
    "CPPF_NoStaticArray = 64,"
    "CPPF_BlueprintCppBackend = 128,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.SuperClassFlags = {"
    "ExcludeSuper = 0,"
    "IncludeSuper = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.DeprecatedPropertyFlags = {"
    "ExcludeDeprecated = 0,"
    "IncludeDeprecated = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.InterfaceClassFlags = {"
    "ExcludeInterfaces = 0,"
    "IncludeInterfaces = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPropertyValueIteratorFlags = {"
    "NoRecursion = 0,"
    "FullRecursion = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPropertyType = {"
    "CPT_None = 0,"
    "CPT_Byte = 1,"
    "CPT_UInt16 = 2,"
    "CPT_UInt32 = 3,"
    "CPT_UInt64 = 4,"
    "CPT_Int8 = 5,"
    "CPT_Int16 = 6,"
    "CPT_Int = 7,"
    "CPT_Int64 = 8,"
    "CPT_Bool = 9,"
    "CPT_Bool8 = 10,"
    "CPT_Bool16 = 11,"
    "CPT_Bool32 = 12,"
    "CPT_Bool64 = 13,"
    "CPT_Float = 14,"
    "CPT_ObjectReference = 15,"
    "CPT_Name = 16,"
    "CPT_Delegate = 17,"
    "CPT_Interface = 18,"
    "CPT_Unused_Index_19 = 19,"
    "CPT_Struct = 20,"
    "CPT_Unused_Index_21 = 21,"
    "CPT_Unused_Index_22 = 22,"
    "CPT_String = 23,"
    "CPT_Text = 24,"
    "CPT_MulticastDelegate = 25,"
    "CPT_WeakObjectReference = 26,"
    "CPT_LazyObjectReference = 27,"
    "CPT_SoftObjectReference = 28,"
    "CPT_Double = 29,"
    "CPT_Map = 30,"
    "CPT_Set = 31,"
    "CPT_MAX = 32,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELocMetadataType = {"
    "None = 0,"
    "Boolean = 1,"
    "String = 2,"
    "Array = 3,"
    "Object = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPropertyLocalizationGathererTextFlags = {"
    "None = 0,"
    "ForceHasScript = 1,"
    "ForceEditorOnlyProperties = 2,"
    "ForceEditorOnlyScriptData = 4,"
    "ForceEditorOnly = 6,"
    "SkipSubObjects = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPropertyLocalizationGathererResultFlags = {"
    "Empty = 0,"
    "HasText = 1,"
    "HasScript = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESavePackageResult = {"
    "Success = 0,"
    "Error = 1,"
    "Canceled = 2,"
    "ContainsEditorOnlyData = 3,"
    "ReferencedOnlyByEditorOnlyData = 4,"
    "ReplaceCompletely = 5,"
    "GenerateStub = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDebugSerializationFlags = {"
    "DSF_None = 0,"
    "DSF_IgnoreDiff = 1,"
    "DSF_EnableCookerWarnings = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPropertyPortFlags = {"
    "PPF_None = 0,"
    "PPF_Delimited = 2,"
    "PPF_CheckReferences = 4,"
    "PPF_ExportsNotFullyQualified = 8,"
    "PPF_AttemptNonQualifiedSearch = 16,"
    "PPF_RestrictImportTypes = 32,"
    "PPF_SerializedAsImportText = 64,"
    "PPF_SubobjectsOnly = 256,"
    "PPF_DeepComparison = 512,"
    "PPF_DeepCompareInstances = 1024,"
    "PPF_Copy = 2048,"
    "PPF_Duplicate = 4096,"
    "PPF_SimpleObjectText = 8192,"
    "PPF_ParsingDefaultProperties = 32768,"
    "PPF_IncludeTransient = 131072,"
    "PPF_DeltaComparison = 262144,"
    "PPF_PropertyWindow = 524288,"
    "PPF_DebugDump = 2097152,"
    "PPF_DuplicateForPIE = 4194304,"
    "PPF_SeparateDeclare = 8388608,"
    "PPF_SeparateDefine = 16777216,"
    "PPF_BlueprintDebugView = 33554432,"
    "PPF_ConsoleVariable = 67108864,"
    "PPF_UseDeprecatedProperties = 134217728,"
    "PPF_ExportCpp = 268435456,"
    "PPF_ForceTaggedSerialization = 536870912,"
    "PPF_DuplicateVerbatim = 1073741824,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBulkDataFlags = {"
    "BULKDATA_None = 0,"
    "BULKDATA_PayloadAtEndOfFile = 1,"
    "BULKDATA_SerializeCompressedZLIB = 2,"
    "BULKDATA_ForceSingleElementSerialization = 4,"
    "BULKDATA_SingleUse = 8,"
    "BULKDATA_Unused = 32,"
    "BULKDATA_ForceInlinePayload = 64,"
    "BULKDATA_SerializeCompressed = 2,"
    "BULKDATA_ForceStreamPayload = 128,"
    "BULKDATA_PayloadInSeperateFile = 256,"
    "BULKDATA_SerializeCompressedBitWindow = 512,"
    "BULKDATA_Force_NOT_InlinePayload = 1024,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBulkDataLockStatus = {"
    "LOCKSTATUS_Unlocked = 0,"
    "LOCKSTATUS_ReadOnlyLock = 1,"
    "LOCKSTATUS_ReadWriteLock = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBulkDataLockFlags = {"
    "LOCK_READ_ONLY = 1,"
    "LOCK_READ_WRITE = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELinkerStatus = {"
    "LINKER_Failed = 0,"
    "LINKER_Loaded = 1,"
    "LINKER_TimedOut = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVerifyResult = {"
    "VERIFY_Failed = 0,"
    "VERIFY_Success = 1,"
    "VERIFY_Redirected = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENotifyRegistrationType = {"
    "NRT_Class = 0,"
    "NRT_ClassCDO = 1,"
    "NRT_Struct = 2,"
    "NRT_Enum = 3,"
    "NRT_Package = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENotifyRegistrationPhase = {"
    "NRP_Added = 0,"
    "NRP_Started = 1,"
    "NRP_Finished = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAsyncPackageLoadingState = {"
    "NewPackage = 0,"
    "WaitingForSummary = 1,"
    "StartImportPackages = 2,"
    "WaitingForImportPackages = 3,"
    "SetupImports = 4,"
    "SetupExports = 5,"
    "ProcessNewImportsAndExports = 6,"
    "WaitingForPostLoad = 7,"
    "ReadyForPostLoad = 8,"
    "PostLoad_Etc = 9,"
    "PackageComplete = 10,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EEventLoadNode = {"
    "Package_LoadSummary = 0,"
    "Package_SetupImports = 1,"
    "Package_ExportsSerialized = 2,"
    "Package_NumPhases = 3,"
    "ImportOrExport_Create = 0,"
    "ImportOrExport_Serialize = 1,"
    "Import_NumPhases = 2,"
    "Export_StartIO = 2,"
    "Export_NumPhases = 3,"
    "MAX_NumPhases = 3,"
    "Invalid_Value = -1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EControllerHand = {"
    "Left = 0,"
    "Right = 1,"
    "AnyHand = 2,"
    "Pad = 3,"
    "ExternalCamera = 4,"
    "Gun = 5,"
    "Special_1 = 6,"
    "Special_2 = 7,"
    "Special_3 = 8,"
    "Special_4 = 9,"
    "Special_5 = 10,"
    "Special_6 = 11,"
    "Special_7 = 12,"
    "Special_8 = 13,"
    "Special_9 = 14,"
    "Special_10 = 15,"
    "Special_11 = 16,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EKeyFlags = {"
    "GamepadKey = 1,"
    "MouseButton = 2,"
    "ModifierKey = 4,"
    "NotBlueprintBindableKey = 8,"
    "FloatAxis = 16,"
    "VectorAxis = 32,"
    "UpdateAxisWithoutSamples = 64,"
    "NoFlags = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInputAxisType = {"
    "None = 0,"
    "Float = 1,"
    "Vector = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECacheApplyPhase = {"
    "PostSimpleConstructionScript = 0,"
    "PostUserConstructionScript = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELightComponentType = {"
    "LightType_Directional = 0,"
    "LightType_Point = 1,"
    "LightType_Spot = 2,"
    "LightType_MAX = 3,"
    "LightType_NumBits = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELightMapInteractionType = {"
    "LMIT_None = 0,"
    "LMIT_Texture = 2,"
    "LMIT_NumBits = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShadowMapInteractionType = {"
    "SMIT_None = 0,"
    "SMIT_Texture = 2,"
    "SMIT_NumBits = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialProperty = {"
    "MP_EmissiveColor = 0,"
    "MP_Opacity = 1,"
    "MP_OpacityMask = 2,"
    "MP_DiffuseColor = 3,"
    "MP_SpecularColor = 4,"
    "MP_BaseColor = 5,"
    "MP_Metallic = 6,"
    "MP_Specular = 7,"
    "MP_Roughness = 8,"
    "MP_Normal = 9,"
    "MP_WorldPositionOffset = 10,"
    "MP_WorldDisplacement = 11,"
    "MP_TessellationMultiplier = 12,"
    "MP_SubsurfaceColor = 13,"
    "MP_CustomData0 = 14,"
    "MP_CustomData1 = 15,"
    "MP_AmbientOcclusion = 16,"
    "MP_Refraction = 17,"
    "MP_CustomizedUVs0 = 18,"
    "MP_CustomizedUVs1 = 19,"
    "MP_CustomizedUVs2 = 20,"
    "MP_CustomizedUVs3 = 21,"
    "MP_CustomizedUVs4 = 22,"
    "MP_CustomizedUVs5 = 23,"
    "MP_CustomizedUVs6 = 24,"
    "MP_CustomizedUVs7 = 25,"
    "MP_PixelDepthOffset = 26,"
    "MP_MaterialAttributes = 27,"
    "MP_CustomOutput = 28,"
    "MP_MAX = 29,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESimpleElementBlendMode = {"
    "SE_BLEND_Opaque = 0,"
    "SE_BLEND_Masked = 1,"
    "SE_BLEND_Translucent = 2,"
    "SE_BLEND_Additive = 3,"
    "SE_BLEND_Modulate = 4,"
    "SE_BLEND_MaskedDistanceField = 5,"
    "SE_BLEND_MaskedDistanceFieldShadowed = 6,"
    "SE_BLEND_TranslucentDistanceField = 7,"
    "SE_BLEND_TranslucentDistanceFieldShadowed = 8,"
    "SE_BLEND_AlphaComposite = 9,"
    "SE_BLEND_AlphaBlend = 10,"
    "SE_BLEND_TranslucentAlphaOnly = 11,"
    "SE_BLEND_TranslucentAlphaOnlyWriteAlpha = 12,"
    "SE_BLEND_RGBA_MASK_START = 13,"
    "SE_BLEND_RGBA_MASK_END = 44,"
    "SE_BLEND_MAX = 45,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPixelFormat = {"
    "PF_Unknown = 0,"
    "PF_A32B32G32R32F = 1,"
    "PF_B8G8R8A8 = 2,"
    "PF_G8 = 3,"
    "PF_G16 = 4,"
    "PF_DXT1 = 5,"
    "PF_DXT3 = 6,"
    "PF_DXT5 = 7,"
    "PF_UYVY = 8,"
    "PF_FloatRGB = 9,"
    "PF_FloatRGBA = 10,"
    "PF_DepthStencil = 11,"
    "PF_ShadowDepth = 12,"
    "PF_R32_FLOAT = 13,"
    "PF_G16R16 = 14,"
    "PF_G16R16F = 15,"
    "PF_G16R16F_FILTER = 16,"
    "PF_G32R32F = 17,"
    "PF_A2B10G10R10 = 18,"
    "PF_A16B16G16R16 = 19,"
    "PF_D24 = 20,"
    "PF_R16F = 21,"
    "PF_R16F_FILTER = 22,"
    "PF_BC5 = 23,"
    "PF_V8U8 = 24,"
    "PF_A1 = 25,"
    "PF_FloatR11G11B10 = 26,"
    "PF_A8 = 27,"
    "PF_R32_UINT = 28,"
    "PF_R32_SINT = 29,"
    "PF_PVRTC2 = 30,"
    "PF_PVRTC4 = 31,"
    "PF_R16_UINT = 32,"
    "PF_R16_SINT = 33,"
    "PF_R16G16B16A16_UINT = 34,"
    "PF_R16G16B16A16_SINT = 35,"
    "PF_R5G6B5_UNORM = 36,"
    "PF_R8G8B8A8 = 37,"
    "PF_A8R8G8B8 = 38,"
    "PF_BC4 = 39,"
    "PF_R8G8 = 40,"
    "PF_ATC_RGB = 41,"
    "PF_ATC_RGBA_E = 42,"
    "PF_ATC_RGBA_I = 43,"
    "PF_X24_G8 = 44,"
    "PF_ETC1 = 45,"
    "PF_ETC2_RGB = 46,"
    "PF_ETC2_RGBA = 47,"
    "PF_R32G32B32A32_UINT = 48,"
    "PF_R16G16_UINT = 49,"
    "PF_ASTC_4x4 = 50,"
    "PF_ASTC_6x6 = 51,"
    "PF_ASTC_8x8 = 52,"
    "PF_ASTC_10x10 = 53,"
    "PF_ASTC_12x12 = 54,"
    "PF_BC6H = 55,"
    "PF_BC7 = 56,"
    "PF_R8_UINT = 57,"
    "PF_L8 = 58,"
    "PF_XGXR8 = 59,"
    "PF_R8G8B8A8_UINT = 60,"
    "PF_R8G8B8A8_SNORM = 61,"
    "PF_MAX = 62,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShaderFrequency = {"
    "SF_Vertex = 0,"
    "SF_Hull = 1,"
    "SF_Domain = 2,"
    "SF_Pixel = 3,"
    "SF_Geometry = 4,"
    "SF_Compute = 5,"
    "SF_NumFrequencies = 6,"
    "SF_NumBits = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShaderPlatform = {"
    "SP_PCD3D_SM5 = 0,"
    "SP_OPENGL_SM4 = 1,"
    "SP_PS4 = 2,"
    "SP_OPENGL_PCES2 = 3,"
    "SP_XBOXONE_D3D12 = 4,"
    "SP_PCD3D_SM4 = 5,"
    "SP_OPENGL_SM5 = 6,"
    "SP_PCD3D_ES2 = 7,"
    "SP_OPENGL_ES2_ANDROID = 8,"
    "SP_OPENGL_ES2_WEBGL = 9,"
    "SP_OPENGL_ES2_IOS = 10,"
    "SP_METAL = 11,"
    "SP_METAL_MRT = 12,"
    "SP_OPENGL_ES31_EXT = 13,"
    "SP_PCD3D_ES3_1 = 14,"
    "SP_OPENGL_PCES3_1 = 15,"
    "SP_METAL_SM5 = 16,"
    "SP_VULKAN_PCES3_1 = 17,"
    "SP_METAL_SM4 = 18,"
    "SP_VULKAN_SM4 = 19,"
    "SP_VULKAN_SM5 = 20,"
    "SP_VULKAN_ES3_1_ANDROID = 21,"
    "SP_METAL_MACES3_1 = 22,"
    "SP_METAL_MACES2 = 23,"
    "SP_OPENGL_ES3_1_ANDROID = 24,"
    "SP_SWITCH = 25,"
    "SP_SWITCH_FORWARD = 26,"
    "SP_METAL_MRT_MAC = 27,"
    "SP_NumPlatforms = 28,"
    "SP_NumBits = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERenderQueryType = {"
    "RQT_Undefined = 0,"
    "RQT_Occlusion = 1,"
    "RQT_AbsoluteTime = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERHIZBuffer = {"
    "FarPlane = 0,"
    "NearPlane = 1,"
    "IsInverted = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESamplerFilter = {"
    "SF_Point = 0,"
    "SF_Bilinear = 1,"
    "SF_Trilinear = 2,"
    "SF_AnisotropicPoint = 3,"
    "SF_AnisotropicLinear = 4,"
    "ESamplerFilter_Num = 5,"
    "ESamplerFilter_NumBits = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESamplerAddressMode = {"
    "AM_Wrap = 0,"
    "AM_Clamp = 1,"
    "AM_Mirror = 2,"
    "AM_Border = 3,"
    "ESamplerAddressMode_Num = 4,"
    "ESamplerAddressMode_NumBits = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESamplerCompareFunction = {"
    "SCF_Never = 0,"
    "SCF_Less = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERasterizerFillMode = {"
    "FM_Point = 0,"
    "FM_Wireframe = 1,"
    "FM_Solid = 2,"
    "ERasterizerFillMode_Num = 3,"
    "ERasterizerFillMode_NumBits = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERasterizerCullMode = {"
    "CM_None = 0,"
    "CM_CW = 1,"
    "CM_CCW = 2,"
    "ERasterizerCullMode_Num = 3,"
    "ERasterizerCullMode_NumBits = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EColorWriteMask = {"
    "CW_RED = 1,"
    "CW_GREEN = 2,"
    "CW_BLUE = 4,"
    "CW_ALPHA = 8,"
    "CW_NONE = 0,"
    "CW_RGB = 7,"
    "CW_RGBA = 15,"
    "CW_RG = 3,"
    "CW_BA = 12,"
    "EColorWriteMask_NumBits = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECompareFunction = {"
    "CF_Less = 0,"
    "CF_LessEqual = 1,"
    "CF_Greater = 2,"
    "CF_GreaterEqual = 3,"
    "CF_Equal = 4,"
    "CF_NotEqual = 5,"
    "CF_Never = 6,"
    "CF_Always = 7,"
    "ECompareFunction_Num = 8,"
    "ECompareFunction_NumBits = 3,"
    "CF_DepthNearOrEqual = 3,"
    "CF_DepthNear = 2,"
    "CF_DepthFartherOrEqual = 1,"
    "CF_DepthFarther = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStencilMask = {"
    "SM_Default = 0,"
    "SM_255 = 1,"
    "SM_1 = 2,"
    "SM_2 = 3,"
    "SM_4 = 4,"
    "SM_8 = 5,"
    "SM_16 = 6,"
    "SM_32 = 7,"
    "SM_64 = 8,"
    "SM_128 = 9,"
    "SM_Count = 10,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStencilOp = {"
    "SO_Keep = 0,"
    "SO_Zero = 1,"
    "SO_Replace = 2,"
    "SO_SaturatedIncrement = 3,"
    "SO_SaturatedDecrement = 4,"
    "SO_Invert = 5,"
    "SO_Increment = 6,"
    "SO_Decrement = 7,"
    "EStencilOp_Num = 8,"
    "EStencilOp_NumBits = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlendOperation = {"
    "BO_Add = 0,"
    "BO_Subtract = 1,"
    "BO_Min = 2,"
    "BO_Max = 3,"
    "BO_ReverseSubtract = 4,"
    "EBlendOperation_Num = 5,"
    "EBlendOperation_NumBits = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlendFactor = {"
    "BF_Zero = 0,"
    "BF_One = 1,"
    "BF_SourceColor = 2,"
    "BF_InverseSourceColor = 3,"
    "BF_SourceAlpha = 4,"
    "BF_InverseSourceAlpha = 5,"
    "BF_DestAlpha = 6,"
    "BF_InverseDestAlpha = 7,"
    "BF_DestColor = 8,"
    "BF_InverseDestColor = 9,"
    "BF_ConstantBlendFactor = 10,"
    "BF_InverseConstantBlendFactor = 11,"
    "EBlendFactor_Num = 12,"
    "EBlendFactor_NumBits = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVertexElementType = {"
    "VET_None = 0,"
    "VET_Float1 = 1,"
    "VET_Float2 = 2,"
    "VET_Float3 = 3,"
    "VET_Float4 = 4,"
    "VET_PackedNormal = 5,"
    "VET_UByte4 = 6,"
    "VET_UByte4N = 7,"
    "VET_Color = 8,"
    "VET_Short2 = 9,"
    "VET_Short4 = 10,"
    "VET_Short2N = 11,"
    "VET_Half2 = 12,"
    "VET_Half4 = 13,"
    "VET_Short4N = 14,"
    "VET_UShort2 = 15,"
    "VET_UShort4 = 16,"
    "VET_UShort2N = 17,"
    "VET_UShort4N = 18,"
    "VET_URGB10A2N = 19,"
    "VET_MAX = 20,"
    "VET_NumBits = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECubeFace = {"
    "CubeFace_PosX = 0,"
    "CubeFace_NegX = 1,"
    "CubeFace_PosY = 2,"
    "CubeFace_NegY = 3,"
    "CubeFace_PosZ = 4,"
    "CubeFace_NegZ = 5,"
    "CubeFace_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUniformBufferUsage = {"
    "UniformBuffer_SingleDraw = 0,"
    "UniformBuffer_SingleFrame = 1,"
    "UniformBuffer_MultiFrame = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUniformBufferBaseType = {"
    "UBMT_INVALID = 0,"
    "UBMT_BOOL = 1,"
    "UBMT_INT32 = 2,"
    "UBMT_UINT32 = 3,"
    "UBMT_FLOAT32 = 4,"
    "UBMT_STRUCT = 5,"
    "UBMT_SRV = 6,"
    "UBMT_UAV = 7,"
    "UBMT_SAMPLER = 8,"
    "UBMT_TEXTURE = 9,"
    "EUniformBufferBaseType_Num = 10,"
    "EUniformBufferBaseType_NumBits = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EResourceTableDefinitions = {"
    "RTD_NumBits_UniformBufferIndex = 8,"
    "RTD_NumBits_ResourceIndex = 16,"
    "RTD_NumBits_BindIndex = 8,"
    "RTD_Mask_UniformBufferIndex = 255,"
    "RTD_Mask_ResourceIndex = 65535,"
    "RTD_Mask_BindIndex = 255,"
    "RTD_Shift_BindIndex = 0,"
    "RTD_Shift_ResourceIndex = 8,"
    "RTD_Shift_UniformBufferIndex = 24,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EResourceLockMode = {"
    "RLM_ReadOnly = 0,"
    "RLM_WriteOnly = 1,"
    "RLM_Num = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERangeCompressionMode = {"
    "RCM_UNorm = 0,"
    "RCM_SNorm = 1,"
    "RCM_MinMaxNorm = 2,"
    "RCM_MinMax = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPrimitiveTopologyType = {"
    "Triangle = 0,"
    "Patch = 1,"
    "Line = 2,"
    "Point = 3,"
    "Num = 4,"
    "NumBits = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPrimitiveType = {"
    "PT_TriangleList = 0,"
    "PT_TriangleStrip = 1,"
    "PT_LineList = 2,"
    "PT_QuadList = 3,"
    "PT_PointList = 4,"
    "PT_1_ControlPointPatchList = 5,"
    "PT_2_ControlPointPatchList = 6,"
    "PT_3_ControlPointPatchList = 7,"
    "PT_4_ControlPointPatchList = 8,"
    "PT_5_ControlPointPatchList = 9,"
    "PT_6_ControlPointPatchList = 10,"
    "PT_7_ControlPointPatchList = 11,"
    "PT_8_ControlPointPatchList = 12,"
    "PT_9_ControlPointPatchList = 13,"
    "PT_10_ControlPointPatchList = 14,"
    "PT_11_ControlPointPatchList = 15,"
    "PT_12_ControlPointPatchList = 16,"
    "PT_13_ControlPointPatchList = 17,"
    "PT_14_ControlPointPatchList = 18,"
    "PT_15_ControlPointPatchList = 19,"
    "PT_16_ControlPointPatchList = 20,"
    "PT_17_ControlPointPatchList = 21,"
    "PT_18_ControlPointPatchList = 22,"
    "PT_19_ControlPointPatchList = 23,"
    "PT_20_ControlPointPatchList = 24,"
    "PT_21_ControlPointPatchList = 25,"
    "PT_22_ControlPointPatchList = 26,"
    "PT_23_ControlPointPatchList = 27,"
    "PT_24_ControlPointPatchList = 28,"
    "PT_25_ControlPointPatchList = 29,"
    "PT_26_ControlPointPatchList = 30,"
    "PT_27_ControlPointPatchList = 31,"
    "PT_28_ControlPointPatchList = 32,"
    "PT_29_ControlPointPatchList = 33,"
    "PT_30_ControlPointPatchList = 34,"
    "PT_31_ControlPointPatchList = 35,"
    "PT_32_ControlPointPatchList = 36,"
    "PT_Num = 37,"
    "PT_NumBits = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBufferUsageFlags = {"
    "BUF_None = 0,"
    "BUF_Static = 1,"
    "BUF_Dynamic = 2,"
    "BUF_Volatile = 4,"
    "BUF_UnorderedAccess = 8,"
    "BUF_ByteAddressBuffer = 32,"
    "BUF_UAVCounter = 64,"
    "BUF_StreamOutput = 128,"
    "BUF_DrawIndirect = 256,"
    "BUF_ShaderResource = 512,"
    "BUF_KeepCPUAccessible = 1024,"
    "BUF_ZeroStride = 2048,"
    "BUF_FastVRAM = 4096,"
    "BUF_Transient = 8192,"
    "BUF_UINT8 = 16384,"
    "BUF_AnyDynamic = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERHIResourceType = {"
    "RRT_None = 0,"
    "RRT_SamplerState = 1,"
    "RRT_RasterizerState = 2,"
    "RRT_DepthStencilState = 3,"
    "RRT_BlendState = 4,"
    "RRT_VertexDeclaration = 5,"
    "RRT_VertexShader = 6,"
    "RRT_HullShader = 7,"
    "RRT_DomainShader = 8,"
    "RRT_PixelShader = 9,"
    "RRT_GeometryShader = 10,"
    "RRT_ComputeShader = 11,"
    "RRT_BoundShaderState = 12,"
    "RRT_UniformBuffer = 13,"
    "RRT_IndexBuffer = 14,"
    "RRT_VertexBuffer = 15,"
    "RRT_StructuredBuffer = 16,"
    "RRT_Texture = 17,"
    "RRT_Texture2D = 18,"
    "RRT_Texture2DArray = 19,"
    "RRT_Texture3D = 20,"
    "RRT_TextureCube = 21,"
    "RRT_TextureReference = 22,"
    "RRT_RenderQuery = 23,"
    "RRT_Viewport = 24,"
    "RRT_UnorderedAccessView = 25,"
    "RRT_ShaderResourceView = 26,"
    "RRT_Num = 27,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureCreateFlags = {"
    "TexCreate_None = 0,"
    "TexCreate_RenderTargetable = 1,"
    "TexCreate_ResolveTargetable = 2,"
    "TexCreate_DepthStencilTargetable = 4,"
    "TexCreate_ShaderResource = 8,"
    "TexCreate_SRGB = 16,"
    "TexCreate_NoMipTail = 32,"
    "TexCreate_NoTiling = 64,"
    "TexCreate_Dynamic = 256,"
    "TexCreate_AllowFailure = 512,"
    "TexCreate_DisableAutoDefrag = 1024,"
    "TexCreate_Memoryless = 2048,"
    "TexCreate_GenerateMipCapable = 4096,"
    "TexCreate_UAV = 65536,"
    "TexCreate_Presentable = 131072,"
    "TexCreate_CPUReadback = 262144,"
    "TexCreate_OfflineProcessed = 524288,"
    "TexCreate_FastVRAM = 1048576,"
    "TexCreate_HideInVisualizeTexture = 2097152,"
    "TexCreate_Virtual = 4194304,"
    "TexCreate_TargetArraySlicesIndependently = 8388608,"
    "TexCreate_Shared = 16777216,"
    "TexCreate_NoFastClear = 33554432,"
    "TexCreate_DepthStencilResolveTarget = 67108864,"
    "TexCreate_Streamable = 134217728,"
    "TexCreate_NoFastClearFinalize = 268435456,"
    "TexCreate_AFRManual = 536870912,"
    "TexCreate_ReduceMemoryWithTilingMode = 1073741824,"
    "TexCreate_Transient = -2147483648,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAsyncComputePriority = {"
    "AsyncComputePriority_Default = 0,"
    "AsyncComputePriority_High = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureReallocationStatus = {"
    "TexRealloc_Succeeded = 0,"
    "TexRealloc_Failed = 1,"
    "TexRealloc_InProgress = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERenderTargetLoadAction = {"
    "ENoAction = 0,"
    "ELoad = 1,"
    "EClear = 2,"
    "Num = 3,"
    "NumBits = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERenderTargetStoreAction = {"
    "ENoAction = 0,"
    "EStore = 1,"
    "EMultisampleResolve = 2,"
    "Num = 3,"
    "NumBits = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESimpleRenderTargetMode = {"
    "EExistingColorAndDepth = 0,"
    "EUninitializedColorAndDepth = 1,"
    "EUninitializedColorExistingDepth = 2,"
    "EUninitializedColorClearDepth = 3,"
    "EClearColorExistingDepth = 4,"
    "EClearColorAndDepth = 5,"
    "EExistingContents_NoDepthStore = 6,"
    "EExistingColorAndClearDepth = 7,"
    "EExistingColorAndDepthAndClearStencil = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EClearDepthStencil = {"
    "Depth = 0,"
    "Stencil = 1,"
    "DepthStencil = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAsyncComputeBudget = {"
    "ELeast_0 = 0,"
    "EGfxHeavy_1 = 1,"
    "EBalanced_2 = 2,"
    "EComputeHeavy_3 = 3,"
    "EAll_4 = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EClearBinding = {"
    "ENoneBound = 0,"
    "EColorBound = 1,"
    "EDepthStencilBound = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EResourceTransitionAccess = {"
    "EReadable = 0,"
    "EWritable = 1,"
    "ERWBarrier = 2,"
    "ERWNoBarrier = 3,"
    "ERWSubResBarrier = 4,"
    "EMetaData = 5,"
    "EMaxAccess = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EResourceAliasability = {"
    "EAliasable = 0,"
    "EUnaliasable = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EResourceTransitionPipeline = {"
    "EGfxToCompute = 0,"
    "EComputeToGfx = 1,"
    "EGfxToGfx = 2,"
    "EComputeToCompute = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInit = {"
    "Zero = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERenderTargetActions = {"
    "LoadOpMask = 2,"
    "DontLoad_DontStore = 0,"
    "DontLoad_Store = 1,"
    "Clear_Store = 9,"
    "Load_Store = 5,"
    "Clear_DontStore = 8,"
    "Load_DontStore = 4,"
    "Clear_Resolve = 10,"
    "Load_Resolve = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDepthStencilTargetActions = {"
    "DepthMask = 4,"
    "DontLoad_DontStore = 0,"
    "DontLoad_StoreDepthStencil = 17,"
    "ClearDepthStencil_StoreDepthStencil = -103,"
    "LoadDepthStencil_StoreDepthStencil = 85,"
    "LoadDepthNotStencil_DontStore = 64,"
    "LoadDepthStencil_StoreStencilNotDepth = 69,"
    "ClearDepthStencil_DontStoreDepthStencil = -120,"
    "LoadDepthStencil_DontStoreDepthStencil = 68,"
    "ClearDepthStencil_StoreDepthNotStencil = -104,"
    "ClearDepthStencil_StoreStencilNotDepth = -119,"
    "ClearDepthStencil_ResolveDepthNotStencil = -88,"
    "ClearDepthStencil_ResolveStencilNotDepth = -118,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELLMTracker = {"
    "Platform = 0,"
    "Default = 1,"
    "Max = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELLMTagSet = {"
    "None = 0,"
    "Assets = 1,"
    "AssetClasses = 2,"
    "Max = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELLMTag = {"
    "Untagged = 0,"
    "Paused = 1,"
    "TrackedTotal = 2,"
    "UntrackedTotal = 3,"
    "PlatformTrackedTotal = 4,"
    "PlatformUntrackedTotal = 5,"
    "SmallBinnedAllocation = 6,"
    "LargeBinnedAllocation = 7,"
    "ThreadStack = 8,"
    "ProgramSizePlatform = 9,"
    "ProgramSize = 10,"
    "BackupOOMMemoryPoolPlatform = 11,"
    "BackupOOMMemoryPool = 12,"
    "GenericPlatformMallocCrash = 13,"
    "GenericPlatformMallocCrashPlatform = 14,"
    "EngineMisc = 15,"
    "TaskGraphTasksMisc = 16,"
    "Audio = 17,"
    "FName = 18,"
    "Networking = 19,"
    "Meshes = 20,"
    "Stats = 21,"
    "Shaders = 22,"
    "Textures = 23,"
    "RenderTargets = 24,"
    "RHIMisc = 25,"
    "PhysXTriMesh = 26,"
    "PhysXConvexMesh = 27,"
    "AsyncLoading = 28,"
    "UObject = 29,"
    "Animation = 30,"
    "StaticMesh = 31,"
    "Materials = 32,"
    "Particles = 33,"
    "GC = 34,"
    "UI = 35,"
    "PhysX = 36,"
    "EnginePreInitMemory = 37,"
    "EngineInitMemory = 38,"
    "RenderingThreadMemory = 39,"
    "LoadMapMisc = 40,"
    "StreamingManager = 41,"
    "GraphicsPlatform = 42,"
    "FileSystem = 43,"
    "GenericTagCount = 44,"
    "PlatformTagStart = 100,"
    "PlatformRHITagStart = -56,"
    "PlatformTagEnd = -1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECmdList = {"
    "EGfx = 0,"
    "ECompute = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERenderThreadContext = {"
    "SceneRenderTargets = 0,"
    "Num = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECmdListType = {"
    "Immediate = 1,"
    "RenderSubPass = 2,"
    "Regular = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMipFadeSettings = {"
    "MipFade_Normal = 0,"
    "MipFade_Slow = 1,"
    "MipFade_NumSettings = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInputEvent = {"
    "IE_Pressed = 0,"
    "IE_Released = 1,"
    "IE_Repeat = 2,"
    "IE_DoubleClick = 3,"
    "IE_Axis = 4,"
    "IE_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMouseCaptureMode = {"
    "NoCapture = 0,"
    "CapturePermanently = 1,"
    "CapturePermanently_IncludingInitialMouseDown = 2,"
    "CaptureDuringMouseDown = 3,"
    "CaptureDuringRightMouseDown = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMouseLockMode = {"
    "DoNotLock = 0,"
    "LockOnCapture = 1,"
    "LockAlways = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELevelTick = {"
    "LEVELTICK_TimeOnly = 0,"
    "LEVELTICK_ViewportsOnly = 1,"
    "LEVELTICK_All = 2,"
    "LEVELTICK_PauseTick = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETickingGroup = {"
    "TG_PrePhysics = 0,"
    "TG_StartPhysics = 1,"
    "TG_DuringPhysics = 2,"
    "TG_EndPhysics = 3,"
    "TG_PostPhysics = 4,"
    "TG_PostUpdateWork = 5,"
    "TG_LastDemotable = 6,"
    "TG_NewlySpawned = 7,"
    "TG_MAX = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETickState = {"
    "Disabled = 0,"
    "Enabled = 1,"
    "CoolingDown = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETravelType = {"
    "TRAVEL_Absolute = 0,"
    "TRAVEL_Partial = 1,"
    "TRAVEL_Relative = 2,"
    "TRAVEL_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENetMode = {"
    "NM_Standalone = 0,"
    "NM_DedicatedServer = 1,"
    "NM_ListenServer = 2,"
    "NM_Client = 3,"
    "NM_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EViewModeIndex = {"
    "VMI_BrushWireframe = 0,"
    "VMI_Wireframe = 1,"
    "VMI_Unlit = 2,"
    "VMI_Lit = 3,"
    "VMI_Lit_DetailLighting = 4,"
    "VMI_LightingOnly = 5,"
    "VMI_LightComplexity = 6,"
    "VMI_ShaderComplexity = 8,"
    "VMI_LightmapDensity = 9,"
    "VMI_LitLightmapDensity = 10,"
    "VMI_ReflectionOverride = 11,"
    "VMI_VisualizeBuffer = 12,"
    "VMI_StationaryLightOverlap = 14,"
    "VMI_CollisionPawn = 15,"
    "VMI_CollisionVisibility = 16,"
    "VMI_LODColoration = 18,"
    "VMI_QuadOverdraw = 19,"
    "VMI_PrimitiveDistanceAccuracy = 20,"
    "VMI_MeshUVDensityAccuracy = 21,"
    "VMI_ShaderComplexityWithQuadOverdraw = 22,"
    "VMI_HLODColoration = 23,"
    "VMI_GroupLODColoration = 24,"
    "VMI_MaterialTextureScaleAccuracy = 25,"
    "VMI_RequiredTextureResolution = 26,"
    "VMI_Max = 27,"
    "VMI_Unknown = 255,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShowFlagGroup = {"
    "SFG_Normal = 0,"
    "SFG_Advanced = 1,"
    "SFG_PostProcess = 2,"
    "SFG_CollisionModes = 3,"
    "SFG_Developer = 4,"
    "SFG_Visualize = 5,"
    "SFG_LightTypes = 6,"
    "SFG_LightingComponents = 7,"
    "SFG_LightingFeatures = 8,"
    "SFG_Hidden = 9,"
    "SFG_Max = 10,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShowFlagInitMode = {"
    "ESFIM_Game = 0,"
    "ESFIM_Editor = 1,"
    "ESFIM_All0 = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShowFlag = {"
    "SF_PostProcessing = 0,"
    "SF_Bloom = 1,"
    "SF_Tonemapper = 2,"
    "SF_AntiAliasing = 3,"
    "SF_TemporalAA = 4,"
    "SF_AmbientCubemap = 5,"
    "SF_EyeAdaptation = 6,"
    "SF_VisualizeHDR = 7,"
    "SF_LensFlares = 8,"
    "SF_GlobalIllumination = 9,"
    "SF_Vignette = 10,"
    "SF_Grain = 11,"
    "SF_AmbientOcclusion = 12,"
    "SF_Decals = 13,"
    "SF_CameraImperfections = 14,"
    "SF_OnScreenDebug = 15,"
    "SF_OverrideDiffuseAndSpecular = 16,"
    "SF_ReflectionOverride = 17,"
    "SF_VisualizeBuffer = 18,"
    "SF_DirectLighting = 19,"
    "SF_DirectionalLights = 20,"
    "SF_PointLights = 21,"
    "SF_SpotLights = 22,"
    "SF_ColorGrading = 23,"
    "SF_VectorFields = 24,"
    "SF_DepthOfField = 25,"
    "SF_GBufferHints = 26,"
    "SF_MotionBlur = 27,"
    "SF_CompositeEditorPrimitives = 28,"
    "SF_TestImage = 29,"
    "SF_VisualizeDOF = 30,"
    "SF_VisualizeAdaptiveDOF = 31,"
    "SF_VertexColors = 32,"
    "SF_Refraction = 33,"
    "SF_CameraInterpolation = 34,"
    "SF_SceneColorFringe = 35,"
    "SF_SeparateTranslucency = 36,"
    "SF_ScreenPercentage = 37,"
    "SF_VisualizeMotionBlur = 38,"
    "SF_ReflectionEnvironment = 39,"
    "SF_VisualizeOutOfBoundsPixels = 40,"
    "SF_Diffuse = 41,"
    "SF_Specular = 42,"
    "SF_SelectionOutline = 43,"
    "SF_ScreenSpaceReflections = 44,"
    "SF_ContactShadows = 45,"
    "SF_SubsurfaceScattering = 46,"
    "SF_VisualizeSSS = 47,"
    "SF_VolumetricLightmap = 48,"
    "SF_IndirectLightingCache = 49,"
    "SF_DebugAI = 50,"
    "SF_VisLog = 51,"
    "SF_Navigation = 52,"
    "SF_GameplayDebug = 53,"
    "SF_TexturedLightProfiles = 54,"
    "SF_LightFunctions = 55,"
    "SF_Tessellation = 56,"
    "SF_InstancedStaticMeshes = 57,"
    "SF_InstancedFoliage = 58,"
    "SF_FoliageOcclusionBounds = 59,"
    "SF_InstancedGrass = 60,"
    "SF_DynamicShadows = 61,"
    "SF_Particles = 62,"
    "SF_SkeletalMeshes = 63,"
    "SF_BuilderBrush = 64,"
    "SF_Translucency = 65,"
    "SF_BillboardSprites = 66,"
    "SF_LOD = 67,"
    "SF_LightComplexity = 68,"
    "SF_ShaderComplexity = 69,"
    "SF_StationaryLightOverlap = 70,"
    "SF_LightMapDensity = 71,"
    "SF_StreamingBounds = 72,"
    "SF_Constraints = 73,"
    "SF_MassProperties = 74,"
    "SF_CameraFrustums = 75,"
    "SF_AudioRadius = 76,"
    "SF_ForceFeedbackRadius = 77,"
    "SF_BSPSplit = 78,"
    "SF_Brushes = 79,"
    "SF_Lighting = 80,"
    "SF_DeferredLighting = 81,"
    "SF_Editor = 82,"
    "SF_BSPTriangles = 83,"
    "SF_LargeVertices = 84,"
    "SF_Grid = 85,"
    "SF_Snap = 86,"
    "SF_MeshEdges = 87,"
    "SF_Cover = 88,"
    "SF_Splines = 89,"
    "SF_Selection = 90,"
    "SF_ModeWidgets = 91,"
    "SF_Bounds = 92,"
    "SF_HitProxies = 93,"
    "SF_PropertyColoration = 94,"
    "SF_LightInfluences = 95,"
    "SF_Pivot = 96,"
    "SF_ShadowFrustums = 97,"
    "SF_Wireframe = 98,"
    "SF_Materials = 99,"
    "SF_StaticMeshes = 100,"
    "SF_Landscape = 101,"
    "SF_LightRadius = 102,"
    "SF_Fog = 103,"
    "SF_Volumes = 104,"
    "SF_Game = 105,"
    "SF_LevelColoration = 106,"
    "SF_BSP = 107,"
    "SF_Collision = 108,"
    "SF_CollisionVisibility = 109,"
    "SF_CollisionPawn = 110,"
    "SF_LightShafts = 111,"
    "SF_PostProcessMaterial = 112,"
    "SF_AtmosphericFog = 113,"
    "SF_CameraAspectRatioBars = 114,"
    "SF_CameraSafeFrames = 115,"
    "SF_TextRender = 116,"
    "SF_Rendering = 117,"
    "SF_HighResScreenshotMask = 118,"
    "SF_HMDDistortion = 119,"
    "SF_StereoRendering = 120,"
    "SF_DistanceCulledPrimitives = 121,"
    "SF_VisualizeLightCulling = 122,"
    "SF_PrecomputedVisibility = 123,"
    "SF_SkyLighting = 124,"
    "SF_VisualizeLPV = 125,"
    "SF_PreviewShadowsIndicator = 126,"
    "SF_PrecomputedVisibilityCells = 127,"
    "SF_VisualizeVolumetricLightmap = 128,"
    "SF_VolumeLightingSamples = 129,"
    "SF_Paper2DSprites = 130,"
    "SF_VisualizeDistanceFieldAO = 131,"
    "SF_VisualizeDistanceFieldGI = 132,"
    "SF_VisualizeMeshDistanceFields = 133,"
    "SF_VisualizeGlobalDistanceField = 134,"
    "SF_ScreenSpaceAO = 135,"
    "SF_DistanceFieldAO = 136,"
    "SF_DistanceFieldGI = 137,"
    "SF_VolumetricFog = 138,"
    "SF_VisualizeSSR = 139,"
    "SF_VisualizeShadingModels = 140,"
    "SF_VisualizeSenses = 141,"
    "SF_VisualizeBloom = 142,"
    "SF_LODColoration = 143,"
    "SF_HLODColoration = 144,"
    "SF_QuadOverdraw = 145,"
    "SF_ShaderComplexityWithQuadOverdraw = 146,"
    "SF_PrimitiveDistanceAccuracy = 147,"
    "SF_MeshUVDensityAccuracy = 148,"
    "SF_MaterialTextureScaleAccuracy = 149,"
    "SF_OutputMaterialTextureScales = 150,"
    "SF_RequiredTextureResolution = 151,"
    "SF_WidgetComponents = 152,"
    "SF_Bones = 153,"
    "SF_MediaPlanes = 154,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EHitProxyPriority = {"
    "HPP_World = 0,"
    "HPP_Wireframe = 1,"
    "HPP_Foreground = 2,"
    "HPP_UI = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPopupMethod = {"
    "CreateNewWindow = 0,"
    "UseCurrentWindow = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShouldThrottle = {"
    "No = 0,"
    "Yes = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.Private = {"
    "VISPRIVATE_Visible = 1,"
    "VISPRIVATE_Collapsed = 2,"
    "VISPRIVATE_Hidden = 4,"
    "VISPRIVATE_SelfHitTestVisible = 8,"
    "VISPRIVATE_ChildrenHitTestVisible = 16,"
    "VIS_Visible = 25,"
    "VIS_Collapsed = 2,"
    "VIS_Hidden = 4,"
    "VIS_HitTestInvisible = 1,"
    "VIS_SelfHitTestInvisible = 17,"
    "VIS_All = 31,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUINavigation = {"
    "Left = 0,"
    "Right = 1,"
    "Up = 2,"
    "Down = 3,"
    "Next = 4,"
    "Previous = 5,"
    "Num = 6,"
    "Invalid = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENavigationSource = {"
    "FocusedWidget = 0,"
    "WidgetUnderCursor = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENavigationGenesis = {"
    "Keyboard = 0,"
    "Controller = 1,"
    "User = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EHorizontalAlignment = {"
    "HAlign_Fill = 0,"
    "HAlign_Left = 1,"
    "HAlign_Center = 2,"
    "HAlign_Right = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVerticalAlignment = {"
    "VAlign_Fill = 0,"
    "VAlign_Top = 1,"
    "VAlign_Center = 2,"
    "VAlign_Bottom = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMenuPlacement = {"
    "MenuPlacement_BelowAnchor = 0,"
    "MenuPlacement_CenteredBelowAnchor = 1,"
    "MenuPlacement_BelowRightAnchor = 2,"
    "MenuPlacement_ComboBox = 3,"
    "MenuPlacement_ComboBoxRight = 4,"
    "MenuPlacement_MenuRight = 5,"
    "MenuPlacement_AboveAnchor = 6,"
    "MenuPlacement_CenteredAboveAnchor = 7,"
    "MenuPlacement_AboveRightAnchor = 8,"
    "MenuPlacement_MenuLeft = 9,"
    "MenuPlacement_Center = 10,"
    "MenuPlacement_RightLeftCenter = 11,"
    "MenuPlacement_MatchBottomLeft = 12,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOrientation = {"
    "Orient_Horizontal = 0,"
    "Orient_Vertical = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EScrollDirection = {"
    "Scroll_Down = 0,"
    "Scroll_Up = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EActiveTimerReturnType = {"
    "Stop = 0,"
    "Continue = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWindowActivation = {"
    "Activate = 0,"
    "ActivateByMouse = 1,"
    "Deactivate = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGestureEvent = {"
    "None = 0,"
    "Scroll = 1,"
    "Magnify = 2,"
    "Swipe = 3,"
    "Rotate = 4,"
    "LongPress = 5,"
    "Count = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWindowType = {"
    "Normal = 0,"
    "Menu = 1,"
    "ToolTip = 2,"
    "Notification = 3,"
    "CursorDecorator = 4,"
    "GameWindow = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWindowTransparency = {"
    "None = 0,"
    "PerWindow = 1,"
    "PerPixel = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWindowActivationPolicy = {"
    "Never = 0,"
    "Always = 1,"
    "FirstShown = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFocusCause = {"
    "Mouse = 0,"
    "Navigation = 1,"
    "SetDirectly = 2,"
    "Cleared = 3,"
    "OtherWidgetLostFocus = 4,"
    "WindowActivate = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EActivationType = {"
    "EA_Activate = 0,"
    "EA_ActivateByMouse = 1,"
    "EA_Deactivate = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EExternalDragType = {"
    "DragText = 1,"
    "DragFiles = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUINavigationRule = {"
    "Escape = 0,"
    "Explicit = 1,"
    "Wrap = 2,"
    "Stop = 3,"
    "Custom = 4,"
    "Invalid = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateDrawEffect = {"
    "None = 0,"
    "NoBlending = 1,"
    "PreMultipliedAlpha = 2,"
    "NoGamma = 4,"
    "InvertAlpha = 8,"
    "NoPixelSnapping = 16,"
    "DisabledEffect = 32,"
    "IgnoreTextureAlpha = 64,"
    "ReverseGamma = -128,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateBatchDrawFlag = {"
    "None = 0,"
    "NoBlending = 1,"
    "PreMultipliedAlpha = 2,"
    "NoGamma = 4,"
    "InvertAlpha = 8,"
    "Wireframe = 16,"
    "TileU = 32,"
    "TileV = 64,"
    "ReverseGamma = -128,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateLineJoinType = {"
    "Sharp = 0,"
    "Simple = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateVertexRounding = {"
    "Disabled = 0,"
    "Enabled = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWidgetClipping = {"
    "Inherit = 0,"
    "ClipToBounds = 1,"
    "ClipToBoundsWithoutIntersecting = 2,"
    "ClipToBoundsAlways = 3,"
    "OnDemand = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EClippingMethod = {"
    "Scissor = 0,"
    "Stencil = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInvalidateWidget = {"
    "Layout = 0,"
    "LayoutAndVolatility = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAspectRatioAxisConstraint = {"
    "AspectRatio_MaintainYFOV = 0,"
    "AspectRatio_MaintainXFOV = 1,"
    "AspectRatio_MajorAxisFOV = 2,"
    "AspectRatio_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EActorMetricsType = {"
    "METRICS_VERTS = 0,"
    "METRICS_TRIS = 1,"
    "METRICS_SECTIONS = 2,"
    "METRICS_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAttachmentRule = {"
    "KeepRelative = 0,"
    "KeepWorld = 1,"
    "SnapToTarget = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDetachmentRule = {"
    "KeepRelative = 0,"
    "KeepWorld = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESceneDepthPriorityGroup = {"
    "SDPG_World = 0,"
    "SDPG_Foreground = 1,"
    "SDPG_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EIndirectLightingCacheQuality = {"
    "ILCQ_Off = 0,"
    "ILCQ_Point = 1,"
    "ILCQ_Volume = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOcclusionCombineMode = {"
    "OCM_Minimum = 0,"
    "OCM_Multiply = 1,"
    "OCM_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlendMode = {"
    "BLEND_Opaque = 0,"
    "BLEND_Masked = 1,"
    "BLEND_Translucent = 2,"
    "BLEND_Additive = 3,"
    "BLEND_Modulate = 4,"
    "BLEND_AlphaComposite = 5,"
    "BLEND_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESamplerSourceMode = {"
    "SSM_FromTextureAsset = 0,"
    "SSM_Wrap_WorldGroupSettings = 1,"
    "SSM_Clamp_WorldGroupSettings = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETranslucencyLightingMode = {"
    "TLM_VolumetricNonDirectional = 0,"
    "TLM_VolumetricDirectional = 1,"
    "TLM_VolumetricPerVertexNonDirectional = 2,"
    "TLM_VolumetricPerVertexDirectional = 3,"
    "TLM_Surface = 4,"
    "TLM_SurfacePerPixelLighting = 5,"
    "TLM_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERefractionMode = {"
    "RM_IndexOfRefraction = 0,"
    "RM_PixelNormalOffset = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESceneCaptureSource = {"
    "SCS_SceneColorHDR = 0,"
    "SCS_SceneColorHDRNoAlpha = 1,"
    "SCS_FinalColorLDR = 2,"
    "SCS_SceneColorSceneDepth = 3,"
    "SCS_SceneDepth = 4,"
    "SCS_DeviceDepth = 5,"
    "SCS_Normal = 6,"
    "SCS_BaseColor = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESceneCaptureCompositeMode = {"
    "SCCM_Overwrite = 0,"
    "SCCM_Additive = 1,"
    "SCCM_Composite = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETrailWidthMode = {"
    "ETrailWidthMode_FromCentre = 0,"
    "ETrailWidthMode_FromFirst = 1,"
    "ETrailWidthMode_FromSecond = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialShadingModel = {"
    "MSM_Unlit = 0,"
    "MSM_DefaultLit = 1,"
    "MSM_Subsurface = 2,"
    "MSM_PreintegratedSkin = 3,"
    "MSM_ClearCoat = 4,"
    "MSM_SubsurfaceProfile = 5,"
    "MSM_TwoSidedFoliage = 6,"
    "MSM_Hair = 7,"
    "MSM_Cloth = 8,"
    "MSM_Eye = 9,"
    "MSM_MAX = 10,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialTessellationMode = {"
    "MTM_NoTessellation = 0,"
    "MTM_FlatTessellation = 1,"
    "MTM_PNTriangles = 2,"
    "MTM_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialSamplerType = {"
    "SAMPLERTYPE_Color = 0,"
    "SAMPLERTYPE_Grayscale = 1,"
    "SAMPLERTYPE_Alpha = 2,"
    "SAMPLERTYPE_Normal = 3,"
    "SAMPLERTYPE_Masks = 4,"
    "SAMPLERTYPE_DistanceFieldFont = 5,"
    "SAMPLERTYPE_LinearColor = 6,"
    "SAMPLERTYPE_LinearGrayscale = 7,"
    "SAMPLERTYPE_External = 8,"
    "SAMPLERTYPE_MAX = 9,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELightingBuildQuality = {"
    "Quality_Preview = 0,"
    "Quality_Medium = 1,"
    "Quality_High = 2,"
    "Quality_Production = 3,"
    "Quality_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETriangleSortOption = {"
    "TRISORT_None = 0,"
    "TRISORT_CenterRadialDistance = 1,"
    "TRISORT_Random = 2,"
    "TRISORT_MergeContiguous = 3,"
    "TRISORT_Custom = 4,"
    "TRISORT_CustomLeftRight = 5,"
    "TRISORT_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETriangleSortAxis = {"
    "TSA_X_Axis = 0,"
    "TSA_Y_Axis = 1,"
    "TSA_Z_Axis = 2,"
    "TSA_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMovementMode = {"
    "MOVE_None = 0,"
    "MOVE_Walking = 1,"
    "MOVE_NavWalking = 2,"
    "MOVE_Falling = 3,"
    "MOVE_Swimming = 4,"
    "MOVE_Flying = 5,"
    "MOVE_Custom = 6,"
    "MOVE_MAX = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENetworkSmoothingMode = {"
    "Disabled = 0,"
    "Linear = 1,"
    "Exponential = 2,"
    "Replay = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECollisionChannel = {"
    "ECC_WorldStatic = 0,"
    "ECC_WorldDynamic = 1,"
    "ECC_Pawn = 2,"
    "ECC_Visibility = 3,"
    "ECC_Camera = 4,"
    "ECC_PhysicsBody = 5,"
    "ECC_Vehicle = 6,"
    "ECC_Destructible = 7,"
    "ECC_EngineTraceChannel1 = 8,"
    "ECC_EngineTraceChannel2 = 9,"
    "ECC_EngineTraceChannel3 = 10,"
    "ECC_EngineTraceChannel4 = 11,"
    "ECC_EngineTraceChannel5 = 12,"
    "ECC_EngineTraceChannel6 = 13,"
    "ECC_GameTraceChannel1 = 14,"
    "ECC_GameTraceChannel2 = 15,"
    "ECC_GameTraceChannel3 = 16,"
    "ECC_GameTraceChannel4 = 17,"
    "ECC_GameTraceChannel5 = 18,"
    "ECC_GameTraceChannel6 = 19,"
    "ECC_GameTraceChannel7 = 20,"
    "ECC_GameTraceChannel8 = 21,"
    "ECC_GameTraceChannel9 = 22,"
    "ECC_GameTraceChannel10 = 23,"
    "ECC_GameTraceChannel11 = 24,"
    "ECC_GameTraceChannel12 = 25,"
    "ECC_GameTraceChannel13 = 26,"
    "ECC_GameTraceChannel14 = 27,"
    "ECC_GameTraceChannel15 = 28,"
    "ECC_GameTraceChannel16 = 29,"
    "ECC_GameTraceChannel17 = 30,"
    "ECC_GameTraceChannel18 = 31,"
    "ECC_OverlapAll_Deprecated = 32,"
    "ECC_MAX = 33,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOverlapFilterOption = {"
    "OverlapFilter_All = 0,"
    "OverlapFilter_DynamicOnly = 1,"
    "OverlapFilter_StaticOnly = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EObjectTypeQuery = {"
    "ObjectTypeQuery1 = 0,"
    "ObjectTypeQuery2 = 1,"
    "ObjectTypeQuery3 = 2,"
    "ObjectTypeQuery4 = 3,"
    "ObjectTypeQuery5 = 4,"
    "ObjectTypeQuery6 = 5,"
    "ObjectTypeQuery7 = 6,"
    "ObjectTypeQuery8 = 7,"
    "ObjectTypeQuery9 = 8,"
    "ObjectTypeQuery10 = 9,"
    "ObjectTypeQuery11 = 10,"
    "ObjectTypeQuery12 = 11,"
    "ObjectTypeQuery13 = 12,"
    "ObjectTypeQuery14 = 13,"
    "ObjectTypeQuery15 = 14,"
    "ObjectTypeQuery16 = 15,"
    "ObjectTypeQuery17 = 16,"
    "ObjectTypeQuery18 = 17,"
    "ObjectTypeQuery19 = 18,"
    "ObjectTypeQuery20 = 19,"
    "ObjectTypeQuery21 = 20,"
    "ObjectTypeQuery22 = 21,"
    "ObjectTypeQuery23 = 22,"
    "ObjectTypeQuery24 = 23,"
    "ObjectTypeQuery25 = 24,"
    "ObjectTypeQuery26 = 25,"
    "ObjectTypeQuery27 = 26,"
    "ObjectTypeQuery28 = 27,"
    "ObjectTypeQuery29 = 28,"
    "ObjectTypeQuery30 = 29,"
    "ObjectTypeQuery31 = 30,"
    "ObjectTypeQuery32 = 31,"
    "ObjectTypeQuery_MAX = 32,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETraceTypeQuery = {"
    "TraceTypeQuery1 = 0,"
    "TraceTypeQuery2 = 1,"
    "TraceTypeQuery3 = 2,"
    "TraceTypeQuery4 = 3,"
    "TraceTypeQuery5 = 4,"
    "TraceTypeQuery6 = 5,"
    "TraceTypeQuery7 = 6,"
    "TraceTypeQuery8 = 7,"
    "TraceTypeQuery9 = 8,"
    "TraceTypeQuery10 = 9,"
    "TraceTypeQuery11 = 10,"
    "TraceTypeQuery12 = 11,"
    "TraceTypeQuery13 = 12,"
    "TraceTypeQuery14 = 13,"
    "TraceTypeQuery15 = 14,"
    "TraceTypeQuery16 = 15,"
    "TraceTypeQuery17 = 16,"
    "TraceTypeQuery18 = 17,"
    "TraceTypeQuery19 = 18,"
    "TraceTypeQuery20 = 19,"
    "TraceTypeQuery21 = 20,"
    "TraceTypeQuery22 = 21,"
    "TraceTypeQuery23 = 22,"
    "TraceTypeQuery24 = 23,"
    "TraceTypeQuery25 = 24,"
    "TraceTypeQuery26 = 25,"
    "TraceTypeQuery27 = 26,"
    "TraceTypeQuery28 = 27,"
    "TraceTypeQuery29 = 28,"
    "TraceTypeQuery30 = 29,"
    "TraceTypeQuery31 = 30,"
    "TraceTypeQuery32 = 31,"
    "TraceTypeQuery_MAX = 32,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPhysicsSceneType = {"
    "PST_Sync = 0,"
    "PST_Cloth = 1,"
    "PST_Async = 2,"
    "PST_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECollisionResponse = {"
    "ECR_Ignore = 0,"
    "ECR_Overlap = 1,"
    "ECR_Block = 2,"
    "ECR_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFilterInterpolationType = {"
    "BSIT_Average = 0,"
    "BSIT_Linear = 1,"
    "BSIT_Cubic = 2,"
    "BSIT_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInputConsumeOptions = {"
    "ICO_ConsumeAll = 0,"
    "ICO_ConsumeBoundKeys = 1,"
    "ICO_ConsumeNone = 2,"
    "ICO_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFlushLevelStreamingType = {"
    "None = 0,"
    "Full = 1,"
    "Visibility = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERadialImpulseFalloff = {"
    "RIF_Constant = 0,"
    "RIF_Linear = 1,"
    "RIF_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESleepFamily = {"
    "Normal = 0,"
    "Sensitive = 1,"
    "Custom = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETimelineSigType = {"
    "ETS_EventSignature = 0,"
    "ETS_FloatSignature = 1,"
    "ETS_VectorSignature = 2,"
    "ETS_LinearColorSignature = 3,"
    "ETS_InvalidSignature = 4,"
    "ETS_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELightMapPaddingType = {"
    "LMPT_NormalPadding = 0,"
    "LMPT_PrePadding = 1,"
    "LMPT_NoPadding = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShadowMapFlags = {"
    "SMF_None = 0,"
    "SMF_Streamed = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETeleportType = {"
    "None = 0,"
    "TeleportPhysics = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUpdateRateShiftBucket = {"
    "ShiftBucket0 = 0,"
    "ShiftBucket1 = 1,"
    "ShiftBucket2 = 2,"
    "ShiftBucket3 = 3,"
    "ShiftBucket4 = 4,"
    "ShiftBucket5 = 5,"
    "ShiftBucketMax = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOptimizeMode = {"
    "TrailMode = 0,"
    "LookAheadMode = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENetRole = {"
    "ROLE_None = 0,"
    "ROLE_SimulatedProxy = 1,"
    "ROLE_AutonomousProxy = 2,"
    "ROLE_Authority = 3,"
    "ROLE_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENetDormancy = {"
    "DORM_Never = 0,"
    "DORM_Awake = 1,"
    "DORM_DormantAll = 2,"
    "DORM_DormantPartial = 3,"
    "DORM_Initial = 4,"
    "DORN_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAutoPossessAI = {"
    "Disabled = 0,"
    "PlacedInWorld = 1,"
    "Spawned = 2,"
    "PlacedInWorldOrSpawned = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVectorQuantization = {"
    "RoundWholeNumber = 0,"
    "RoundOneDecimal = 1,"
    "RoundTwoDecimals = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERotatorQuantization = {"
    "ByteComponents = 0,"
    "ShortComponents = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWalkableSlopeBehavior = {"
    "WalkableSlope_Default = 0,"
    "WalkableSlope_Increase = 1,"
    "WalkableSlope_Decrease = 2,"
    "WalkableSlope_Unwalkable = 3,"
    "WalkableSlope_Max = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPhysicalSurface = {"
    "SurfaceType_Default = 0,"
    "SurfaceType1 = 1,"
    "SurfaceType2 = 2,"
    "SurfaceType3 = 3,"
    "SurfaceType4 = 4,"
    "SurfaceType5 = 5,"
    "SurfaceType6 = 6,"
    "SurfaceType7 = 7,"
    "SurfaceType8 = 8,"
    "SurfaceType9 = 9,"
    "SurfaceType10 = 10,"
    "SurfaceType11 = 11,"
    "SurfaceType12 = 12,"
    "SurfaceType13 = 13,"
    "SurfaceType14 = 14,"
    "SurfaceType15 = 15,"
    "SurfaceType16 = 16,"
    "SurfaceType17 = 17,"
    "SurfaceType18 = 18,"
    "SurfaceType19 = 19,"
    "SurfaceType20 = 20,"
    "SurfaceType21 = 21,"
    "SurfaceType22 = 22,"
    "SurfaceType23 = 23,"
    "SurfaceType24 = 24,"
    "SurfaceType25 = 25,"
    "SurfaceType26 = 26,"
    "SurfaceType27 = 27,"
    "SurfaceType28 = 28,"
    "SurfaceType29 = 29,"
    "SurfaceType30 = 30,"
    "SurfaceType31 = 31,"
    "SurfaceType32 = 32,"
    "SurfaceType33 = 33,"
    "SurfaceType34 = 34,"
    "SurfaceType35 = 35,"
    "SurfaceType36 = 36,"
    "SurfaceType37 = 37,"
    "SurfaceType38 = 38,"
    "SurfaceType39 = 39,"
    "SurfaceType40 = 40,"
    "SurfaceType41 = 41,"
    "SurfaceType42 = 42,"
    "SurfaceType43 = 43,"
    "SurfaceType44 = 44,"
    "SurfaceType45 = 45,"
    "SurfaceType46 = 46,"
    "SurfaceType47 = 47,"
    "SurfaceType48 = 48,"
    "SurfaceType49 = 49,"
    "SurfaceType50 = 50,"
    "SurfaceType51 = 51,"
    "SurfaceType52 = 52,"
    "SurfaceType53 = 53,"
    "SurfaceType54 = 54,"
    "SurfaceType55 = 55,"
    "SurfaceType56 = 56,"
    "SurfaceType57 = 57,"
    "SurfaceType58 = 58,"
    "SurfaceType59 = 59,"
    "SurfaceType60 = 60,"
    "SurfaceType61 = 61,"
    "SurfaceType62 = 62,"
    "SurfaceType_Max = 63,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAngularConstraintMotion = {"
    "ACM_Free = 0,"
    "ACM_Limited = 1,"
    "ACM_Locked = 2,"
    "ACM_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESpawnActorCollisionHandlingMethod = {"
    "Undefined = 0,"
    "AlwaysSpawn = 1,"
    "AdjustIfPossibleButAlwaysSpawn = 2,"
    "AdjustIfPossibleButDontSpawnIfColliding = 3,"
    "DontSpawnIfColliding = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUserActivityContext = {"
    "Game = 0,"
    "Editor = 1,"
    "Other = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMeshBufferAccess = {"
    "Default = 0,"
    "ForceCPUAndGPU = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELevelCollectionType = {"
    "DynamicSourceLevels = 0,"
    "DynamicDuplicatedLevels = 1,"
    "StaticLevels = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EQueryMobilityType = {"
    "Any = 0,"
    "Static = 1,"
    "Dynamic = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.InitType = {"
    "AllObjects = 0,"
    "AllStaticObjects = 1,"
    "AllDynamicObjects = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAsyncTraceType = {"
    "Test = 0,"
    "Single = 1,"
    "Multi = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlendableLocation = {"
    "BL_AfterTonemapping = 0,"
    "BL_BeforeTonemapping = 1,"
    "BL_BeforeTranslucency = 2,"
    "BL_ReplacingTonemapper = 3,"
    "BL_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDepthOfFieldMethod = {"
    "DOFM_BokehDOF = 0,"
    "DOFM_Gaussian = 1,"
    "DOFM_CircleDOF = 2,"
    "DOFM_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAntiAliasingMethod = {"
    "AAM_None = 0,"
    "AAM_FXAA = 1,"
    "AAM_TemporalAA = 2,"
    "AAM_MSAA = 3,"
    "AAM_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAutoExposureMethod = {"
    "AEM_Histogram = 0,"
    "AEM_Basic = 1,"
    "AEM_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBloomMethod = {"
    "BM_SOG = 0,"
    "BM_FFT = 1,"
    "BM_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBasePassDrawListType = {"
    "EBasePass_Default = 0,"
    "EBasePass_Masked = 1,"
    "EBasePass_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShadingPath = {"
    "Mobile = 0,"
    "Deferred = 1,"
    "Num = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDebugViewShaderMode = {"
    "DVSM_None = 0,"
    "DVSM_ShaderComplexity = 1,"
    "DVSM_ShaderComplexityContainedQuadOverhead = 2,"
    "DVSM_ShaderComplexityBleedingQuadOverhead = 3,"
    "DVSM_QuadComplexity = 4,"
    "DVSM_PrimitiveDistanceAccuracy = 5,"
    "DVSM_MeshUVDensityAccuracy = 6,"
    "DVSM_MaterialTextureScaleAccuracy = 7,"
    "DVSM_OutputMaterialTextureScales = 8,"
    "DVSM_RequiredTextureResolution = 9,"
    "DVSM_MAX = 10,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EEdGraphPinDirection = {"
    "EGPD_Input = 0,"
    "EGPD_Output = 1,"
    "EGPD_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPinContainerType = {"
    "None = 0,"
    "Array = 1,"
    "Set = 2,"
    "Map = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENodeEnabledState = {"
    "Enabled = 0,"
    "Disabled = 1,"
    "DevelopmentOnly = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESaveOrphanPinMode = {"
    "SaveNone = 0,"
    "SaveAll = 1,"
    "SaveAllButExec = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlueprintPinStyleType = {"
    "BPST_Original = 0,"
    "BPST_VariantA = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EComponentCreationMethod = {"
    "Native = 0,"
    "SimpleConstructionScript = 1,"
    "UserConstructionScript = 2,"
    "Instance = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUpdateTransformFlags = {"
    "None = 0,"
    "SkipPhysicsUpdate = 1,"
    "PropagateFromParent = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDetailMode = {"
    "DM_Low = 0,"
    "DM_Medium = 1,"
    "DM_High = 2,"
    "DM_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERelativeTransformSpace = {"
    "RTS_World = 0,"
    "RTS_Actor = 1,"
    "RTS_Component = 2,"
    "RTS_ParentBoneSpace = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMoveComponentFlags = {"
    "MOVECOMP_NoFlags = 0,"
    "MOVECOMP_IgnoreBases = 1,"
    "MOVECOMP_SkipPhysicsMove = 2,"
    "MOVECOMP_NeverIgnoreBlockingOverlaps = 4,"
    "MOVECOMP_DisableBlockingOverlapDispatch = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVisibilityPropagation = {"
    "NoPropagation = 0,"
    "DirtyOnly = 1,"
    "Propagate = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EHasMovedTransformOption = {"
    "eTestTransform = 0,"
    "eIgnoreTransform = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOverlapState = {"
    "eUseParent = 0,"
    "eUnknown = 1,"
    "eIncludesOverlaps = 2,"
    "eForceUpdate = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureSizingType = {"
    "TextureSizingType_UseSingleTextureSize = 0,"
    "TextureSizingType_UseAutomaticBiasedSizes = 1,"
    "TextureSizingType_UseManualOverrideTextureSize = 2,"
    "TextureSizingType_UseSimplygonAutomaticSizing = 3,"
    "TextureSizingType_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialMergeType = {"
    "MaterialMergeType_Default = 0,"
    "MaterialMergeType_Simplygon = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EActorBeginPlayState = {"
    "HasNotBegunPlay = 0,"
    "BeginningPlay = 1,"
    "HasBegunPlay = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECreateIfEmpty = {"
    "Invalid = -1,"
    "DontCreate = 0,"
    "Create = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENavDataGatheringMode = {"
    "Default = 0,"
    "Instant = 1,"
    "Lazy = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENavDataGatheringModeConfig = {"
    "Invalid = 0,"
    "Instant = 1,"
    "Lazy = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlueprintStatus = {"
    "BS_Unknown = 0,"
    "BS_Dirty = 1,"
    "BS_Error = 2,"
    "BS_UpToDate = 3,"
    "BS_BeingCreated = 4,"
    "BS_UpToDateWithWarnings = 5,"
    "BS_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlueprintType = {"
    "BPTYPE_Normal = 0,"
    "BPTYPE_Const = 1,"
    "BPTYPE_MacroLibrary = 2,"
    "BPTYPE_Interface = 3,"
    "BPTYPE_LevelScript = 4,"
    "BPTYPE_FunctionLibrary = 5,"
    "BPTYPE_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlueprintCompileMode = {"
    "Default = 0,"
    "Development = 1,"
    "FinalRelease = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBlueprintNativizationFlag = {"
    "Disabled = 0,"
    "Dependency = 1,"
    "ExplicitlyEnabled = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EIsBPNonReducible = {"
    "Unkown = 0,"
    "Yes = 1,"
    "No = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EEncryptionResponse = {"
    "Failure = 0,"
    "Success = 1,"
    "InvalidToken = 2,"
    "NoKey = 3,"
    "SessionIdMismatch = 4,"
    "InvalidParams = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EInitialOscillatorOffset = {"
    "EOO_OffsetRandom = 0,"
    "EOO_OffsetZero = 1,"
    "EOO_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EViewTargetBlendFunction = {"
    "VTBlend_Linear = 0,"
    "VTBlend_Cubic = 1,"
    "VTBlend_EaseIn = 2,"
    "VTBlend_EaseOut = 3,"
    "VTBlend_EaseInOut = 4,"
    "VTBlend_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERelationshipType = {"
    "None = 0,"
    "Same = 1,"
    "Masked = 2,"
    "Masks = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERichCurveInterpMode = {"
    "RCIM_Linear = 0,"
    "RCIM_Constant = 1,"
    "RCIM_Cubic = 2,"
    "RCIM_None = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERichCurveTangentMode = {"
    "RCTM_Auto = 0,"
    "RCTM_User = 1,"
    "RCTM_Break = 2,"
    "RCTM_None = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERichCurveTangentWeightMode = {"
    "RCTWM_WeightedNone = 0,"
    "RCTWM_WeightedArrive = 1,"
    "RCTWM_WeightedLeave = 2,"
    "RCTWM_WeightedBoth = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERichCurveExtrapolation = {"
    "RCCE_Cycle = 0,"
    "RCCE_CycleWithOffset = 1,"
    "RCCE_Oscillate = 2,"
    "RCCE_Linear = 3,"
    "RCCE_Constant = 4,"
    "RCCE_None = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPackageReloadPhase = {"
    "PrePackageFixup = 0,"
    "OnPackageFixup = 1,"
    "PostPackageFixup = 2,"
    "PreBatch = 3,"
    "PostBatchPreGC = 4,"
    "PostBatchPostGC = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.FForceFeedbackChannelType = {"
    "LEFT_LARGE = 0,"
    "LEFT_SMALL = 1,"
    "RIGHT_LARGE = 2,"
    "RIGHT_SMALL = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMeshLODSelectionType = {"
    "AllLODs = 0,"
    "SpecificLOD = 1,"
    "CalculateLOD = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMeshMergeType = {"
    "MeshMergeType_Default = 0,"
    "MeshMergeType_MergeActor = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECsgOper = {"
    "CSG_Active = 0,"
    "CSG_Add = 1,"
    "CSG_Subtract = 2,"
    "CSG_Intersect = 3,"
    "CSG_Deintersect = 4,"
    "CSG_None = 5,"
    "CSG_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBrushType = {"
    "Brush_Default = 0,"
    "Brush_Add = 1,"
    "Brush_Subtract = 2,"
    "Brush_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAttenuationDistanceModel = {"
    "Linear = 0,"
    "Logarithmic = 1,"
    "Inverse = 2,"
    "LogReverse = 3,"
    "NaturalSound = 4,"
    "Custom = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAudioPlatform = {"
    "Windows = 0,"
    "Mac = 1,"
    "Linux = 2,"
    "IOS = 3,"
    "Android = 4,"
    "XboxOne = 5,"
    "Playstation4 = 6,"
    "Switch = 7,"
    "HTML5 = 8,"
    "Unknown = 9,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAudioPlugin = {"
    "SPATIALIZATION = 0,"
    "REVERB = 1,"
    "OCCLUSION = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESoundDistanceCalc = {"
    "SOUNDDISTANCE_Normal = 0,"
    "SOUNDDISTANCE_InfiniteXYPlane = 1,"
    "SOUNDDISTANCE_InfiniteXZPlane = 2,"
    "SOUNDDISTANCE_InfiniteYZPlane = 3,"
    "SOUNDDISTANCE_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESoundSpatializationAlgorithm = {"
    "SPATIALIZATION_Default = 0,"
    "SPATIALIZATION_HRTF = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAirAbsorptionMethod = {"
    "Linear = 0,"
    "CustomCurve = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EReverbSendMethod = {"
    "Linear = 0,"
    "CustomCurve = 1,"
    "Manual = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAudioSpeakers = {"
    "SPEAKER_FrontLeft = 0,"
    "SPEAKER_FrontRight = 1,"
    "SPEAKER_FrontCenter = 2,"
    "SPEAKER_LowFrequency = 3,"
    "SPEAKER_LeftSurround = 4,"
    "SPEAKER_RightSurround = 5,"
    "SPEAKER_LeftBack = 6,"
    "SPEAKER_RightBack = 7,"
    "SPEAKER_Count = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELoopingMode = {"
    "LOOP_Never = 0,"
    "LOOP_WithNotification = 1,"
    "LOOP_Forever = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ReverbPreset = {"
    "REVERB_Default = 0,"
    "REVERB_Bathroom = 1,"
    "REVERB_StoneRoom = 2,"
    "REVERB_Auditorium = 3,"
    "REVERB_ConcertHall = 4,"
    "REVERB_Cave = 5,"
    "REVERB_Hallway = 6,"
    "REVERB_StoneCorridor = 7,"
    "REVERB_Alley = 8,"
    "REVERB_Forest = 9,"
    "REVERB_City = 10,"
    "REVERB_Mountains = 11,"
    "REVERB_Quarry = 12,"
    "REVERB_Plain = 13,"
    "REVERB_ParkingLot = 14,"
    "REVERB_SewerPipe = 15,"
    "REVERB_Underwater = 16,"
    "REVERB_SmallRoom = 17,"
    "REVERB_MediumRoom = 18,"
    "REVERB_LargeRoom = 19,"
    "REVERB_MediumHall = 20,"
    "REVERB_LargeHall = 21,"
    "REVERB_Plate = 22,"
    "REVERB_MAX = 23,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVisibilityAggressiveness = {"
    "VIS_LeastAggressive = 0,"
    "VIS_ModeratelyAggressive = 1,"
    "VIS_MostAggressive = 2,"
    "VIS_Max = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVolumeLightingMethod = {"
    "VLM_VolumetricLightmap = 0,"
    "VLM_SparseVolumeLightingSamples = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.Mode = {"
    "Client = 0,"
    "Server = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EChannelType = {"
    "CHTYPE_None = 0,"
    "CHTYPE_Control = 1,"
    "CHTYPE_Actor = 2,"
    "CHTYPE_File = 3,"
    "CHTYPE_Voice = 4,"
    "CHTYPE_MAX = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENetworkChecksumMode = {"
    "None = 0,"
    "SaveAndUse = 1,"
    "SaveButIgnore = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAsyncLoadMode = {"
    "UseCVar = 0,"
    "ForceDisable = 1,"
    "ForceEnable = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EJson = {"
    "None = 0,"
    "Null = 1,"
    "String = 2,"
    "Number = 3,"
    "Boolean = 4,"
    "Array = 5,"
    "Object = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EJsonToken = {"
    "None = 0,"
    "Comma = 1,"
    "CurlyOpen = 2,"
    "CurlyClose = 3,"
    "SquareOpen = 4,"
    "SquareClose = 5,"
    "Colon = 6,"
    "String = 7,"
    "Number = 8,"
    "True = 9,"
    "False = 10,"
    "Null = 11,"
    "Identifier = 12,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EJsonNotation = {"
    "ObjectStart = 0,"
    "ObjectEnd = 1,"
    "ArrayStart = 2,"
    "ArrayEnd = 3,"
    "Boolean = 4,"
    "String = 5,"
    "Number = 6,"
    "Null = 7,"
    "Error = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConnectionState = {"
    "USOCK_Invalid = 0,"
    "USOCK_Closed = 1,"
    "USOCK_Pending = 2,"
    "USOCK_Open = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWriteBitsDataType = {"
    "Unknown = 0,"
    "Bunch = 1,"
    "Ack = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENetworkVersionHistory = {"
    "HISTORY_INITIAL = 1,"
    "HISTORY_SAVE_ABS_TIME_MS = 2,"
    "HISTORY_INCREASE_BUFFER = 3,"
    "HISTORY_SAVE_ENGINE_VERSION = 4,"
    "HISTORY_EXTRA_VERSION = 5,"
    "HISTORY_MULTIPLE_LEVELS = 6,"
    "HISTORY_MULTIPLE_LEVELS_TIME_CHANGES = 7,"
    "HISTORY_DELETED_STARTUP_ACTORS = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESafeZoneType = {"
    "eSZ_TOP = 0,"
    "eSZ_BOTTOM = 1,"
    "eSZ_LEFT = 2,"
    "eSZ_RIGHT = 3,"
    "eSZ_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStereoscopicPass = {"
    "eSSP_FULL = 0,"
    "eSSP_LEFT_EYE = 1,"
    "eSSP_RIGHT_EYE = 2,"
    "eSSP_MONOSCOPIC_EYE = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShaderParameterFlags = {"
    "SPF_Optional = 0,"
    "SPF_Mandatory = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConstructTextureFlags = {"
    "CTF_Compress = 1,"
    "CTF_DeferCompression = 2,"
    "CTF_SRGB = 4,"
    "CTF_AllowMips = 8,"
    "CTF_ForceOneBitAlpha = 16,"
    "CTF_RemapAlphaAsMasked = 32,"
    "CTF_ForceOpaque = 64,"
    "CTF_Default = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMonoscopicFarFieldMode = {"
    "Off = 0,"
    "On = 1,"
    "StereoOnly = 2,"
    "StereoNoClipping = 3,"
    "MonoOnly = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETranslucencyVolumeCascade = {"
    "TVC_Inner = 0,"
    "TVC_Outer = 1,"
    "TVC_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialUsage = {"
    "MATUSAGE_SkeletalMesh = 0,"
    "MATUSAGE_ParticleSprites = 1,"
    "MATUSAGE_BeamTrails = 2,"
    "MATUSAGE_MeshParticles = 3,"
    "MATUSAGE_StaticLighting = 4,"
    "MATUSAGE_MorphTargets = 5,"
    "MATUSAGE_SplineMesh = 6,"
    "MATUSAGE_InstancedStaticMeshes = 7,"
    "MATUSAGE_Clothing = 8,"
    "MATUSAGE_NiagaraSprites = 9,"
    "MATUSAGE_NiagaraRibbons = 10,"
    "MATUSAGE_NiagaraMeshParticles = 11,"
    "MATUSAGE_MAX = 12,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBoneAxis = {"
    "BA_X = 0,"
    "BA_Y = 1,"
    "BA_Z = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBoneControlSpace = {"
    "BCS_WorldSpace = 0,"
    "BCS_ComponentSpace = 1,"
    "BCS_ParentBoneSpace = 2,"
    "BCS_BoneSpace = 3,"
    "BCS_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBoneRotationSource = {"
    "BRS_KeepComponentSpaceRotation = 0,"
    "BRS_KeepLocalSpaceRotation = 1,"
    "BRS_CopyFromTarget = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAdditiveAnimationType = {"
    "AAT_None = 0,"
    "AAT_LocalSpaceBase = 1,"
    "AAT_RotationOffsetMeshSpace = 2,"
    "AAT_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAnimInterpolationType = {"
    "Linear = 0,"
    "Step = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAnimAssetCurveFlags = {"
    "AACF_DriveMorphTarget_DEPRECATED = 1,"
    "AACF_DriveAttribute_DEPRECATED = 2,"
    "AACF_Editable = 4,"
    "AACF_DriveMaterial_DEPRECATED = 8,"
    "AACF_Metadata = 16,"
    "AACF_DriveTrack = 32,"
    "AACF_Disabled = 64,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EIndex = {"
    "X = 0,"
    "Y = 1,"
    "Z = 2,"
    "Max = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERawCurveTrackTypes = {"
    "RCT_Float = 0,"
    "RCT_Vector = 1,"
    "RCT_Transform = 2,"
    "RCT_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EEdGraphActionType = {"
    "GRAPHACTION_Default = 0,"
    "GRAPHACTION_AddNode = 1,"
    "GRAPHACTION_SelectNode = 2,"
    "GRAPHACTION_RemoveNode = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECompilerFlags = {"
    "CFLAG_PreferFlowControl = 0,"
    "CFLAG_Debug = 1,"
    "CFLAG_AvoidFlowControl = 2,"
    "CFLAG_SkipValidation = 3,"
    "CFLAG_StandardOptimization = 4,"
    "CFLAG_OnChip = 5,"
    "CFLAG_KeepDebugInfo = 6,"
    "CFLAG_NoFastMath = 7,"
    "CFLAG_ZeroInitialise = 8,"
    "CFLAG_BoundsChecking = 9,"
    "CFLAG_FeatureLevelES31 = 10,"
    "CFLAG_ForceRemoveUnusedInterpolators = 11,"
    "CFLAG_UseFullPrecisionInPS = 12,"
    "CFLAG_VertexToGeometryShader = 13,"
    "CFLAG_Archive = 14,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShaderTypeForDynamicCast = {"
    "Global = 0,"
    "Material = 1,"
    "MeshMaterial = 2,"
    "Niagara = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFilter = {"
    "EAll = 0,"
    "EOnlyShared = 1,"
    "EOnlyUnique = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleVertexFactoryType = {"
    "PVFT_Sprite = 0,"
    "PVFT_BeamTrail = 1,"
    "PVFT_Mesh = 2,"
    "PVFT_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.TextureGroup = {"
    "TEXTUREGROUP_World = 0,"
    "TEXTUREGROUP_WorldNormalMap = 1,"
    "TEXTUREGROUP_WorldSpecular = 2,"
    "TEXTUREGROUP_Character = 3,"
    "TEXTUREGROUP_CharacterNormalMap = 4,"
    "TEXTUREGROUP_CharacterSpecular = 5,"
    "TEXTUREGROUP_Weapon = 6,"
    "TEXTUREGROUP_WeaponNormalMap = 7,"
    "TEXTUREGROUP_WeaponSpecular = 8,"
    "TEXTUREGROUP_Vehicle = 9,"
    "TEXTUREGROUP_VehicleNormalMap = 10,"
    "TEXTUREGROUP_VehicleSpecular = 11,"
    "TEXTUREGROUP_Cinematic = 12,"
    "TEXTUREGROUP_Effects = 13,"
    "TEXTUREGROUP_EffectsNotFiltered = 14,"
    "TEXTUREGROUP_Skybox = 15,"
    "TEXTUREGROUP_UI = 16,"
    "TEXTUREGROUP_Lightmap = 17,"
    "TEXTUREGROUP_RenderTarget = 18,"
    "TEXTUREGROUP_MobileFlattened = 19,"
    "TEXTUREGROUP_ProcBuilding_Face = 20,"
    "TEXTUREGROUP_ProcBuilding_LightMap = 21,"
    "TEXTUREGROUP_Shadowmap = 22,"
    "TEXTUREGROUP_ColorLookupTable = 23,"
    "TEXTUREGROUP_Terrain_Heightmap = 24,"
    "TEXTUREGROUP_Terrain_Weightmap = 25,"
    "TEXTUREGROUP_Bokeh = 26,"
    "TEXTUREGROUP_IESLightProfile = 27,"
    "TEXTUREGROUP_Pixels2D = 28,"
    "TEXTUREGROUP_HierarchicalLOD = 29,"
    "TEXTUREGROUP_MAX = 30,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.TextureMipGenSettings = {"
    "TMGS_FromTextureGroup = 0,"
    "TMGS_SimpleAverage = 1,"
    "TMGS_Sharpen0 = 2,"
    "TMGS_Sharpen1 = 3,"
    "TMGS_Sharpen2 = 4,"
    "TMGS_Sharpen3 = 5,"
    "TMGS_Sharpen4 = 6,"
    "TMGS_Sharpen5 = 7,"
    "TMGS_Sharpen6 = 8,"
    "TMGS_Sharpen7 = 9,"
    "TMGS_Sharpen8 = 10,"
    "TMGS_Sharpen9 = 11,"
    "TMGS_Sharpen10 = 12,"
    "TMGS_NoMipmaps = 13,"
    "TMGS_LeaveExistingMips = 14,"
    "TMGS_Blur1 = 15,"
    "TMGS_Blur2 = 16,"
    "TMGS_Blur3 = 17,"
    "TMGS_Blur4 = 18,"
    "TMGS_Blur5 = 19,"
    "TMGS_MAX = 20,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureSamplerFilter = {"
    "Point = 0,"
    "Bilinear = 1,"
    "Trilinear = 2,"
    "AnisotropicPoint = 3,"
    "AnisotropicLinear = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialValueType = {"
    "MCT_Float1 = 1,"
    "MCT_Float2 = 2,"
    "MCT_Float3 = 4,"
    "MCT_Float4 = 8,"
    "MCT_Float = 15,"
    "MCT_Texture2D = 16,"
    "MCT_TextureCube = 32,"
    "MCT_Texture = 560,"
    "MCT_StaticBool = 64,"
    "MCT_Unknown = 128,"
    "MCT_MaterialAttributes = 256,"
    "MCT_TextureExternal = 512,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialCommonBasis = {"
    "MCB_Tangent = 0,"
    "MCB_Local = 1,"
    "MCB_TranslatedWorld = 2,"
    "MCB_World = 3,"
    "MCB_View = 4,"
    "MCB_Camera = 5,"
    "MCB_MeshParticle = 6,"
    "MCB_MAX = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDeferredParamStrictness = {"
    "ELoose = 0,"
    "EStrict = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialDomain = {"
    "MD_Surface = 0,"
    "MD_DeferredDecal = 1,"
    "MD_LightFunction = 2,"
    "MD_Volume = 3,"
    "MD_PostProcess = 4,"
    "MD_UI = 5,"
    "MD_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECompiledMaterialProperty = {"
    "CompiledMP_EmissiveColorCS = 29,"
    "CompiledMP_PrevWorldPositionOffset = 30,"
    "CompiledMP_MAX = 31,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMobileHDRMode = {"
    "Unset = 0,"
    "Disabled = 1,"
    "EnabledFloat16 = 2,"
    "EnabledMosaic = 3,"
    "EnabledRGBE = 4,"
    "EnabledRGBA8 = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDrawRectangleFlags = {"
    "EDRF_Default = 0,"
    "EDRF_UseTriangleOptimization = 1,"
    "EDRF_UseTesselatedIndexBuffer = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.TextureCompressionSettings = {"
    "TC_Default = 0,"
    "TC_Normalmap = 1,"
    "TC_Masks = 2,"
    "TC_Grayscale = 3,"
    "TC_Displacementmap = 4,"
    "TC_VectorDisplacementmap = 5,"
    "TC_HDR = 6,"
    "TC_EditorIcon = 7,"
    "TC_Alpha = 8,"
    "TC_DistanceFieldFont = 9,"
    "TC_HDR_Compressed = 10,"
    "TC_BC7 = 11,"
    "TC_MAX = 12,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.TextureFilter = {"
    "TF_Nearest = 0,"
    "TF_Bilinear = 1,"
    "TF_Trilinear = 2,"
    "TF_Default = 3,"
    "TF_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.TextureAddress = {"
    "TA_Wrap = 0,"
    "TA_Clamp = 1,"
    "TA_Mirror = 2,"
    "TA_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECompositeTextureMode = {"
    "CTM_Disabled = 0,"
    "CTM_NormalRoughnessToRed = 1,"
    "CTM_NormalRoughnessToGreen = 2,"
    "CTM_NormalRoughnessToBlue = 3,"
    "CTM_NormalRoughnessToAlpha = 4,"
    "CTM_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureMipCount = {"
    "TMC_ResidentMips = 0,"
    "TMC_AllMips = 1,"
    "TMC_AllMipsBiased = 2,"
    "TMC_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureSourceArtType = {"
    "TSAT_Uncompressed = 0,"
    "TSAT_PNGCompressed = 1,"
    "TSAT_DDSFile = 2,"
    "TSAT_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureSourceFormat = {"
    "TSF_Invalid = 0,"
    "TSF_G8 = 1,"
    "TSF_BGRA8 = 2,"
    "TSF_BGRE8 = 3,"
    "TSF_RGBA16 = 4,"
    "TSF_RGBA16F = 5,"
    "TSF_RGBA8 = 6,"
    "TSF_RGBE8 = 7,"
    "TSF_MAX = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureCompressionQuality = {"
    "TCQ_Default = 0,"
    "TCQ_Lowest = 1,"
    "TCQ_Low = 2,"
    "TCQ_Medium = 3,"
    "TCQ_High = 4,"
    "TCQ_Highest = 5,"
    "TCQ_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELightInteractionType = {"
    "LIT_CachedIrrelevant = 0,"
    "LIT_CachedLightMap = 1,"
    "LIT_Dynamic = 2,"
    "LIT_CachedSignedDistanceFieldShadowMap2D = 3,"
    "LIT_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleStates = {"
    "STATE_Particle_Freeze = 67108864,"
    "STATE_Particle_IgnoreCollisions = 134217728,"
    "STATE_Particle_FreezeTranslation = 268435456,"
    "STATE_Particle_FreezeRotation = 536870912,"
    "STATE_Particle_CollisionIgnoreCheck = 1006632960,"
    "STATE_Particle_DelayCollisions = 1073741824,"
    "STATE_Particle_CollisionHasOccurred = -2147483648,"
    "STATE_Mask = -67108864,"
    "STATE_CounterMask = 67108863,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDynamicEmitterType = {"
    "DET_Unknown = 0,"
    "DET_Sprite = 1,"
    "DET_Mesh = 2,"
    "DET_Beam2 = 3,"
    "DET_Ribbon = 4,"
    "DET_AnimTrail = 5,"
    "DET_Custom = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleSignificanceLevel = {"
    "Low = 0,"
    "Medium = 1,"
    "High = 2,"
    "Critical = 3,"
    "Num = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleSystemInsignificanceReaction = {"
    "Auto = 0,"
    "Complete = 1,"
    "DisableTick = 2,"
    "DisableTickAndKill = 3,"
    "Num = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERawDistributionOperation = {"
    "RDO_Uninitialized = 0,"
    "RDO_None = 1,"
    "RDO_Random = 2,"
    "RDO_Extreme = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.DistributionParamMode = {"
    "DPM_Normal = 0,"
    "DPM_Abs = 1,"
    "DPM_Direct = 2,"
    "DPM_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDistributionVectorLockFlags = {"
    "EDVLF_None = 0,"
    "EDVLF_XY = 1,"
    "EDVLF_XZ = 2,"
    "EDVLF_YZ = 3,"
    "EDVLF_XYZ = 4,"
    "EDVLF_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDistributionVectorMirrorFlags = {"
    "EDVMF_Same = 0,"
    "EDVMF_Different = 1,"
    "EDVMF_Mirror = 2,"
    "EDVMF_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EModuleType = {"
    "EPMT_General = 0,"
    "EPMT_TypeData = 1,"
    "EPMT_Beam = 2,"
    "EPMT_Trail = 3,"
    "EPMT_Spawn = 4,"
    "EPMT_Required = 5,"
    "EPMT_Event = 6,"
    "EPMT_Light = 7,"
    "EPMT_SubUV = 8,"
    "EPMT_MAX = 9,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleSourceSelectionMethod = {"
    "EPSSM_Random = 0,"
    "EPSSM_Sequential = 1,"
    "EPSSM_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleAxisLock = {"
    "EPAL_NONE = 0,"
    "EPAL_X = 1,"
    "EPAL_Y = 2,"
    "EPAL_Z = 3,"
    "EPAL_NEGATIVE_X = 4,"
    "EPAL_NEGATIVE_Y = 5,"
    "EPAL_NEGATIVE_Z = 6,"
    "EPAL_ROTATE_X = 7,"
    "EPAL_ROTATE_Y = 8,"
    "EPAL_ROTATE_Z = 9,"
    "EPAL_MAX = 10,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGetTrailDirection = {"
    "GET_Prev = 0,"
    "GET_Next = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGetTrailParticleOption = {"
    "GET_Any = 0,"
    "GET_Spawned = 1,"
    "GET_Interpolated = 2,"
    "GET_Start = 3,"
    "GET_End = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EQualityLevelBehavior = {"
    "EAbsolute = 0,"
    "ERelativeToMax = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETimerStatus = {"
    "Pending = 0,"
    "Active = 1,"
    "Paused = 2,"
    "Executing = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.SkeletalMeshOptimizationImportance = {"
    "SMOI_Off = 0,"
    "SMOI_Lowest = 1,"
    "SMOI_Low = 2,"
    "SMOI_Normal = 3,"
    "SMOI_High = 4,"
    "SMOI_Highest = 5,"
    "SMOI_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.SkeletalMeshOptimizationType = {"
    "SMOT_NumOfTriangles = 0,"
    "SMOT_MaxDeviation = 1,"
    "SMOT_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAdditiveBasePoseType = {"
    "ABPT_None = 0,"
    "ABPT_RefPose = 1,"
    "ABPT_AnimScaled = 2,"
    "ABPT_AnimFrame = 3,"
    "ABPT_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.AnimationCompressionFormat = {"
    "ACF_None = 0,"
    "ACF_Float96NoW = 1,"
    "ACF_Fixed48NoW = 2,"
    "ACF_IntervalFixed32NoW = 3,"
    "ACF_Fixed32NoW = 4,"
    "ACF_Float32NoW = 5,"
    "ACF_Identity = 6,"
    "ACF_MAX = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERootMotionAccumulateMode = {"
    "Override = 0,"
    "Additive = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERootMotionSourceStatusFlags = {"
    "Prepared = 1,"
    "Finished = 2,"
    "MarkedForRemoval = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERootMotionSourceSettingsFlags = {"
    "UseSensitiveLiftoffCheck = 1,"
    "DisablePartialEndTick = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERootMotionSourceID = {"
    "Invalid = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERootMotionFinishVelocityMode = {"
    "MaintainLastRootMotionVelocity = 0,"
    "SetVelocity = 1,"
    "ClampVelocity = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.BodyInstanceSceneState = {"
    "NotAdded = 0,"
    "AwaitingAdd = 1,"
    "Added = 2,"
    "AwaitingRemove = 3,"
    "Removed = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDynamicActorScene = {"
    "Default = 0,"
    "UseSyncScene = 1,"
    "UseAsyncScene = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureStreamingBuildType = {"
    "TSB_MapBuild = 0,"
    "TSB_ValidationOnly = 1,"
    "TSB_ViewMode = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECanBeCharacterBase = {"
    "ECB_No = 0,"
    "ECB_Yes = 1,"
    "ECB_Owner = 2,"
    "ECB_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERendererStencilMask = {"
    "ERSM_Default = 0,"
    "ERSM_255 = 1,"
    "ERSM_1 = 2,"
    "ERSM_2 = 3,"
    "ERSM_4 = 4,"
    "ERSM_8 = 5,"
    "ERSM_16 = 6,"
    "ERSM_32 = 7,"
    "ERSM_64 = 8,"
    "ERSM_128 = 9,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBoneVisibilityStatus = {"
    "BVS_HiddenByParent = 0,"
    "BVS_Visible = 1,"
    "BVS_ExplicitlyHidden = 2,"
    "BVS_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPhysBodyOp = {"
    "PBO_None = 0,"
    "PBO_Term = 1,"
    "PBO_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EClothingTeleportMode = {"
    "None = 0,"
    "Teleport = 1,"
    "TeleportAndReset = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAllowKinematicDeferral = {"
    "AllowDeferral = 0,"
    "DisallowDeferral = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShapeBodySetupHelper = {"
    "InvalidateSharingIfStale = 0,"
    "UpdateBodySetup = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERuntimeGenerationType = {"
    "Static = 0,"
    "DynamicModifiersOnly = 1,"
    "Dynamic = 2,"
    "LegacyGeneration = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.FNavigationSystemRunMode = {"
    "InvalidMode = 0,"
    "GameMode = 1,"
    "EditorMode = 2,"
    "SimulationMode = 3,"
    "PIEMode = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERegistrationResult = {"
    "RegistrationError = 0,"
    "RegistrationFailed_DataPendingKill = 1,"
    "RegistrationFailed_AgentAlreadySupported = 2,"
    "RegistrationFailed_AgentNotValid = 3,"
    "RegistrationSuccessful = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOctreeUpdateMode = {"
    "OctreeUpdate_Default = 0,"
    "OctreeUpdate_Geometry = 1,"
    "OctreeUpdate_Modifiers = 2,"
    "OctreeUpdate_Refresh = 4,"
    "OctreeUpdate_ParentChain = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECleanupMode = {"
    "CleanupWithWorld = 0,"
    "CleanupUnsafe = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAlphaBlendOption = {"
    "Linear = 0,"
    "Cubic = 1,"
    "HermiteCubic = 2,"
    "Sinusoidal = 3,"
    "QuadraticInOut = 4,"
    "CubicInOut = 5,"
    "QuarticInOut = 6,"
    "QuinticInOut = 7,"
    "CircularIn = 8,"
    "CircularOut = 9,"
    "CircularInOut = 10,"
    "ExpIn = 11,"
    "ExpOut = 12,"
    "ExpInOut = 13,"
    "Custom = 14,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETypeAdvanceAnim = {"
    "ETAA_Default = 0,"
    "ETAA_Finished = 1,"
    "ETAA_Looped = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETimeStretchCurveMapping = {"
    "T_Original = 0,"
    "T_TargetMin = 1,"
    "T_TargetMax = 2,"
    "MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMontageSubStepResult = {"
    "Moved = 0,"
    "NotMoved = 1,"
    "InvalidSection = 2,"
    "InvalidMontage = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPlaneConstraintAxisSetting = {"
    "Custom = 0,"
    "X = 1,"
    "Y = 2,"
    "Z = 3,"
    "UseGlobalPhysicsSetting = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EShrinkCapsuleExtent = {"
    "SHRINK_None = 0,"
    "SHRINK_RadiusCustom = 1,"
    "SHRINK_HeightCustom = 2,"
    "SHRINK_AllCustom = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERootMotionMapping = {"
    "MapSize = 16,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPostUpdateMode = {"
    "PostUpdate_Record = 0,"
    "PostUpdate_Replay = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.CompressedFlags = {"
    "FLAG_JumpPressed = 1,"
    "FLAG_WantsToCrouch = 2,"
    "FLAG_Reserved_1 = 4,"
    "FLAG_Reserved_2 = 8,"
    "FLAG_Custom_0 = 16,"
    "FLAG_Custom_1 = 32,"
    "FLAG_Custom_2 = 64,"
    "FLAG_Custom_3 = 128,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleBurstMethod = {"
    "EPBM_Instant = 0,"
    "EPBM_Interpolated = 1,"
    "EPBM_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleSubUVInterpMethod = {"
    "PSUVIM_None = 0,"
    "PSUVIM_Linear = 1,"
    "PSUVIM_Linear_Blend = 2,"
    "PSUVIM_Random = 3,"
    "PSUVIM_Random_Blend = 4,"
    "PSUVIM_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EEmitterRenderMode = {"
    "ERM_Normal = 0,"
    "ERM_Point = 1,"
    "ERM_Cross = 2,"
    "ERM_LightsOnly = 3,"
    "ERM_None = 4,"
    "ERM_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleSystemUpdateMode = {"
    "EPSUM_RealTime = 0,"
    "EPSUM_FixedTime = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ParticleSystemLODMethod = {"
    "PARTICLESYSTEMLODMETHOD_Automatic = 0,"
    "PARTICLESYSTEMLODMETHOD_DirectSet = 1,"
    "PARTICLESYSTEMLODMETHOD_ActivateAutomatic = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleSystemOcclusionBoundsMethod = {"
    "EPSOBM_None = 0,"
    "EPSOBM_ParticleBounds = 1,"
    "EPSOBM_CustomBounds = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleSysParamType = {"
    "PSPT_None = 0,"
    "PSPT_Scalar = 1,"
    "PSPT_ScalarRand = 2,"
    "PSPT_Vector = 3,"
    "PSPT_VectorRand = 4,"
    "PSPT_Color = 5,"
    "PSPT_Actor = 6,"
    "PSPT_Material = 7,"
    "PSPT_MAX = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ParticleReplayState = {"
    "PRS_Disabled = 0,"
    "PRS_Capturing = 1,"
    "PRS_Replaying = 2,"
    "PRS_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParticleEventType = {"
    "EPET_Any = 0,"
    "EPET_Spawn = 1,"
    "EPET_Death = 2,"
    "EPET_Collision = 3,"
    "EPET_Burst = 4,"
    "EPET_Blueprint = 5,"
    "EPET_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EForceAsyncWorkCompletion = {"
    "STALL = 0,"
    "ENSURE_AND_STALL = 1,"
    "SILENT = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECollisionTraceFlag = {"
    "CTF_UseDefault = 0,"
    "CTF_UseSimpleAndComplex = 1,"
    "CTF_UseSimpleAsComplex = 2,"
    "CTF_UseComplexAsSimple = 3,"
    "CTF_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPhysicsType = {"
    "PhysType_Default = 0,"
    "PhysType_Kinematic = 1,"
    "PhysType_Simulated = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStaticMeshVertexTangentBasisType = {"
    "Default = 0,"
    "HighPrecision = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStaticMeshVertexUVType = {"
    "Default = 0,"
    "HighPrecision = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ENormalMode = {"
    "NM_PreserveSmoothingGroups = 0,"
    "NM_RecalculateNormals = 1,"
    "NM_RecalculateNormalsSmooth = 2,"
    "NM_RecalculateNormalsHard = 3,"
    "TEMP_BROKEN = 4,"
    "ENormalMode_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EImportanceLevel = {"
    "IL_Off = 0,"
    "IL_Lowest = 1,"
    "IL_Low = 2,"
    "IL_Normal = 3,"
    "IL_High = 4,"
    "IL_Highest = 5,"
    "TEMP_BROKEN2 = 6,"
    "EImportanceLevel_MAX = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EOptimizationType = {"
    "OT_NumOfTriangles = 0,"
    "OT_MaxDeviation = 1,"
    "OT_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EImportStaticMeshVersion = {"
    "BeforeImportStaticMeshVersionWasAdded = 0,"
    "RemoveStaticMeshSkinxxWorkflow = 1,"
    "VersionPlusOne = 2,"
    "LastVersion = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDecalBlendMode = {"
    "DBM_Translucent = 0,"
    "DBM_Stain = 1,"
    "DBM_Normal = 2,"
    "DBM_Emissive = 3,"
    "DBM_DBuffer_ColorNormalRoughness = 4,"
    "DBM_DBuffer_Color = 5,"
    "DBM_DBuffer_ColorNormal = 6,"
    "DBM_DBuffer_ColorRoughness = 7,"
    "DBM_DBuffer_Normal = 8,"
    "DBM_DBuffer_NormalRoughness = 9,"
    "DBM_DBuffer_Roughness = 10,"
    "DBM_Volumetric_DistanceFunction = 11,"
    "DBM_MAX = 12,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMaterialDecalResponse = {"
    "MDR_None = 0,"
    "MDR_ColorNormalRoughness = 1,"
    "MDR_Color = 2,"
    "MDR_ColorNormal = 3,"
    "MDR_ColorRoughness = 4,"
    "MDR_Normal = 5,"
    "MDR_NormalRoughness = 6,"
    "MDR_Roughness = 7,"
    "MDR_MAX = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESoundGroup = {"
    "SOUNDGROUP_Default = 0,"
    "SOUNDGROUP_Effects = 1,"
    "SOUNDGROUP_UI = 2,"
    "SOUNDGROUP_Music = 3,"
    "SOUNDGROUP_Voice = 4,"
    "SOUNDGROUP_GameSoundGroup1 = 5,"
    "SOUNDGROUP_GameSoundGroup2 = 6,"
    "SOUNDGROUP_GameSoundGroup3 = 7,"
    "SOUNDGROUP_GameSoundGroup4 = 8,"
    "SOUNDGROUP_GameSoundGroup5 = 9,"
    "SOUNDGROUP_GameSoundGroup6 = 10,"
    "SOUNDGROUP_GameSoundGroup7 = 11,"
    "SOUNDGROUP_GameSoundGroup8 = 12,"
    "SOUNDGROUP_GameSoundGroup9 = 13,"
    "SOUNDGROUP_GameSoundGroup10 = 14,"
    "SOUNDGROUP_GameSoundGroup11 = 15,"
    "SOUNDGROUP_GameSoundGroup12 = 16,"
    "SOUNDGROUP_GameSoundGroup13 = 17,"
    "SOUNDGROUP_GameSoundGroup14 = 18,"
    "SOUNDGROUP_GameSoundGroup15 = 19,"
    "SOUNDGROUP_GameSoundGroup16 = 20,"
    "SOUNDGROUP_GameSoundGroup17 = 21,"
    "SOUNDGROUP_GameSoundGroup18 = 22,"
    "SOUNDGROUP_GameSoundGroup19 = 23,"
    "SOUNDGROUP_GameSoundGroup20 = 24,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDecompressionType = {"
    "DTYPE_Setup = 0,"
    "DTYPE_Invalid = 1,"
    "DTYPE_Preview = 2,"
    "DTYPE_Native = 3,"
    "DTYPE_RealTime = 4,"
    "DTYPE_Procedural = 5,"
    "DTYPE_Xenon = 6,"
    "DTYPE_Streaming = 7,"
    "DTYPE_MAX = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESoundWaveResourceState = {"
    "NeedsFree = 0,"
    "Freeing = 1,"
    "Freed = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBspNodeFlags = {"
    "NF_NotCsg = 1,"
    "NF_NotVisBlocking = 4,"
    "NF_BrightCorners = 16,"
    "NF_IsNew = 32,"
    "NF_IsFront = 64,"
    "NF_IsBack = 128,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPolyFlags = {"
    "PF_Invisible = 1,"
    "PF_NotSolid = 8,"
    "PF_Semisolid = 32,"
    "PF_GeomMarked = 64,"
    "PF_TwoSided = 256,"
    "PF_Portal = 67108864,"
    "PF_Memorized = 16777216,"
    "PF_Selected = 33554432,"
    "PF_HiddenEd = 134217728,"
    "PF_Hovered = 268435456,"
    "PF_EdProcessed = 1073741824,"
    "PF_EdCut = -2147483648,"
    "PF_NoEdit = -754974720,"
    "PF_NoImport = -754974720,"
    "PF_AddLast = 40,"
    "PF_NoAddToBSP = -754974720,"
    "PF_ModelComponentMask = 0,"
    "PF_DefaultFlags = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStreamingVolumeUsage = {"
    "SVB_Loading = 0,"
    "SVB_LoadingAndVisibility = 1,"
    "SVB_VisibilityBlockingOnLoad = 2,"
    "SVB_BlockingOnLoad = 3,"
    "SVB_LoadingNotVisible = 4,"
    "SVB_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFontHinting = {"
    "Default = 0,"
    "Auto = 1,"
    "AutoLight = 2,"
    "Monochrome = 3,"
    "None = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFontLoadingPolicy = {"
    "LazyLoad = 0,"
    "Stream = 1,"
    "Inline = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFontLayoutMethod = {"
    "Metrics = 0,"
    "BoundingBox = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFontFallback = {"
    "FF_NoFallback = 0,"
    "FF_LocalizedFallback = 1,"
    "FF_LastResortFallback = 2,"
    "FF_Max = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFontImportCharacterSet = {"
    "FontICS_Default = 0,"
    "FontICS_Ansi = 1,"
    "FontICS_Symbol = 2,"
    "FontICS_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFontCacheType = {"
    "Offline = 0,"
    "Runtime = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECanvasAllowModes = {"
    "Allow_Flush = 1,"
    "Allow_DeleteOnRender = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECanvasDrawMode = {"
    "CDM_DeferDrawing = 0,"
    "CDM_ImmediateDrawing = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EHandleBlockingHitResult = {"
    "Deflect = 0,"
    "AdvanceNextSubstep = 1,"
    "Abort = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPrecomputeState = {"
    "EInvalid = 0,"
    "EValid = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESkyLightSourceType = {"
    "SLS_CapturedScene = 0,"
    "SLS_SpecifiedCubemap = 1,"
    "SLS_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EHorizTextAligment = {"
    "EHTA_Left = 0,"
    "EHTA_Center = 1,"
    "EHTA_Right = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVerticalTextAligment = {"
    "EVRTA_TextTop = 0,"
    "EVRTA_TextCenter = 1,"
    "EVRTA_TextBottom = 2,"
    "EVRTA_QuadTop = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EReflectionSourceType = {"
    "CapturedScene = 0,"
    "SpecifiedCubemap = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESceneCapturePrimitiveRenderMode = {"
    "PRM_LegacySceneCapture = 0,"
    "PRM_RenderScenePrimitives = 1,"
    "PRM_UseShowOnlyList = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETimelineLengthMode = {"
    "TL_TimelineLength = 0,"
    "TL_LastKeyFrame = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDataTableExportFlags = {"
    "None = 0,"
    "UsePrettyPropertyNames = 1,"
    "UsePrettyEnumNames = 2,"
    "UseJsonObjectsForStructs = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EGetWorldErrorMode = {"
    "ReturnNull = 0,"
    "LogAndReturnNull = 1,"
    "Assert = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFullyLoadPackageType = {"
    "FULLYLOAD_Map = 0,"
    "FULLYLOAD_Game_PreLoadClass = 1,"
    "FULLYLOAD_Game_PostLoadClass = 2,"
    "FULLYLOAD_Always = 3,"
    "FULLYLOAD_Mutator = 4,"
    "FULLYLOAD_MAX = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETransitionType = {"
    "TT_None = 0,"
    "TT_Paused = 1,"
    "TT_Loading = 2,"
    "TT_Saving = 3,"
    "TT_Connecting = 4,"
    "TT_Precaching = 5,"
    "TT_WaitingToConnect = 6,"
    "TT_MAX = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConsoleType = {"
    "CONSOLE_Any = 0,"
    "CONSOLE_Mobile = 1,"
    "CONSOLE_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERotationSpace = {"
    "RelativeToElement = 0,"
    "RelativeToWorld = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EConsumeMouseWheel = {"
    "WhenScrollingPossible = 0,"
    "Always = 1,"
    "Never = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECheckBoxState = {"
    "Unchecked = 0,"
    "Checked = 1,"
    "Undetermined = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStyleMessageSeverity = {"
    "CriticalError = 0,"
    "Error = 1,"
    "PerformanceWarning = 2,"
    "Warning = 3,"
    "Info = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAutoCenter = {"
    "None = 0,"
    "PrimaryWorkArea = 1,"
    "PreferredWorkArea = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESizingRule = {"
    "FixedSize = 0,"
    "Autosized = 1,"
    "UserSized = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EReqLevelBlock = {"
    "BlockAlwaysLoadedLevelsOnly = 0,"
    "AlwaysBlock = 1,"
    "NeverBlock = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EPlatformInterfaceDataType = {"
    "PIDT_None = 0,"
    "PIDT_Int = 1,"
    "PIDT_Float = 2,"
    "PIDT_String = 3,"
    "PIDT_Object = 4,"
    "PIDT_Custom = 5,"
    "PIDT_MAX = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECloudStorageDelegate = {"
    "CSD_KeyValueReadComplete = 0,"
    "CSD_KeyValueWriteComplete = 1,"
    "CSD_ValueChanged = 2,"
    "CSD_DocumentQueryComplete = 3,"
    "CSD_DocumentReadComplete = 4,"
    "CSD_DocumentWriteComplete = 5,"
    "CSD_DocumentConflictDetected = 6,"
    "CSD_MAX = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAdManagerDelegate = {"
    "AMD_ClickedBanner = 0,"
    "AMD_UserClosedAd = 1,"
    "AMD_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMicroTransactionDelegate = {"
    "MTD_PurchaseQueryComplete = 0,"
    "MTD_PurchaseComplete = 1,"
    "MTD_MAX = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMicroTransactionResult = {"
    "MTR_Succeeded = 0,"
    "MTR_Failed = 1,"
    "MTR_Canceled = 2,"
    "MTR_RestoredFromServer = 3,"
    "MTR_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETwitterRequestMethod = {"
    "TRM_Get = 0,"
    "TRM_Post = 1,"
    "TRM_Delete = 2,"
    "TRM_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETwitterIntegrationDelegate = {"
    "TID_AuthorizeComplete = 0,"
    "TID_TweetUIComplete = 1,"
    "TID_RequestComplete = 2,"
    "TID_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESplitType = {"
    "SP_Coplanar = 0,"
    "SP_Front = 1,"
    "SP_Back = 2,"
    "SP_Split = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ELightMapFlags = {"
    "LMF_None = 0,"
    "LMF_Streamed = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextureRenderTargetFormat = {"
    "RTF_R8 = 0,"
    "RTF_RG8 = 1,"
    "RTF_RGBA8 = 2,"
    "RTF_R16f = 3,"
    "RTF_RG16f = 4,"
    "RTF_RGBA16f = 5,"
    "RTF_R32f = 6,"
    "RTF_RG32f = 7,"
    "RTF_RGBA32f = 8,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUserDefinedStructureStatus = {"
    "UDSS_UpToDate = 0,"
    "UDSS_Dirty = 1,"
    "UDSS_Error = 2,"
    "UDSS_Duplicate = 3,"
    "UDSS_MAX = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.AnimationKeyFormat = {"
    "AKF_ConstantKeyLerp = 0,"
    "AKF_VariableKeyLerp = 1,"
    "AKF_PerTrackCompression = 2,"
    "AKF_MAX = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAnimCurveType = {"
    "AttributeCurve = 0,"
    "MaterialCurve = 1,"
    "MorphTargetCurve = 2,"
    "MaxAnimCurveType = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMontagePlayReturnType = {"
    "MontageLength = 0,"
    "Duration = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EActorIteratorType = {"
    "End = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EActorIteratorFlags = {"
    "AllActors = 0,"
    "SkipPendingKill = 1,"
    "OnlySelectedActors = 2,"
    "OnlyActiveLevels = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAssetToLoad = {"
    "ATL_Regular = 0,"
    "ATL_Class = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EStrippedData = {"
    "None = 0,"
    "Editor = 1,"
    "Server = 2,"
    "All = 255,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateTextureAtlasPaddingStyle = {"
    "NoPadding = 0,"
    "DilateBorder = 1,"
    "PadWithZero = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateTextureAtlasThreadId = {"
    "Unknown = 0,"
    "Game = 1,"
    "Render = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EFontCacheAtlasDataType = {"
    "Regular = 0,"
    "Outline = 1,"
    "Num = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextShapingMethod = {"
    "Auto = 0,"
    "KerningOnly = 1,"
    "FullShaping = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EEnumerateGlyphsResult = {"
    "EnumerationFailed = 0,"
    "EnumerationAborted = 1,"
    "EnumerationComplete = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.Result = {"
    "Live = 0,"
    "Truncated = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.memory_order = {"
    "memory_order_relaxed = 0,"
    "memory_order_consume = 1,"
    "memory_order_acquire = 2,"
    "memory_order_release = 3,"
    "memory_order_acq_rel = 4,"
    "memory_order_seq_cst = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.errc = {"
    "address_family_not_supported = 102,"
    "address_in_use = 100,"
    "address_not_available = 101,"
    "already_connected = 113,"
    "argument_list_too_long = 7,"
    "argument_out_of_domain = 33,"
    "bad_address = 14,"
    "bad_file_descriptor = 9,"
    "bad_message = 104,"
    "broken_pipe = 32,"
    "connection_aborted = 106,"
    "connection_already_in_progress = 103,"
    "connection_refused = 107,"
    "connection_reset = 108,"
    "cross_device_link = 18,"
    "destination_address_required = 109,"
    "device_or_resource_busy = 16,"
    "directory_not_empty = 41,"
    "executable_format_error = 8,"
    "file_exists = 17,"
    "file_too_large = 27,"
    "filename_too_long = 38,"
    "function_not_supported = 40,"
    "host_unreachable = 110,"
    "identifier_removed = 111,"
    "illegal_byte_sequence = 42,"
    "inappropriate_io_control_operation = 25,"
    "interrupted = 4,"
    "invalid_argument = 22,"
    "invalid_seek = 29,"
    "io_error = 5,"
    "is_a_directory = 21,"
    "message_size = 115,"
    "network_down = 116,"
    "network_reset = 117,"
    "network_unreachable = 118,"
    "no_buffer_space = 119,"
    "no_child_process = 10,"
    "no_link = 121,"
    "no_lock_available = 39,"
    "no_message_available = 120,"
    "no_message = 122,"
    "no_protocol_option = 123,"
    "no_space_on_device = 28,"
    "no_stream_resources = 124,"
    "no_such_device_or_address = 6,"
    "no_such_device = 19,"
    "no_such_file_or_directory = 2,"
    "no_such_process = 3,"
    "not_a_directory = 20,"
    "not_a_socket = 128,"
    "not_a_stream = 125,"
    "not_connected = 126,"
    "not_enough_memory = 12,"
    "not_supported = 129,"
    "operation_canceled = 105,"
    "operation_in_progress = 112,"
    "operation_not_permitted = 1,"
    "operation_not_supported = 130,"
    "operation_would_block = 140,"
    "owner_dead = 133,"
    "permission_denied = 13,"
    "protocol_error = 134,"
    "protocol_not_supported = 135,"
    "read_only_file_system = 30,"
    "resource_deadlock_would_occur = 36,"
    "resource_unavailable_try_again = 11,"
    "result_out_of_range = 34,"
    "state_not_recoverable = 127,"
    "stream_timeout = 137,"
    "text_file_busy = 139,"
    "timed_out = 138,"
    "too_many_files_open_in_system = 23,"
    "too_many_files_open = 24,"
    "too_many_links = 31,"
    "too_many_symbolic_link_levels = 114,"
    "value_too_large = 132,"
    "wrong_protocol_type = 136,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.io_errc = {"
    "stream = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.event = {"
    "erase_event = 0,"
    "imbue_event = 1,"
    "copyfmt_event = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ValueType = {"
    "nullValue = 0,"
    "intValue = 1,"
    "uintValue = 2,"
    "realValue = 3,"
    "stringValue = 4,"
    "booleanValue = 5,"
    "arrayValue = 6,"
    "objectValue = 7,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.CommentPlacement = {"
    "commentBefore = 0,"
    "commentAfterOnSameLine = 1,"
    "commentAfter = 2,"
    "numberOfCommentPlacement = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.DuplicationPolicy = {"
    "noDuplication = 0,"
    "duplicate = 1,"
    "duplicateOnCopy = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.Kind = {"
    "kindNone = 0,"
    "kindIndex = 1,"
    "kindKey = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.TokenType = {"
    "tokenEndOfStream = 0,"
    "tokenObjectBegin = 1,"
    "tokenObjectEnd = 2,"
    "tokenArrayBegin = 3,"
    "tokenArrayEnd = 4,"
    "tokenString = 5,"
    "tokenNumber = 6,"
    "tokenTrue = 7,"
    "tokenFalse = 8,"
    "tokenNull = 9,"
    "tokenArraySeparator = 10,"
    "tokenMemberSeparator = 11,"
    "tokenComment = 12,"
    "tokenError = 13,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlideDirection = {"
    "None = 0,"
    "ComboButton = 1,"
    "TopMenu = 2,"
    "SubMenu = 3,"
    "TypeInPopup = 4,"
    "ContextMenu = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateTickType = {"
    "TimeOnly = 0,"
    "All = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EToolTipOffsetDirection = {"
    "Undetermined = 0,"
    "Down = 1,"
    "Right = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EUIActionRepeatMode = {"
    "RepeatDisabled = 0,"
    "RepeatEnabled = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EMultipleKeyBindingIndex = {"
    "Primary = 0,"
    "Secondary = 1,"
    "NumChords = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextHitPoint = {"
    "WithinText = 0,"
    "LeftGutter = 1,"
    "RightGutter = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ERunAttributes = {"
    "None = 0,"
    "SupportsText = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextWrappingPolicy = {"
    "DefaultWrapping = 0,"
    "AllowPerCharacterWrapping = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextFlowDirection = {"
    "Auto = 0,"
    "LeftToRight = 1,"
    "RightToLeft = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.Position = {"
    "Before = 0,"
    "After = 1,"
    "First = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EKeyboardType = {"
    "Keyboard_Default = 0,"
    "Keyboard_Number = 1,"
    "Keyboard_Web = 2,"
    "Keyboard_Email = 3,"
    "Keyboard_Password = 4,"
    "Keyboard_AlphaNumeric = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextEntryType = {"
    "TextEntryCanceled = 0,"
    "TextEntryAccepted = 1,"
    "TextEntryUpdated = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECursorMoveMethod = {"
    "Cardinal = 0,"
    "ScreenPosition = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECursorMoveGranularity = {"
    "Character = 0,"
    "Word = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECursorAction = {"
    "MoveCursor = 0,"
    "SelectText = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ETextLocation = {"
    "BeginningOfDocument = 0,"
    "EndOfDocument = 1,"
    "BeginningOfLine = 2,"
    "EndOfLine = 3,"
    "PreviousPage = 4,"
    "NextPage = 5,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVirtualKeyboardTrigger = {"
    "OnFocusByPointer = 0,"
    "OnAllFocusEvents = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EVirtualKeyboardDismissAction = {"
    "TextChangeOnDismiss = 0,"
    "TextCommitOnAccept = 1,"
    "TextCommitOnDismiss = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAllowOverscroll = {"
    "Yes = 0,"
    "No = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EListItemAlignment = {"
    "EvenlyDistributed = 0,"
    "EvenlySize = 1,"
    "EvenlyWide = 2,"
    "LeftAligned = 3,"
    "RightAligned = 4,"
    "CenterAligned = 5,"
    "Fill = 6,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EScrollIntoViewResult = {"
    "Success = 0,"
    "Deferred = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EHeaderComboVisibility = {"
    "Always = 0,"
    "Ghosted = 1,"
    "OnHover = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDescendantScrollDestination = {"
    "IntoView = 0,"
    "TopOrLeft = 1,"
    "Center = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EParseState = {"
    "Continue = 0,"
    "StopAfter = 1,"
    "StopBefore = 2,"
    "Cancel = 3,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EAssociativity = {"
    "RightToLeft = 0,"
    "LeftToRight = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ECommitMethod = {"
    "CommittedViaSpin = 0,"
    "CommittedViaTypeIn = 0,"
    "CommittedViaArrowKey = 0,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EWindowPlacement = {"
    "Placement_NoWindow = 0,"
    "Placement_Automatic = 1,"
    "Placement_Specified = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.pointer_safety = {"
    "relaxed = 0,"
    "preferred = 1,"
    "strict = 2,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.ESlateVisibility = {"
    "Visible = 0,"
    "Collapsed = 1,"
    "Hidden = 2,"
    "HitTestInvisible = 3,"
    "SelfHitTestInvisible = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EBindingKind = {"
    "Function = 0,"
    "Property = 1,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.EDesignPreviewSizeMode = {"
    "FillScreen = 0,"
    "Custom = 1,"
    "CustomOnScreen = 2,"
    "Desired = 3,"
    "DesiredOnScreen = 4,"
"}";

state->initInnerCode(s);
} {
char s[] = 

"UEnums.LogLevel = {"
    "LL_Log = 0,"
    "LL_Debug = 1,"
    "LL_Warning = 2,"
    "LL_Error = 3,"
"}";

state->initInnerCode(s);
}
