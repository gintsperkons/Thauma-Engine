#include "Core/MemoryManagment.h"
#include "Window.h"
#include <GLFW/glfw3.h>



Window::Window()
{
}

void Window::Init(const char* title, int width, int height)
{
	glfwInit();
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
}

Window::~Window()
{
}
