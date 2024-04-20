#pragma once
#include "Define.h"
#include "VulkanDefines.h"
#include <vulkan/vulkan.h>

namespace VulkanHelpers { 
u32 RateDeviceSuitability(VkPhysicalDevice device);
b8 CheckDeviceExtensionSupport(VkPhysicalDevice device);
VulkanDefines::QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
}