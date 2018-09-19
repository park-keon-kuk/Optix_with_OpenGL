#include "gui.h"
#include "my_optix.h"

int main()
{
	MyOptix * my_optix;

	/* â �ʱ�ȭ, ���� �ڵ鸵 ���, �̺�Ʈ �ݹ� ���, OpenGL �ʱ�ȭ */
	/* -------------------------------------------------------------------------------------- */
	glfwInit();
	glfwSetErrorCallback([](int err, const char* desc) { puts(desc); });
	initContext(/*use dafault = */ true);
	GLFWwindow *window = glfwCreateWindow(g_width, g_height, "Optix!!", nullptr, nullptr);
	framebufferSizeCallback(window, 512, 512);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwMakeContextCurrent(window);
	glewInit();

	/* ��ü ���� */
	/* -------------------------------------------------------------------------------------- */
	my_optix = new MyOptix();


	/* �ʱ�ȭ */
	/* -------------------------------------------------------------------------------------- */


	/* ���� ���� */
	/* -------------------------------------------------------------------------------------- */
	while (!glfwWindowShouldClose(window))
	{
		// �̺�Ʈ �ڵ鸵
		/* -------------------------------------------------------------------------------------- */
		glfwPollEvents();


		// GO TO
		/* -------------------------------------------------------------------------------------- */
		my_optix->launch();
		my_optix->render();


		// ���� ����
		/* -------------------------------------------------------------------------------------- */
		glfwSwapBuffers(window);
	}


	// ��ü ����
	/* -------------------------------------------------------------------------------------- */
	delete my_optix;


	// ����
	/* -------------------------------------------------------------------------------------- */
	glfwTerminate();
}