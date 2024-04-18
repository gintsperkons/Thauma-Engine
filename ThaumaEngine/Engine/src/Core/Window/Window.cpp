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

TAPI b8 Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

TAPI void Window::Update()
{
	glfwPollEvents();
}



Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
