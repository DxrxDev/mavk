/*
	MAVK header file: This file contains the main include for mavk.
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

#if !defined(MAVK_HEADER_DEFINED)
#define MAVK_HEADER_DEFINED

#include <stdint.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#include "version.h"
#include "usefulMacros.h"


/* Define some general types */
typedef uint32_t MavkResult;
typedef uint32_t MavkBool;


/* Instance types & functions */
typedef struct MavkCreateInstance{
	MavkBool usingSurface;
} MavkCreateInstance;

MAVK_DECL MavkCreateInstance mavkCreateInstanceDefault();
MAVK_DECL MavkResult mavkCreateInstance(MavkCreateInstance *p);
MAVK_DECL VkInstance mavkGetInstance();


/* I dont know where esle to put these :) */
MAVK_DECL void mavkDestroy();


#endif /* HEADER GUARD */
