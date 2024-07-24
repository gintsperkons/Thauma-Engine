#pragma once
#include "Defines.h"
#include <vulkan/vulkan.h>
#include <vector>

namespace ThaumaEngine
{
	const std::vector<const char *> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	#ifdef TDEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif // TDEBUG


	class VulkanInstance
	{
		VkInstance m_Instance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		void CreateInstance();
		std::vector<const char*> GetInstanceExtensions();
		bool CheckInstanceExtensionSupport(std::vector<const char*> extensions);
		bool CheckValidationLayerSupport();
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
		void SetupDebugMessenger();
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
			void *pUserData);
	public:
		VulkanInstance();
		~VulkanInstance();
		VkInstance GetInstance();
	};
}

