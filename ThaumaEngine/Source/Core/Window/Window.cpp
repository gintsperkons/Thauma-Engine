#include "Window.h"

Window::Window(std::string title, int width, int height)
	: width(width), height(height)
{
	printf("Window Created: %s\n", title.c_str());
	if (!glfwInit())
	{
		printf("GLFW Init Failed\n");
		glfwTerminate();
	}
	glfwSetErrorCallback([](int error, const char *description)
	{
			fprintf(stderr,"Error: %s\n", description);
	});
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	printf("Window Destroyed\n");
}

b8 Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
