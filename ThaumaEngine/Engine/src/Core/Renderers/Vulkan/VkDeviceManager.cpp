#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "VulkanDefines.h"
#include "VkDeviceManager.h"


namespace ThaumaEngine {
	VkDeviceManager::VkDeviceManager()
	{
	
	}

	VkDeviceManager VkDeviceManager::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new VkDeviceManager();
		}
		return VkDeviceManager();
	}

	void VkDeviceManager::Init(GLFWwindow &window)
	{
		m_window = &window;
		CreateInstance();
		SetupDebugMessanger();
		CreateSurface();
		SelectPhysicalDevice();
		CreateLogicalDevice();
	}

	VkDeviceManager::~VkDeviceManager()
	{
	}

	void VkDeviceManager::CreateInstance()
	{
		if (VulkanDefines::enableValidationLayers && !CheckValidationLayerSupport())
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

		std::vector<const char*> instanceExtensions = GetInstanceExtensions();


		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.ppEnabledExtensionNames = instanceExtensions.data();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (VulkanDefines::enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanDefines::ValidationLayers.size());
			createInfo.ppEnabledLayerNames = VulkanDefines::ValidationLayers.data();

			PopulateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;

			createInfo.pNext = nullptr;
		}



		if (vkCreateInstance(&createInfo, nullptr, &m_vInstance))
			throw std::runtime_error("Failed to create instance!");

	}

	void VkDeviceManager::SetupDebugMessanger()
	{
		if (!VulkanDefines::enableValidationLayers) return;

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

		if (CreateDebugUtilsMessangerEXT(m_vInstance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
			throw std::runtime_error("Failed to set up debug messenger!");
	}


	void VkDeviceManager::CreateSurface()
	{
		if (glfwCreateWindowSurface(m_vInstance, m_window, nullptr, &m_vSurface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create window surface!");
		}
	}

	void VkDeviceManager::SelectPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_vInstance, &deviceCount, nullptr);
		if (deviceCount == 0)
			throw std::runtime_error("Failed to find GPUs with Vulkan support!");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_vInstance, &deviceCount, devices.data());

		std::multimap<int, VkPhysicalDevice> candidates;

		for (const auto& device : devices)
		{
			int score = RateDeviceSuitability(device);
			candidates.insert(std::make_pair(score, device));
		}

		// Check if the best candidate is suitable at all
		if (candidates.rbegin()->first > 0)
		{
			m_pDevice = candidates.rbegin()->second;
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(m_pDevice, &deviceProperties);
			printf("Selected GPU: %s\n", deviceProperties.deviceName);
		}
		else
		{
			throw std::runtime_error("failed to find a suitable GPU!");
		}
	}
	void VkDeviceManager::CreateLogicalDevice()
	{
		VulkanDefines::QueueFamilyIndices indices = FindQueueFamilies(m_pDevice);

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
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(VulkanDefines::DeviceExtensions.size());
		createInfo.ppEnabledExtensionNames = VulkanDefines::DeviceExtensions.data();

		if (VulkanDefines::enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanDefines::ValidationLayers.size());
			createInfo.ppEnabledLayerNames = VulkanDefines::ValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(m_pDevice, &createInfo, nullptr, &m_lDevice) != VK_SUCCESS)
			throw std::runtime_error("failed to create logical device!");

		vkGetDeviceQueue(m_lDevice, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_lDevice, indices.presentFamily.value(), 0, &m_presentQueue);
	}


	b8 VkDeviceManager::CheckValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> layers = std::vector<VkLayerProperties>(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

		for (const char* layerName : VulkanDefines::ValidationLayers)
		{
			b8 layerFound = false;

			for (const auto& layerProperties : layers)
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

	b8 VkDeviceManager::CheckInstanceExtensionSupport(std::vector<const char*> checkExtensions)
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());



		for (const auto& checkExtension : checkExtensions)
		{
			b8 hasExtension = false;
			for (const auto& extension : extensions)
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


	std::vector<const char*> VkDeviceManager::GetInstanceExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		std::vector<const char*> instanceExtensions = std::vector<const char*>();

		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		for (size_t i = 0; i < glfwExtensionCount; i++)
		{
			instanceExtensions.push_back(glfwExtensions[i]);
		}

		if (VulkanDefines::enableValidationLayers)
		{
			instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}


		if (!CheckInstanceExtensionSupport(instanceExtensions))
		{
			throw std::runtime_error("One or more instance extensions not supported!");
		}

		return instanceExtensions;
	}

	void VkDeviceManager::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
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

	VKAPI_ATTR VkBool32 VKAPI_CALL VkDeviceManager::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
		}

		return VK_FALSE;
	}


	u32 VkDeviceManager::RateDeviceSuitability(VkPhysicalDevice device)
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

		b8 extensionsSupported = CheckDeviceExtensionSupport(device);

		b8 swapChainAdequate = false;
		if (extensionsSupported)
		{
			VulkanDefines::SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}
		if (!swapChainAdequate || !extensionsSupported)
		{
			score = -10000;
		}


		return score;
	}

	b8 VkDeviceManager::CheckDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(VulkanDefines::DeviceExtensions.begin(),
			VulkanDefines::DeviceExtensions.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}


		return requiredExtensions.empty();
	}


	VulkanDefines::SwapChainSupportDetails VkDeviceManager::QuerySwapChainSupport(VkPhysicalDevice device)
	{
		VulkanDefines::SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_vSurface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_vSurface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_vSurface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_vSurface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_vSurface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	VkResult VkDeviceManager::CreateDebugUtilsMessangerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessanger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr)
			return func(instance, pCreateInfo, pAllocator, pDebugMessanger);
		else
			return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	VulkanDefines::QueueFamilyIndices VkDeviceManager::FindQueueFamilies(VkPhysicalDevice device)
	{
		VulkanDefines::QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				indices.graphicsFamily = i;

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_vSurface, &presentSupport);
			if (presentSupport)
				indices.presentFamily = i;

			if (indices.isComplete())
				break;
			i++;
		}

		return indices;
	}

}