-- test cpp binding
local f1=Foo(1024)
local str=Foo.getStr()
-- f2 not collect
local f2=Foo.getInstance()
f1:bar(str)
f2:bar(str)
-- call base function
f1:baseFunc1()

local f3=FooChild(2048)
f3:virtualFunc()
f3:bar("f3")
f3:baseFunc1()
-- f3 is a FooChild, but pushed as Foo
-- should downcast to Foo, but how to do it?
-- local f3 = slua.cast(f3,Foo)
-- f3:fooChildFunc1()