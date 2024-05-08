#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Core/Renderers/BaseRenderer/BaseRenderer.h"

class OpenGLRenderer : public BaseRenderer

{
	~OpenGLRenderer();
public:
	OpenGLRenderer();
	int Init(GLFWwindow* window);
	void StartRendering();
	void FinishRendering();
	void Draw();
	void Update();
	void Destroy();
	void Complete();
};