#include "VulkanPhysicalDevice.h"
#include "VulkanSurface.h"
#include "VulkanInstance.h"
#include "Core/Logger/Logger.h"
#include <stdexcept>
#include <set>
#include <string>

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
		QueueFamilyIndices indices = FindQueueFamilies(device);
		bool extensionsSupported = CheckDeviceExtensionSupport(device);
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
			score = -1;
		}

		if (!indices.isComplete())
		{
			score = -1;
		}

		if (!extensionsSupported) {
			score = -1;
		}

		LOG_INFO("Possible Device Name: %s\n", deviceProperties.deviceName);
		candidates.insert(std::pair<int,VkPhysicalDevice>(score,device));
	}


	return candidates;
}

ThaumaEngine::QueueFamilyIndices ThaumaEngine::VulkanPhysicalDevice::FindQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());


	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}


		VkBool32 presentSupport = false;	
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface->GetSurface(), &presentSupport);
		
		if (presentSupport) {
			indices.presentFamily = i;
		}


		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

ThaumaEngine::SwapChainSupportDetails ThaumaEngine::VulkanPhysicalDevice::QuerySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;	
    return details;
}

bool ThaumaEngine::VulkanPhysicalDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}






ThaumaEngine::VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance, VulkanSurface* surface) 
	:m_InstanceManager(instance),m_surface(surface), m_physicalDevice(VK_NULL_HANDLE)
{
	PickPhysicalDevice();
}

ThaumaEngine::VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

ThaumaEngine::QueueFamilyIndices ThaumaEngine::VulkanPhysicalDevice::GetQueueFamilyIndices()
{
	return FindQueueFamilies(m_physicalDevice);
}
