#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>

extern uint32_t g_width;
extern uint32_t g_height;
extern float g_aspect;

// 함수 선언
int printAllErrors(const char * caption = nullptr);
const char * getGLErrorStr(GLenum err);
void initContext(bool useDefault, int major = 3, int minor = 3, bool useCompatibility = false);
void framebufferSizeCallback(GLFWwindow*, int w, int h);
void cursorPosCallback(GLFWwindow* window, double x, double y);
