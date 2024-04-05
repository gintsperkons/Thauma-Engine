#pragma once

#include "define.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "Core/Rendering/BaseRenderer/BaseRenderer.h"

class VulkanRenderer : public BaseRenderer
{
private:
	VkInstance vInstance;
	//Creation Funcions
	void CreateInstance();
	//Getter Functions
	std::vector<const char*>GetInstanceExtensions();
	//Checker Functions
	b8 CheckInstanceExtensionSupport(std::vector<const char*>);

	~VulkanRenderer();
public:
	VulkanRenderer();
	int Init(GLFWwindow* window);
	void Draw();
	void Update();
	void Destroy();
};