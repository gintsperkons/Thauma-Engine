#include "VulkanStructures.h"
#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include <set>
#include <stdexcept>


ThaumaEngine::VulkanLogicalDevice::VulkanLogicalDevice(VulkanPhysicalDevice* pDevice)
	:m_physicalDevice(pDevice), m_device(VK_NULL_HANDLE)
{
	CreateLogicalDevice();
	vkGetDeviceQueue(m_device, m_queueIndecies.graphicsFamily.value(), 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_device, m_queueIndecies.presentFamily.value(), 0, &m_presentQueue);
}

ThaumaEngine::VulkanLogicalDevice::~VulkanLogicalDevice()
{
	vkDestroyDevice(m_device, nullptr);
}


void ThaumaEngine::VulkanLogicalDevice::PopulateQueueCreateInfos(std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos)
{
	m_queueIndecies = m_physicalDevice->GetQueueFamilyIndices();

	std::set<uint32_t> uniqueQueueFamilies = { m_queueIndecies.graphicsFamily.value(), m_queueIndecies.presentFamily.value() };

	float queuePriority = 1.0f;

	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}	
}

void ThaumaEngine::VulkanLogicalDevice::CreateLogicalDevice()
{
	VkPhysicalDeviceFeatures deviceFeatures{};

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	PopulateQueueCreateInfos(queueCreateInfos);

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

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
