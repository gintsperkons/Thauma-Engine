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
		std::optional<uint32_t> presentFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

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