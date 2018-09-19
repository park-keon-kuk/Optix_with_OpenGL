#include "gui.h"
#include <cstdio>

/********************************************/
// Global Variable
/********************************************/

uint32_t g_width;
uint32_t g_height;
float g_aspect;



/********************************************/
// Functions
/********************************************/

void framebufferSizeCallback(GLFWwindow*, int w, int h)
{
	g_width = w;
	g_height = h == 0 ? 1 : h;

	g_aspect = (float)g_width / (float)g_height;
}

void cursorPosCallback(GLFWwindow * window, double x, double y)
{
	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{

	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{

	}
}

void initContext(bool useDefault, int major, int minor, bool useCompatibility)
{
	if (useDefault)
	{
		// 기본적으로  Default로 설정해주면
		// 가능한 최신의 OpenGL Vesion을 선택하며 (연구실 컴퓨터는 4.5)
		// Profile은 Legacy Function도 사용할 수 있게 해줍니다.(Compatibility 사용)
		glfwDefaultWindowHints();
	}
	else
	{
		// Major 와 Minor 결정
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

		// Core 또는 Compatibility 선택
		if (useCompatibility)
		{
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		}
		else
		{
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
	}
}

int printAllErrors(const char * caption /*= nullptr*/)
{
	if (caption)
		puts(caption);

	int err;
	int err_count = 0;

	do {
		// 에러 출력
		err = glGetError();
		printf(" Error: %s\n", getGLErrorStr(err));
		err_count++;
	} while (err != GL_NO_ERROR);

	return err_count - 1;
}

const char * getGLErrorStr(GLenum err)
{
	switch (err)
	{
	case GL_NO_ERROR:          return "No error";
	case GL_INVALID_ENUM:      return "Invalid enum";
	case GL_INVALID_VALUE:     return "Invalid value";
	case GL_INVALID_OPERATION: return "Invalid operation";
	case GL_STACK_OVERFLOW:    return "Stack overflow";
	case GL_STACK_UNDERFLOW:   return "Stack underflow";
	case GL_OUT_OF_MEMORY:     return "Out of memory";
	default:                   return "Unknown error";
	}
}