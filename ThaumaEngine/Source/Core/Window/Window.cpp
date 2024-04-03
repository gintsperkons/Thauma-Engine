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
	glfwTerminate();
	printf("Window Destroyed\n");
}
