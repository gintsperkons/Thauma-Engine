#pragma once
#include "Defines.h"
#include "VulkanStructures.h"
#include <map>
#include <vector>
#include <vulkan/vulkan.h>
namespace ThaumaEngine {
	class VulkanInstance;
	class VulkanPhysicalDevice
	{
		VulkanInstance* m_InstanceManager;
		VkPhysicalDevice m_physicalDevice;
		void PickPhysicalDevice();
		std::multimap<int, VkPhysicalDevice> RateDeviceSutability(std::vector<VkPhysicalDevice> devices);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		public:
			VulkanPhysicalDevice(VulkanInstance* instance);
			~VulkanPhysicalDevice();
	};
}

