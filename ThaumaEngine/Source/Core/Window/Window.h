#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "define.h"

class Window
{
	GLFWwindow *window;
	int width = 800;
	int height = 600;
public:
	Window(std::string title, int width, int height);
	~Window();
};

