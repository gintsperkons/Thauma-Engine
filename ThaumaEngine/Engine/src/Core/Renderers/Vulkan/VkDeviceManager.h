#pragma once
#include <define.h>
#include <vulkan/vulkan.h>

namespace ThaumaEngine {
	class VkDeviceManager
	{
	private:
		GLFWwindow* m_window;
		VkInstance m_vInstance;
		VkSurfaceKHR m_vSurface;
		VkDebugUtilsMessengerEXT m_debugMessenger;
		VkDevice m_lDevice;
		VkPhysicalDevice m_pDevice;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;


	public:
		VkDeviceManager GetInstance();
		void Init(GLFWwindow &window);

		~VkDeviceManager();

	protected:
		VkDeviceManager* m_instance;
	private:
		VkDeviceManager();
		void CreateInstance();
		void SetupDebugMessanger();
		void CreateSurface();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
		b8 CheckValidationLayerSupport();
		b8 CheckInstanceExtensionSupport(std::vector<const char*> checkExtensions);
		std::vector<const char*>GetInstanceExtensions();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
		u32 RateDeviceSuitability(VkPhysicalDevice device);
		b8 CheckDeviceExtensionSupport(VkPhysicalDevice device);
		VkResult CreateDebugUtilsMessangerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessanger);
			VulkanDefines::QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
			VulkanDefines::SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	};
}