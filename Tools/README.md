## lua-wrapper 是什么？

lua-wrapper 是 slua-unreal 的静态代码导出工具，主要功能是将非蓝图类型生成 lua 接口导入 unreal4 中，该工具采用 c# 开发，.Net framework 是 4.6.2，依赖两个库，Newtonsoft.Json 11.0.2 和 libclang（32位），运行前请自行下载。

lua-wrapper is a static code export tool in slua-unreal. The main job is to statically export non-blueprint types in unreal4 to interfaces that conform to lua calls. The tool is written in C#, the target .Net framework is 4.6.2, the tool runs. Depends on two dynamic libraries, Newtonsoft.Json 11.0.2 (.net framework 4.6.2) and libclang (32-bit version), please download and install them before running.

## 如何导出自定义接口？

lua-wrapper 可运行于 windows 和 mac 平台，slua-unreal 自带了一份已经生成好的文件，但是可能还不够，如果需要导出更多的类型，不管是 unreal 的类型，还是自定义的类型，请修改 Tools 目录下的 config*.json 文件，找到 "Customs" 字段，指定类型和该类型所在的文件，然后导出即可。

lua-wrapper runs on windows and mac platforms. slua-unreal already has a generated file, but it may not be enough, if you need to export more types, whether it is unreal4 or a custom type, please modify the config*.json file in the "Tools" directory, find the "Customs" field, specify the type and file of the type, then export.