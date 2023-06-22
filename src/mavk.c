/*
	MAVK header file: This file contains the main source definitions for mavk.
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
*/

#include "mavk/mavk.h"

static VkInstance s_instance;

/* Instance types & functions */
//MAVK_IMPL static {

}
MAVK_IMPL MavkCreateInstance mavkCreateInstanceDefault(){
	MavkCreateInstance ci;
	ci.usingSurface = MAVK_TRUE;
	return ci;
}
MAVK_IMPL MavkResult mavkCreateInstance(MavkCreateInstance *p){
	VkApplicationInfo ai;
	ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ai.pNext = NULL;
	ai.pApplicationName = "mavk";
	ai.applicationVersion = VK_MAKE_VERSION(MAVK_VERSION_MAJOR, MAVK_VERSION_MINOR, MAVK_VERSION_PATCH);
	ai.pEngineName = MAVK_VERSION_NAME;
	ai.engineVersion = VK_MAKE_VERSION(MAVK_VERSION_MAJOR, MAVK_VERSION_MINOR, MAVK_VERSION_PATCH);

	VkInstanceCreateInfo ici;
	ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ici.pNext = NULL;
	if (p->usingSurface){
		ici.enabledExtensionCount = 2;
		ici.pEnabledExtensions = {
			"VK_KHR_surface",
			#if defined(MAVK_PLATFORM_X11)
				"VK_KHR_xcb_surface"
			#elif defined(MAVK_PLATFORM_WAYLAND)
				"VK_KHR_wayland_surface"
			#elif defined(MAVK_PLATFORM_WINDOWS)
				"VK_KHR_win32_surface"
			#endif
		};
	}

	#if !defined(NDEBUG)
		ici.enabledLayerCount = 1;
		ici.pEnabledLayers = {"VK_LAYER_KHRONOS_validation"};
	#else
		ici.enabledLayerCount = 0;
		ici.pEnabledLayers = NULL;
	#endif

	ici.pAppicationInfo = &ai;

	return VkCreateInstance(&ici, NULL, &s_instance);
	
}
MAVK_IMPL VkInstance mavkGetInstance(){
	return s_instance;
}


/* I dont know where esle to put these :) */
MAVK_IMPL void mavkDestroy(){
	
}
