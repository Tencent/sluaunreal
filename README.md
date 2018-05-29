# slua-unreal

Now slua for unreal available.

# Feature

* Export all blueprint interface to lua via refection by Unreal4.
* Lua function passed as callback of blueprint.
* Common c++ class (Non blueprint class) can be exported by static code generation by libclang tool( another tool available ASAP )
* support operator overloading for FVector etc.
* support extension-method mechanism for some non blueprint function in blueprint class, like GetWidgetFromName of UUserWidget

# Usage at a glance

```lua
-- import blueprint class to use
local Button = import('Button');
local ButtonStyle = import('ButtonStyle');
local TextBlock = import('TextBlock');
-- create Button
local btn=Button();
local txt=TextBlock();
-- load panel of blueprint
local ui=slua.loadUI('/Game/Panel.Panel');
-- add to show
ui:AddToViewport(0);
-- find sub widget from the panel
local tree=ui.WidgetTree;
local btn2=tree:FindWidget('Button1');
local index = 1
-- handle click event
btn2.OnClicked:Add(function() 
    index=index+1
    print('fuck',index) 
end);
-- handle text changed event
local edit=tree:FindWidget('TextBox_0');
local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);

-- use FVector
local p = actor:K2_GetActorLocation()
local h = HitResult()
local v = FVector(math.sin(tt)*100,2,3)
local offset = FVector(0,math.cos(tt)*50,0)
-- support Operator
local ok,h=actor:K2_SetActorLocation(v+offset,true,h,true)
-- get referenced value
print("hit info",h)
```

