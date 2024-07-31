#pragma once
#include "Defines.h"
#include "VulkanStructures.h"
#include <map>
#include <vector>
#include <vulkan/vulkan.h>

namespace ThaumaEngine {
	class VulkanInstance;
	class VulkanSurface;
	class VulkanPhysicalDevice
	{
		VulkanInstance* m_InstanceManager;
		VulkanSurface* m_surface;
		VkPhysicalDevice m_physicalDevice;
		void PickPhysicalDevice();
		std::multimap<int, VkPhysicalDevice> RateDeviceSutability(std::vector<VkPhysicalDevice> devices);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		public:
			VulkanPhysicalDevice(VulkanInstance* instance, VulkanSurface* surface);
			~VulkanPhysicalDevice();
			QueueFamilyIndices GetQueueFamilyIndices();
			VkPhysicalDevice GetDevice() const { return m_physicalDevice; }
	};
}

