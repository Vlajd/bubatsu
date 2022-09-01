copy .\premake\glad.lua .\Bubatsu\extern\glad\premake5.lua
copy .\premake\glfw.lua .\Bubatsu\extern\glfw\premake5.lua
copy .\premake\imgui.lua .\Bubatsu\extern\imgui\premake5.lua
copy .\premake\main.lua .\premake5.lua

call .\extern\premake\premake5.exe vs2022

PAUSE
