#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
	static GLFWwindow* GLFWwindowPtr;
	Window();
	~Window();

	static bool start();
	static void update();
};