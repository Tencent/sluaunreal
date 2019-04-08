## lua-wrapper 是什么？

lua-wrapper 是 slua-unreal 的静态代码导出工具，主要功能是将非蓝图类型生成 lua 接口导入 unreal4 中，该工具采用 c# 开发，.Net framework 是 4.6.2，依赖两个库，Newtonsoft.Json 11.0.2 和 libclang 5.0.0（32位），运行前请自行下载。

lua-wrapper is a static code export tool in slua-unreal. The main job is to statically export non-blueprint types in unreal4 to interfaces that conform to lua calls. The tool is written in C#, the target .Net framework is 4.6.2, the tool runs. Depends on two dynamic libraries, Newtonsoft.Json 11.0.2 (.net framework 4.6.2) and libclang 5.0.0 (32-bit version), please download and install them before running.

## lua-wrapper 的作用范围是什么？

lua-wrapper 是作为 slua-unreal 中 lua 导出接口的补充，slua-unreal 支持 3 种接口导出的方式：
1. 反射，凡是支持 blueprint 的类型，都可以直接在 lua 中通过反射的形式访问
2. LuaCppbinding，通过 C++ 模版的自动推导导出 lua 接口
3. lua-wrapper，通过静态代码生成导出以上两种方式不支持的接口

所以，lua-wrapper 的作用范围是：
1. 不支持导出自定义类型
2. 不支持导出可反射的类型
3. 导出类型限定于引擎中的 USTRUCT 类型
4. 优先使用反射或者 LuaCppBinding 导出类型，最后才考虑使用 lua-wrapper
5. 如果 lua-wrapper 导出的类型编译错误，说明不支持导出该类型，参考第 4 条

lua-wrapper is a supplement to the lua export interface in slua-unreal, which supports three types of interface export:
1. Reflection, any type that supports blueprint can be accessed directly in lua by reflection
2. LuaCppbinding, exporting lua interface through automatic derivation of C++ template
3. lua-wrapper, through the static code generation to export the interface that is not supported by the above two methods

so, the scope of lua-wrapper is:
1. Exporting custom types is not supported
2. Exporting reflective types is not supported
3. The export type is limited to the USTRUCT type in the engine
4. Use reflection or LuaCppBinding to export the type first, and finally consider using lua-wrapper
5. If the type exported by lua-wrapper is compiled incorrectly, it means that exporting the type is not supported. See Article 4.

## 如何导出自定义接口？

lua-wrapper 可运行于 windows 和 mac 平台，slua-unreal 自带了一份已经生成好的文件，但是可能还不够，如果需要导出更多的类型，不管是 unreal 的类型，还是自定义的类型，请修改 Tools 目录下的 config*.json 文件，找到 "Customs" 字段，指定类型和该类型所在的文件，然后导出。注意，编译结果依赖于配置是否正确，如果发现没有正确生成预期的结果，请检查配置。

lua-wrapper runs on windows and mac platforms. slua-unreal already has a generated file, but it may not be enough, if you need to export more types, whether it is unreal4 or a custom type, please modify the config*.json file in the "Tools" directory, find the "Customs" field, specify the type and file of the type, then export. Note, that the results depend on whether the configuration is correct, if you find the results are not generated correctly, check the configuration (see the config.json) .

## 依赖

Newtonsoft.Json 11.0.02 (.net framework 4.6.2)
libclang 5.0.0 (32 bit)

## 配置文件

config.json

配置文件主要配置两部分信息：
1. 编译参数相关信息：引擎和项目路径、预处理器
2. 指定导出类型信息

字段含义：
* solution_dir: slua 项目路径
* ue4_dir: ue4 安装路径
* ue_vcproj: slua c++ 工程路径
* output_dir: LuaWrapper.cpp 输出目录
* filter: 过滤器，可指定类型的方法不导出
* struct_files: "TBaseStructure" 默认导出，"Custom" 可自主添加
* include_path: 搜索路径
* preprocess: 预处理器

The config file contains two parts of information:
1. compile parameter related information: engine and project path, preprocessor
2. specify export type information

Field meaning:
* solution_dir: slua project path
* ue4_dir: ue4 installation path
* ue_vcproj: slua c++ project path
* output_dir: LuaWrapper.cpp output dir
* filter: specify which methd is not exported in a type
* struct_files: "TBaseStructure" default export, "Custom" can be added by yourself
* include_path: include path
* preprocess: preprocessor