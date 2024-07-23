#include "Core/MemoryManagment.h"
#include "Window.h"
#include <GLFW/glfw3.h>



void Window::FrameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
	Window* parentWindowClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	parentWindowClass->Resized();
}

Window::Window()
{
}

void Window::Init(const char* title, int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetFramebufferSizeCallback(m_window, FrameBufferResizeCallback);
}

TAPI b8 Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
	
}

TAPI void Window::Update()
{
	glfwPollEvents();
}



Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
