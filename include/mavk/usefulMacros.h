/*
	MAVK header file: This file contains useful macros for mavk.
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

#if !defined(MAVK_HEADER_USEFUL_MACROS)
#define MAVK_HEADER_USEFUL_MACROS

#if defined(DEBUG) && !defined(NDEBUG)
	#define MAVK_DEBUG
	#include <stdio.h>
#endif

#define MAVK_DECL
#define MAVK_IMPL

#define MAVK_OK 0

#define MAVK_TRUE 1
#define MAVK_FALSE 0

#if defined(MAVK_DEBUG)
	#define MAVK_DEBUG_MSG(str) puts(str)
	#define MAVK_DEBUG_ERR(str, err) puts(str); exit(err)
#else
	#define MAVK_DEBUG_MSG(str)
	#define MAVK_DEBUG_ERR(str, err)
#endif


#endif /* HEADER GUARD */
