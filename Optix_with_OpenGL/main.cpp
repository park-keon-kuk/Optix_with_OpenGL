#include "gui.h"
#include "my_optix.h"

int main()
{
	/* â �ʱ�ȭ, ���� �ڵ鸵 ���, �̺�Ʈ �ݹ� ���, OpenGL �ʱ�ȭ */
	/* -------------------------------------------------------------------------------------- */
	glfwInit();
	glfwSetErrorCallback([](int err, const char* desc) { puts(desc); });
	initContext(/*use dafault = */ true);
	framebufferSizeCallback(nullptr, 256, 256);
	GLFWwindow *window = glfwCreateWindow(g_width, g_height, "Optix!!", nullptr, nullptr);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwMakeContextCurrent(window);
	glewInit();

	/* ��ü ���� */
	/* -------------------------------------------------------------------------------------- */
	MyOptix *my_optix = new MyOptix();


	/* �ʱ�ȭ */
	/* -------------------------------------------------------------------------------------- */
	bool result = my_optix->initialize(300, 300);
	if (result) {
		puts("Optix �ʱ�ȭ ����!");
	}
	else {
		delete my_optix;
		glfwTerminate();
		puts("Optix �ʱ�ȭ ����!");
		return 0;
	}


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
		my_optix->update_opengl_texture();
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