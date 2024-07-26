#pragma once
#include "Defines.h"
#include "vulkan/vulkan.h"
namespace ThaumaEngine {
	struct QueueFamilyIndices;
	class VulkanPhysicalDevice;
	class VulkanLogicalDevice
	{
		VkDevice m_device;
		VulkanPhysicalDevice* m_physicalDevice;
		VkQueue m_graphicsQueue;
		QueueFamilyIndices m_queueIndecies;
		
		void PopulateQueueCreateInfo(VkDeviceQueueCreateInfo& queueCreateInfo);
		void CreateLogicalDevice();
	public:
		VulkanLogicalDevice(VulkanPhysicalDevice* pDevice);
		~VulkanLogicalDevice();
	};
}