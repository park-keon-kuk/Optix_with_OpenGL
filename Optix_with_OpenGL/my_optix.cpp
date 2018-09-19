#include "my_optix.h"
#include "gui.h"

MyOptix::MyOptix()
{
	if (m_context)
		return;

	rtContextCreate(&m_context);
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
