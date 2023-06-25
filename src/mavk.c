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
#include <vulkan/vulkan.h>

#if !defined(NDEBUG)
#include <stdio.h>
#endif

/* Note: s_ is for static variables, sf_ is for static functions */
static VkInstance s_instance;

static VkPhysicalDevice *s_pDevices;
static uint32_t s_pDeviceCount;



/*** INSTANCE RELATED SECTION ***/

#if !defined(NDEBUG)
static VkDebugUtilsMessengerEXT s_debugMsg;
MAVK_IMPL static VKAPI_ATTR VkBool32 VKAPI_CALL sf_mavkDebugCallbackFunction(
	VkDebugUtilsMessageSeverityFlagBitsEXT _severity,
	VkDebugUtilsMessageTypeFlagsEXT _type,
	const VkDebugUtilsMessengerCallbackDataEXT* _data,
	void* _uData) {

    printf("validation layer: %s\n", _data->pMessage);

    return VK_FALSE;
}

MAVK_IMPL static void sf_mavkDebugCallback(){
	/* Setting up the callback function. only detecting warnings and errors */
	VkDebugUtilsMessengerCreateInfoEXT dumci;
	dumci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	dumci.pNext = NULL;
	dumci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	dumci.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	dumci.pfnUserCallback = sf_mavkDebugCallbackFunction;
	dumci.pUserData = NULL;

	PFN_vkCreateDebugUtilsMessengerEXT fun = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(s_instance, "vkCreateDebugUtilsMessengerEXT");
	if (fun == NULL) {
		puts("Couldnt set up the debug callback: :/\n"); return;
	}

	VkResult res = fun(s_instance, &dumci, NULL, &s_debugMsg);

	printf("Created debug callback messenger with result %i\n", res);
}
#endif

MAVK_IMPL MavkCreateInstance mavkCreateInstanceDefault(){
	MavkCreateInstance ci;
	ci.usingSurface = MAVK_TRUE;
	return ci;
}
MAVK_IMPL MavkResult mavkCreateInstance(MavkCreateInstance *_p){
	/* Debug parameter checking */
	#if !defined(NDEBUG)
		if (_p == NULL){
			puts("passed NULL variable into mavkCreateInstance!");
		}
	#endif

	/* App info */
	VkApplicationInfo ai;
	ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ai.pNext = NULL;
	ai.pApplicationName = "mavk";
	ai.applicationVersion = VK_MAKE_VERSION(MAVK_VERSION_MAJOR, MAVK_VERSION_MINOR, MAVK_VERSION_PATCH);
	ai.pEngineName = MAVK_VERSION_NAME;
	ai.engineVersion = VK_MAKE_VERSION(MAVK_VERSION_MAJOR, MAVK_VERSION_MINOR, MAVK_VERSION_PATCH);


	/* Now for some instance creation wizardry */
	VkInstanceCreateInfo ici;
	ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ici.pNext = NULL;

	// I will leave these definitions here for convenience
	const char *enabledExtensions[] = {
		"VK_KHR_surface",
		#if defined(MAVK_PLATFORM_X11)
			"VK_KHR_xcb_surface",
		#elif defined(MAVK_PLATFORM_WAYLAND)
			"VK_KHR_wayland_surface",
		#elif defined(MAVK_PLATFORM_WINDOWS)
			"VK_KHR_win32_surface",
		#endif

		#if !defined(NDEBUG)
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME
		#endif

	};
	const char *enabledLayers[] = {
		"VK_LAYER_KHRONOS_validation"
	};

	if (_p->usingSurface){
		ici.enabledExtensionCount = sizeof(enabledExtensions) / sizeof(char *);
		ici.ppEnabledExtensionNames = (const char *const *)enabledExtensions;
	}

	ici.ppEnabledLayerNames = (const char * const*)enabledLayers;
	#if !defined(NDEBUG)
		ici.enabledLayerCount = 1;
	#else
		ici.enabledLayerCount = 0;
	#endif

	ici.pApplicationInfo = &ai;

	/* :) */
	VkResult res = vkCreateInstance(&ici, NULL, &s_instance);

	#if !defined(NDEBUG)
		sf_mavkDebugCallback();
	#endif

	return res;
}
MAVK_IMPL VkInstance mavkGetInstance(){
	return s_instance;
}
MAVK_IMPL void mavkSetInstance(VkInstance _inst){
	s_instance = _inst;
}


/*** DEVICE RELATED SECTION ***/



/* I dont know where esle to put these :) */
MAVK_IMPL void mavkDestroy(){
	#if !defined(NDEBUG)
	
	PFN_vkDestroyDebugUtilsMessengerEXT fun = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(s_instance, "vkDestroyDebugUtilsMessengerEXT");
	if (fun != NULL){fun(s_instance, s_debugMsg, NULL);}	
	
	#endif	


	vkDestroyInstance(s_instance, NULL);
}
