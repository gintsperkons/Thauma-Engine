#pragma once
#include "Defines.h"
#include "VulkanStructures.h"
#include "vulkan/vulkan.h"
namespace ThaumaEngine {
	struct QueueFamilyIndices;
	class VulkanPhysicalDevice;
	class VulkanLogicalDevice
	{
		VkDevice m_device;
		VulkanPhysicalDevice* m_physicalDevice;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		QueueFamilyIndices m_queueIndecies;
		
		void PopulateQueueCreateInfos(std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos);
		void CreateLogicalDevice();
	public:
		VulkanLogicalDevice(VulkanPhysicalDevice* pDevice);
		~VulkanLogicalDevice();

		VkDevice GetDevice() const { return m_device; }
	};
}