#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include "Core/Logger/Logger.h"
#include <stdexcept>

void ThaumaEngine::VulkanPhysicalDevice::PickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_InstanceManager->GetInstance(),&deviceCount,nullptr);
	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_InstanceManager->GetInstance(), &deviceCount, devices.data());


	std::multimap<int, VkPhysicalDevice> candidates = RateDeviceSutability(devices);
	if (candidates.size() >=1 && candidates.rbegin()->first > 0) {
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(candidates.rbegin()->second, &deviceProperties);
		LOG_INFO("Chosen Device Name: %s\n", deviceProperties.deviceName);
		m_physicalDevice = candidates.rbegin()->second;
	}
	else {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

std::multimap<int, VkPhysicalDevice> ThaumaEngine::VulkanPhysicalDevice::RateDeviceSutability(std::vector<VkPhysicalDevice> devices)
{
	std::multimap<int, VkPhysicalDevice> candidates;

	for (const auto& device : devices) {
		int score = 0;
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		// Discrete GPUs have a significant performance advantage
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			score += 1000;
		}

		// Maximum possible size of textures affects graphics quality
		score += deviceProperties.limits.maxImageDimension2D;

		// Application can't function without geometry shaders
		if (!deviceFeatures.geometryShader) {
			score = 0;
		}

		LOG_INFO("Possible Device Name: %s\n", deviceProperties.deviceName);
		candidates.insert(std::pair<int,VkPhysicalDevice>(score,device));
	}


	return candidates;
}





ThaumaEngine::VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance) 
	:m_InstanceManager(instance), m_physicalDevice(VK_NULL_HANDLE)
{
	PickPhysicalDevice();
}

ThaumaEngine::VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}
