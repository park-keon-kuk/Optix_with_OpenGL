#pragma once

#define NOMINMAX
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_stream_namespace.h>

class MyOptix
{
	RTcontext m_context = nullptr;

public:
	MyOptix();
	virtual ~MyOptix();
};