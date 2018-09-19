#pragma once

#define NOMINMAX
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_stream_namespace.h>

class MyOptix
{
	RTcontext m_context = nullptr;
	RTbuffer m_buffer = nullptr;
	RTprogram m_program = nullptr;
	RTvariable m_result_buffer = nullptr;
	RTvariable m_draw_color = nullptr;

	GLuint m_opengl_texture_id = 0;

public:
	MyOptix();
	virtual ~MyOptix();

	void launch();
	void update_opengl_texture();
	void render();
};