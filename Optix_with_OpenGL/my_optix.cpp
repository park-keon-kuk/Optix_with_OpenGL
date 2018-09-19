#include "my_optix.h"

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
