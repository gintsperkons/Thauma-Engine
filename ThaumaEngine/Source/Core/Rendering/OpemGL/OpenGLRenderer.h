#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Core/Rendering/BaseRenderer/BaseRenderer.h"

class OpenGLRenderer : public BaseRenderer

{
	~OpenGLRenderer();
public:
	OpenGLRenderer();
	int Init(GLFWwindow* window);
	void Draw();
	void Update();
	void Destroy();
};