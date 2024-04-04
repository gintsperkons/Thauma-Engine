#pragma once
#include "define.h"
#include "GLFW/glfw3.h"
#include "BaseRenderer/BaseRenderer.h"

class Renderer {
	BaseRenderer* currentRenderer;
	i8 currentRendererID = 0;

	void Destroy();
public:
	void Init(int renderType, GLFWwindow* window);
	~Renderer();


	enum Type
	{
		None,
		Vulkan,
		OpenGL
	};
};