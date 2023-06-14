--[[ 
	MAVK premake5 file: This file contains the premake5 script for mavk.
	   ^ (Minimal Abstraction for Vulkan)

	=== (LICENSE) ===

	BSD 2-Clause License

	Copyright (c) 2023 - present, DxrxDev <DxrxMa@gmail.com>

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
   	this list of conditions and the following disclaimer in the documentation
   	and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--]]


-- [[ PLATFORM ]]
-- This file contains functionality for automatically detecting the OS and window
-- managers, however it is possible to feed that information manually
-- (call premake5 [intended build system] --os=XXX)
platformMacro = nil

-- [[ WINDOW MANAGER ]]
-- This only applies to unix like systems. windowManager tells mavk wether
-- you are running off of Xorg or Wayland. again this can detect automatically.
-- (to give custom value, add to the main premake5 file `windowManager = XXX`)

-- [[ THIRD PARTY ]]
-- If you are using a third party for window/surface creation, spicify
-- `thirdParty = "XXX"` in the main premake5 file. Mavk does NOT automatically detect this.


-- Function to detect the platform
function GetPlatform()
	platformMacro = "MAVK_PLATFORM_" .. string.upper(os.target())
	defines {paltformMacro}
	print("mavk: defined macro " .. platformMacro)
end

-- Function to detect window manager
function GetWindowManager()
	local handle = io.popen("echo $XDG_SESSION_TYPE")
	if handle:read("l") == "x11" then
		windowManager = "MAVK_PLATFORM_X11"
	else
		windowManager = "MAVK_PLATFORM_WAYLAND"
	end
	handle:close()

	defines {windowManager}
	print("mavk: defined macro " .. windowManager)
end

-- Function to set window manager
function SetWindowManager()
	windowManager = "MAVK_PLATFORM_" .. string.upper(windowManager)
	defines {windowManager}
	print("mavk: defined macro " .. windowManager)
end

-- Function to define third party APIs
function DefineThirdParty()
	thirdParty = "MAVK_PLATFORM_" .. string.upper(thirdParty)
	defines {thirdParty}
	print("mavk: defined macro " .. thirdParty)
end


project "mavk"
	language "C"
	cdialect "C17"
	kind "StaticLib"
	files {"src/*.c"}

	-- This code is all in regular lua as premake5 does not
	-- offer all these tools out the box
	GetPlatform()

	if (os.target() == "linux" or os.target() == "bsd") and windowManager == nil then
		GetWindowManager()
	else	SetWindowManager()  end

	if thirdParty ~= nil then DefineThirdParty() end

	-- Back to regular premake5
	filter {"configurations:debug"}
		defines {"DEBUG"}
		targetdir "./bin/debug/"
		objdir "./bin-int/debug/"
	filter {"configurations:ndebug"}
		defines {"NDEBUG"}
		targetdir "./bin"
		objdir "./bin-int/"

	filter ""

