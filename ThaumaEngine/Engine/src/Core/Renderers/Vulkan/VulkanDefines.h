#pragma once
#include "Define.h"
#include <vector>
#include <vulkan/vulkan.h>
#include <optional>


namespace VulkanDefines
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value();
		}
	};

	const std::vector<const char *> ValidationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char *> DeviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};


#ifdef TDEBUG
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif

}