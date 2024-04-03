#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Core/Rendering/Renderer.h"

class VulkanRenderer : public Renderer

{
	~VulkanRenderer();
public:
	VulkanRenderer();
	int Init(GLFWwindow* window);
	void Draw();
	void Update();
	void Destroy();
};