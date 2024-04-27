#pragma once
#include "Define.h"
#include "VulkanDefines.h"
#include <vulkan/vulkan.h>
#include <vector>

namespace VulkanHelpers { 
b8 CheckInstanceExtensionSupport(std::vector<const char *> checkExtensions);
b8 CheckValidationLayerSupport();
b8 CheckDeviceExtensionSupport(VkPhysicalDevice device);
}