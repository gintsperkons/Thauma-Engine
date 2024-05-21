#pragma once
#include "Define.h"
#include "VulkanDefines.h"
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace ThaumaEngine {
	namespace VulkanHelpers {
		b8 CheckInstanceExtensionSupport(std::vector<const char*> checkExtensions);
		b8 CheckValidationLayerSupport();
		b8 CheckDeviceExtensionSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow& window);
		VkShaderModule CreateShaderModule(VkDevice device, const std::vector<char>& code);
		uint32_t FindMemoryType(VkPhysicalDevice pDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
		std::vector<char> ReadFileSPV(const std::string& filename);
	}
}