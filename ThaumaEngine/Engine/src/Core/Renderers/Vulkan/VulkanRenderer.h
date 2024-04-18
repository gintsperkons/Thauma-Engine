#pragma once

#include "define.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "Core/Renderers/BaseRenderer/BaseRenderer.h"

class VulkanRenderer : public BaseRenderer
{
	const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

	#ifdef DEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif

private:
	VkInstance vInstance;
	//Creation Funcions
	void CreateInstance();
	//Getter Functions
	std::vector<const char*>GetInstanceExtensions();
	//Checker Functions
	b8 CheckInstanceExtensionSupport(std::vector<const char*>);
	b8 CheckValidationLayerSupport();

	~VulkanRenderer();
public:
	VulkanRenderer();
	int Init(GLFWwindow* window);
	void Draw();
	void Update();
	void Destroy();
};