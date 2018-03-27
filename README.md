# slua-unreal

Now slua for unreal available.

# Feature

* Export all blueprint interface to lua via refection by Unreal4.
* Lua function passed as callback of blueprint.
* Common c++ class (Non blueprint class) can be exported by static code generation by libclang tool( another tool available ASAP )

# Usage at a glance

```lua
local Button = import('Button');
local ButtonStyle = import('ButtonStyle');
local TextBlock = import('TextBlock');
local btn=Button();
local txt=TextBlock();
local ui=slua.loadUI('/Game/Panel.Panel');
ui:AddToViewport(0);
local tree=ui.WidgetTree;
local btn2=tree:FindWidget('Button1');
local index = 1

btn2.OnClicked:Add(function() 
    index=index+1
    print('fuck',index) 
end);
local edit=tree:FindWidget('TextBox_0');
local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
```

