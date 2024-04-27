#include "VulkanHelpers.h"
#include <set>
#include <string>




b8 VulkanHelpers::CheckInstanceExtensionSupport(std::vector<const char *> checkExtensions)
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());



	for (const auto &checkExtension : checkExtensions)
	{
		b8 hasExtension = false;
		for (const auto &extension : extensions)
		{
			if (strcmp(checkExtension, extension.extensionName))
			{
				hasExtension = true;
				break;
			}

		}
		if (!hasExtension)
		{
			printf("Not found extension: %s\n", checkExtension);
			return false;
		}
	}
	return true;

}

b8 VulkanHelpers::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> layers = std::vector<VkLayerProperties>(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

	for (const char *layerName : VulkanDefines::ValidationLayers)
	{
		b8 layerFound = false;

		for (const auto &layerProperties : layers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{

			printf("Not found layer: %s\n", layerName);
			return false;
		}
	}




	return true;
}



b8 VulkanHelpers::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(VulkanDefines::DeviceExtensions.begin(), 
											 VulkanDefines::DeviceExtensions.end());

	for (const auto &extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}


	return requiredExtensions.empty();
}

