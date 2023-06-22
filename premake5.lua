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

-- When calling premake5 on a unix-like system, make sure to use the --wm=XXX option.
-- Note: this file assumes if the --wm option is not set, then x11 is used as default.
newoption({
	trigger = "wm",
	description = "Applies to unix systems only. Spicifies if using x11 or wayland",
	allowed = {
		{"x11", "X11"},
		{"wayland", "Wayland"}
	},
	catagory = "Build Options"
})


-- Like above, if you are using GLFW, make sure to use the --using-glfw option.
-- By default GLFW is not enabled.
newoption({
	trigger = "using-glfw",
	description = "Spicify if using glfw for window creation"
})

project("mavk")
	language "C"
	cdialect "C17"
	kind "StaticLib"
	files {"**.c", "**.h"}
	includedirs {"include"}

	objdir    "bin-int/%{cfg.system}-%{cfg.buildcfg}"
	targetdir "bin/%{cfg.system}-%{cfg.buildcfg}"

	filter "configurations:debug"
		defines {"DEBUG"}
		targetname "mavk-debug"

	filter "configurations:ndebug"
		defines {"NDEBUG"}
		targetname "mavk"


	-- define platform macro
	defines {"MAVK_PLATFORM_" .. string.upper(os.target())}

	-- define window manager (if necessary)
	filter {"system:linux or bsd", "not options:wm"}
		defines {"MAVK_PLATFORM_X11"}
		objdir    "bin-int/%{cfg.system}-x11-%{cfg.buildcfg}"
		targetdir "bin/%{cfg.system}-x11-%{cfg.buildcfg}"

	filter {"system:linux or bsd", "options:wm=x11"}
		defines {"MAVK_PLATFORM_X11"}
		objdir    "bin-int/%{cfg.system}-x11-%{cfg.buildcfg}"
		targetdir "bin/%{cfg.system}-x11-%{cfg.buildcfg}"

	filter {"system:linux or bsd", "options:wm=wayland"}
		defines {"MAVK_PLATFORM_WAYLAND"}
		objdir    "bin-int/%{cfg.system}-wl-%{cfg.buildcfg}"
		targetdir "bin/%{cfg.system}-wl-%{cfg.buildcfg}"
	filter ""


	-- if 'using-glfw' is set, define the thing
	filter "options:using-glfw"
		defines {"MAVK_PLATFORM_GLFW"}
	
	filter ""
-- project end
