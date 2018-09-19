#include "gui.h"
#include "my_optix.h"

int main()
{
	MyOptix * my_optix;

	/* 창 초기화, 에러 핸들링 등록, 이벤트 콜백 등록, OpenGL 초기화 */
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

	/* 객체 생성 */
	/* -------------------------------------------------------------------------------------- */
	my_optix = new MyOptix();


	/* 초기화 */
	/* -------------------------------------------------------------------------------------- */


	/* 메인 루프 */
	/* -------------------------------------------------------------------------------------- */
	while (!glfwWindowShouldClose(window))
	{
		// 이벤트 핸들링
		/* -------------------------------------------------------------------------------------- */
		glfwPollEvents();


		// GO TO
		/* -------------------------------------------------------------------------------------- */
		my_optix->launch();
		my_optix->render();


		// 스왑 버퍼
		/* -------------------------------------------------------------------------------------- */
		glfwSwapBuffers(window);
	}


	// 객체 제거
	/* -------------------------------------------------------------------------------------- */
	delete my_optix;


	// 종료
	/* -------------------------------------------------------------------------------------- */
	glfwTerminate();
}