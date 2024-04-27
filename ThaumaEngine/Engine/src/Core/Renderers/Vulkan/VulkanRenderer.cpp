#include "VulkanRenderer.h"

#include "Core/Logger.h"
#include "VulkanHelpers.h"
#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <map>
#include <set>

void VulkanRenderer::CreateInstance()
{
	if (enableValidationLayers && !VulkanHelpers::CheckValidationLayerSupport())
	{
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "TestsAppLication";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	appInfo.pEngineName = "Thauma Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
	appInfo.apiVersion = VK_API_VERSION_1_3;

	std::vector<const char *> instanceExtensions = GetInstanceExtensions();


	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanDefines::ValidationLayers.size());
		createInfo.ppEnabledLayerNames = VulkanDefines::ValidationLayers.data();

		PopulateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
	}



	if (vkCreateInstance(&createInfo, nullptr, &vInstance))
		throw std::runtime_error("Failed to create instance!");


}

void VulkanRenderer::SetupDebugMessanger()
{
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = DebugCallback;
	createInfo.pUserData = nullptr;

	if (CreateDebugUtilsMessangerEXT(vInstance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
		throw std::runtime_error("Failed to set up debug messenger!");
}

void VulkanRenderer::SelectPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(vInstance, &deviceCount, nullptr);
	if (deviceCount == 0)
		throw std::runtime_error("Failed to find GPUs with Vulkan support!");

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(vInstance, &deviceCount, devices.data());

	std::multimap<int, VkPhysicalDevice> candidates;

	for (const auto &device : devices)
	{
		//int score = RateDeviceSuitability(device);
		int score = RateDeviceSuitability(device);
		candidates.insert(std::make_pair(score, device));
	}

	// Check if the best candidate is suitable at all
	if (candidates.rbegin()->first > 0)
	{
		physicalDevice = candidates.rbegin()->second;
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
		printf("Selected GPU: %s\n", deviceProperties.deviceName);
	}
	else
	{
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}


void VulkanRenderer::CreateLogicalDevice()
{
	VulkanDefines::QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

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

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(VulkanDefines::DeviceExtensions.size());
	createInfo.ppEnabledExtensionNames = VulkanDefines::DeviceExtensions.data();

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanDefines::ValidationLayers.size());
		createInfo.ppEnabledLayerNames = VulkanDefines::ValidationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		throw std::runtime_error("failed to create logical device!");

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

void VulkanRenderer::CreateSurface()
{
	if (glfwCreateWindowSurface(vInstance, glfwWindow, nullptr, &vSurface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface!");
	}
}

std::vector<const char *> VulkanRenderer::GetInstanceExtensions()
{
	uint32_t glfwExtensionCount = 0;
	std::vector<const char *> instanceExtensions = std::vector<const char *>();

	const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (size_t i = 0; i < glfwExtensionCount; i++)
	{
		instanceExtensions.push_back(glfwExtensions[i]);
	}

	if (enableValidationLayers)
	{
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}


	if (!VulkanHelpers::CheckInstanceExtensionSupport(instanceExtensions))
	{
		throw std::runtime_error("One or more instance extensions not supported!");
	}

	return instanceExtensions;
}


u32 VulkanRenderer::RateDeviceSuitability(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int score = 0;


	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
	{
		score += 10000;
	}
	VulkanDefines::QueueFamilyIndices indices = FindQueueFamilies(device);
	if (indices.graphicsFamily.has_value())
		score += 1000;

	if (!VulkanHelpers::CheckDeviceExtensionSupport(device))
	{
		score += -1;
	}


	return score;
}


VulkanDefines::QueueFamilyIndices VulkanRenderer::FindQueueFamilies(VkPhysicalDevice device)
{
	VulkanDefines::QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto &queueFamily : queueFamilies)
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, vSurface, &presentSupport);
		if (presentSupport)
			indices.presentFamily = i;

		if (indices.isComplete())
			break;
		i++;
	}

	return indices;
}



VkResult VulkanRenderer::CreateDebugUtilsMessangerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
													  const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessanger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessanger);
	else
		return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void VulkanRenderer::DestroyDebugUtilsMessangerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
		return func(instance, debugMessenger, pAllocator);
}

void VulkanRenderer::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = DebugCallback;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
															 VkDebugUtilsMessageTypeFlagsEXT messageType,
															 const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
															 void *pUserData)
{
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
	}

	return VK_FALSE;
}

VulkanRenderer::~VulkanRenderer()
{
	vkDestroySurfaceKHR(vInstance, vSurface, nullptr);
	vkDestroyDevice(device, nullptr);
	if (enableValidationLayers)
		DestroyDebugUtilsMessangerEXT(vInstance, debugMessenger, nullptr);
	vkDestroyInstance(vInstance, nullptr);

}

VulkanRenderer::VulkanRenderer()
{}

int VulkanRenderer::Init(GLFWwindow *window)
{
	glfwWindow = window;
	CreateInstance();
	SetupDebugMessanger();
	SelectPhysicalDevice();
	CreateLogicalDevice();
	CreateSurface();


	return 0;
}

void VulkanRenderer::Draw()
{}

void VulkanRenderer::Update()
{}

void VulkanRenderer::Destroy()
{
	VulkanRenderer::~VulkanRenderer();
}
