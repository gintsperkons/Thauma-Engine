#include "Core/Rendering/Vulkan/VulkanRenderer.h"
#include "Window.h"

void Window::InitializeRenderer(int RenderType)
{
	switch (RenderType)
	{
	case  Renderer::RenderType::Vulkan:
		if (currentRendererID != Renderer::RenderType::None)
			DestroyCurrentRenderer();
		currentRenderer = new VulkanRenderer();
		currentRenderer->Init(window);
		currentRendererID = RenderType;
		break;
	case  Renderer::RenderType::OpenGL:
		break;
	default:
		break;
	}
}

void Window::DestroyCurrentRenderer()
{
	currentRenderer->Destroy();
	currentRendererID = 0;
}

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
	InitializeRenderer(Renderer::RenderType::Vulkan);
}

Window::~Window()
{
	DestroyCurrentRenderer();
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
