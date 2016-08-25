#define GLEW_STATIC
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "window.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

#ifdef _DEBUG

void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar *message, const void *userParam)
{
	//std::cerr << message << std::endl;
	fprintf(stderr, "%s\n", message);

	if (severity == GL_DEBUG_SEVERITY_HIGH)
	{
		//exit();
		abort();
	}
}
#endif

bool Window::init(int a_width, int a_height, char * a_title)
{
	width = a_width;
	height = a_height;
	strcpy_s(title, 64, a_title);

	glfwInit();

	winHandle = glfwCreateWindow(width, height , title, nullptr, nullptr);

	glfwMakeContextCurrent(winHandle);
	isInitialized = true;

	glewExperimental = true;
	glewInit();
	//            R     G     B   alpha
	glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif
	return true;
}

bool Window::step()
{
	if (!isInitialized) return false;
	
	glfwPollEvents();
	glfwSwapBuffers(winHandle);
	glClear(GL_COLOR_BUFFER_BIT);

	return !glfwWindowShouldClose(winHandle);
}

bool Window::term()
{
	glfwDestroyWindow(winHandle);
	glfwTerminate();
	winHandle = nullptr;
	isInitialized = false;
	return true;
}
