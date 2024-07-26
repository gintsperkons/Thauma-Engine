#include "VulkanStructures.h"
#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include <stdexcept>


ThaumaEngine::VulkanLogicalDevice::VulkanLogicalDevice(VulkanPhysicalDevice* pDevice)
	:m_physicalDevice(pDevice), m_device(VK_NULL_HANDLE)
{
	CreateLogicalDevice();
	vkGetDeviceQueue(m_device, m_queueIndecies.graphicsFamily.value(), 0, &m_graphicsQueue);
}

ThaumaEngine::VulkanLogicalDevice::~VulkanLogicalDevice()
{
	vkDestroyDevice(m_device, nullptr);
}


void ThaumaEngine::VulkanLogicalDevice::PopulateQueueCreateInfo(VkDeviceQueueCreateInfo& queueCreateInfo)
{
	m_queueIndecies = m_physicalDevice->GetQueueFamilyIndices();

	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = m_queueIndecies.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;
	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;
}

void ThaumaEngine::VulkanLogicalDevice::CreateLogicalDevice()
{
	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceQueueCreateInfo queueCreateInfo{};
	PopulateQueueCreateInfo(queueCreateInfo);

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;

	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(m_physicalDevice->GetDevice(), &createInfo, nullptr, &m_device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

}
