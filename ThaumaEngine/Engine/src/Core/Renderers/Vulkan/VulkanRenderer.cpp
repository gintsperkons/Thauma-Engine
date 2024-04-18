#include "VulkanRenderer.h"

#include <stdexcept>
#include <iostream>
#include <stdio.h>

void VulkanRenderer::CreateInstance()
{
	if (enableValidationLayers && !CheckValidationLayerSupport()) {
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

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}



	if (vkCreateInstance(&createInfo, nullptr, &vInstance))
		throw std::runtime_error("Failed to create instance!");


}

std::vector<const char*> VulkanRenderer::GetInstanceExtensions()
{
	uint32_t glfwExtensionCount = 0;
	std::vector<const char*> instanceExtensions = std::vector<const char*>();

	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (size_t i = 0; i < glfwExtensionCount; i++)
	{
		instanceExtensions.push_back(glfwExtensions[i]);
	}

	if (enableValidationLayers)
	{
		//TODO
	}


	if (!CheckInstanceExtensionSupport(instanceExtensions))
	{
		throw std::runtime_error("One or more instance extensions not supported!");
	}

	return instanceExtensions;
}

b8 VulkanRenderer::CheckInstanceExtensionSupport(std::vector<const char*> checkExtensions)
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "available extensions:\n";

	for (const auto& extension : extensions) {
		std::cout << '\t' << extension.extensionName << '\n';
	}

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

b8 VulkanRenderer::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> layers = std::vector<VkLayerProperties>(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

	for (const char* layerName : validationLayers)
	{
		b8 layerFound = false;

		for (const auto& layerProperties : layers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
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




	std::cout << "available layers:\n";

	for (const auto& layer : layers) {
		std::cout << '\t' << layer.layerName << '\n';
	}
	return true;
}

VulkanRenderer::~VulkanRenderer()
{
	vkDestroyInstance(vInstance,nullptr);
	printf("Destroyed Vulkan Renderer\n");
}

VulkanRenderer::VulkanRenderer()
{
}

int VulkanRenderer::Init(GLFWwindow* window)
{
	CreateInstance();
	printf("Created Vulkan Renderer\n");
	return 0;
}

void VulkanRenderer::Draw()
{
}

void VulkanRenderer::Update()
{
}

void VulkanRenderer::Destroy()
{
	VulkanRenderer::~VulkanRenderer();
}