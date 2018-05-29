x86\lua test.lua
x64\lua test.lua

x86\luac -o x86\test.luac test.lua
x64\luac -o x64\test.luac test.lua

x86\lua x86\test.luac
x64\lua x64\test.luac

x86\lua x64\test.luac
x64\lua x86\test.luac
