/*
* Copyright (c) 2018 NVIDIA CORPORATION. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*  * Neither the name of NVIDIA CORPORATION nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <optix_cuda.h>

using namespace optix;

// 변수
rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtDeclareVariable(float3, draw_color, , );

// 버퍼
rtBuffer<float4, 2>   result_buffer;

// Ray Gen
RT_PROGRAM void draw_solid_color()
{
	size_t2 size = result_buffer.size();
	float3 color = make_float3(0, 0, 0);

	if (launch_index.x > 50 && launch_index.x < 100
		&& launch_index.y > 50 && launch_index.y < 100) 
	{
		color = make_float3(1, 0, 0);
	}

	result_buffer[launch_index] = make_float4(color, 0.f);
}

// Exception
RT_PROGRAM void exception()
{
	const unsigned int code = rtGetExceptionCode();
	rtPrintf("Caught exception 0x%X at launch index (%d,%d)\n", code, launch_index.x, launch_index.y);
	result_buffer[launch_index] = make_float4(0.f, 0.f, 0.f, 0.f);
}