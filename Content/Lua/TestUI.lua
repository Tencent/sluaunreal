
local Button = import('Button');
local ButtonStyle = import('ButtonStyle');
local TextBlock = import('TextBlock');
local btn=Button();
local txt=TextBlock();
local ui=slua.loadUI('/Game/Panel.Panel');
ui:AddToViewport(0);
local seq=ui.ActiveSequencePlayers;
print('seq',seq:Num());
local btn2=ui:FindWidget('Button1');
local index = 1
btn2.OnClicked:Add(function() 
    index=index+1
    print('say helloworld',index) 
end);
local edit=ui:FindWidget('TextBox_0');
local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
txt:SetText('helloworld button');
local style=ButtonStyle();
btn:SetStyle(style);
btn:AddChild(txt);
print(btn:IsPressed(),btn.OnClicked);
local event=btn.OnClicked;
local index=1
event:Add(function() 
    index=index+1
    print('helloworld',index) 
end);