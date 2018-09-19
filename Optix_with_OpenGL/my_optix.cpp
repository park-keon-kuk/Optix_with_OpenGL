#include "my_optix.h"
#include "gui.h"

MyOptix::MyOptix()
{
	if (m_context)
		return;

	RTprogram pinhole_camera = nullptr;
	RTprogram thin_lens_camera = nullptr;
	RTprogram exception = nullptr;

	rtContextCreate(&m_context);
	rtContextSetEntryPointCount(m_context, 2);
	rtContextSetPrintEnabled(m_context, 1); // 0 is disable, otherwise enable.
	rtContextSetPrintBufferSize(m_context, 4096);

	rtContextSetRayGenerationProgram(m_context, 0, pinhole_camera);
	rtContextSetRayGenerationProgram(m_context, 1, thin_lens_camera);

	rtContextSetExceptionProgram(m_context, 0, exception);
	rtContextSetExceptionProgram(m_context, 1, exception);
}

MyOptix::~MyOptix()
{
	if (!m_context)
		return;

	rtContextDestroy(m_context);
	m_context = nullptr;
}

void MyOptix::launch()
{
	rtContextLaunch2D(m_context, 0, g_width, g_height);
}

void MyOptix::render()
{
}
