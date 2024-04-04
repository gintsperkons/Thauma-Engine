#pragma once
#include "define.h"
#include "Core/Rendering/Renderer.h"
#include <GLFW/glfw3.h>
#include <string>

class Window
{
	Renderer* currentRenderer;
	GLFWwindow *window;
	int width = 800;
	int height = 600;
	
public:
	Window(std::string title, int width, int height);
	~Window();

	b8 ShouldClose();
	void PollEvents();
	void ProcessInput();
};

