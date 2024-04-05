
#include "Core/Rendering/Renderer.h"
#include "Window.h"





void Window::SetupForVulkan()
{
	glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void Window::SetupForOpenGL()
{
}

Window::Window(std::string title, int width, int height)
	: width(width), height(height)
{
	int RenderType = Renderer::Type::Vulkan;
	printf("Window Created: %s\n", title.c_str());
	glfwSetErrorCallback([](int error, const char *description)
	{
			fprintf(stderr,"Error: %s\n", description);
	});
	switch (RenderType)
	{
	case Renderer::Type::Vulkan:
		SetupForVulkan();
	case Renderer::Type::OpenGL:
		SetupForOpenGL();
	default:
		break;
	}

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwSetWindowUserPointer(window, this);
	currentRenderer = new Renderer();
	currentRenderer->Init(RenderType,window);
}

Window::~Window()
{
	delete currentRenderer;
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
