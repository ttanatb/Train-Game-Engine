#include "Window.h"

GLFWwindow* Window::GLFWwindowPtr;

Window::Window()
{

}

Window::~Window()
{

}

bool Window::start()
{
	if (glfwInit() == GL_FALSE) {
		return -1;
	}

	GLFWwindowPtr = glfwCreateWindow(800, 600, "Super Duper Game Engine 2056", NULL, NULL);

	if (GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
		return false;
	}

	glfwSetInputMode(GLFWwindowPtr,
		GLFW_CURSOR,
		GLFW_CURSOR_HIDDEN);

	glfwSetCursorPos(GLFWwindowPtr, 800.f / 2.f, 600.f / 2.f);
	return true;
}

void Window::update()
{
	glfwSwapBuffers(GLFWwindowPtr);
}