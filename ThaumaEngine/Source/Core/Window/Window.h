#pragma once
#include "Core/Rendering/Renderer.h"
#include <GLFW/glfw3.h>
#include <string>
#include "define.h"

class Window
{
	Renderer* currentRenderer;
	int currentRendererID = 0;
	GLFWwindow *window;
	int width = 800;
	int height = 600;


	void InitializeRenderer(int RenderType);
	void DestroyCurrentRenderer();
public:
	Window(std::string title, int width, int height);
	~Window();

	b8 ShouldClose();
	void PollEvents();
	void ProcessInput();
};

