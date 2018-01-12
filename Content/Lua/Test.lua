
local B=require 'b'

print("test require",B.foo())

local Test=import('SluaTestCase');
local t=Test();

print(t:GetWidget())

-- test
for i=1,10 do
    local arr=t:GetArray();
    print("arr len",arr:Num())
    for i=0,arr:Num()-1 do
        print("arr item",i,arr:Get(i))
    end
end

local Button = import('Button');
-- local ButtonStyle = import('ButtonStyle');
-- local TextBlock = import('TextBlock');
local btn=Button();
-- local txt=TextBlock();
local ui=loadUI('/Game/Panel.Panel');
ui:AddToViewport(0);
-- local seq=ui.ActiveSequencePlayers;
-- print('seq',seq:Num());
local tree=ui.WidgetTree;
local btn2=tree:FindWidget('Button1');
local index = 1

btn2.OnClicked:Add(function() 
    index=index+1
    print('fuck',index) 
end);
local edit=tree:FindWidget('TextBox_0');
-- local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
-- edit.OnTextChanged:Remove(evt);
-- txt:SetText('fuck button');
-- local style=ButtonStyle();
-- btn:SetStyle(style);
-- btn:AddChild(txt);
-- print(btn:IsPressed(),btn.OnClicked);
-- local event=btn.OnClicked;
-- local index=1
-- event:Add(function() 
--     index=index+1
--     print('fuck',index) 
-- end);

function update(dt)
    -- test memory leak?
    local arr=t:GetArray();
    -- print("arr len",arr:Num())
    for i=0,arr:Num()-1 do
         -- print("arr item",i,arr:Get(i))
    end

    local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
    edit.OnTextChanged:Remove(evt);
    -- test free event twice
    edit.OnTextChanged:Remove(evt);
end
