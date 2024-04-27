#pragma once
#include "Define.h"
#include "VulkanDefines.h"
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vector>

namespace VulkanHelpers { 
b8 CheckInstanceExtensionSupport(std::vector<const char *> checkExtensions);
b8 CheckValidationLayerSupport();
b8 CheckDeviceExtensionSupport(VkPhysicalDevice device);
VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow &window);
}