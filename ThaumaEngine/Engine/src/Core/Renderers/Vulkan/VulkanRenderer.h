#pragma once

#include "define.h"
#include <vector>
#include <optional>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>


#include "VulkanDefines.h"
#include "Core/Renderers/BaseRenderer/BaseRenderer.h"

class VulkanRenderer : public BaseRenderer
{
	GLFWwindow* glfwWindow;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkSurfaceKHR vSurface;

	VkQueue graphicsQueue;
	VkQueue presentQueue;



	#ifdef TDEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif

private:
	VkInstance vInstance;
	VkDebugUtilsMessengerEXT debugMessenger;
	//CreationSelection Funcions
	void CreateInstance();
	void SetupDebugMessanger();
	void SelectPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSurface();
	//Getter Functions
	std::vector<const char*>GetInstanceExtensions();
	//SupportCreationAndDestruction Functions
	u32 RateDeviceSuitability(VkPhysicalDevice device);
	VulkanDefines::QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	VkResult CreateDebugUtilsMessangerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
										  const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessanger);
	void DestroyDebugUtilsMessangerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
										   											const VkAllocationCallbacks* pAllocator);

	//Support Functions
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	~VulkanRenderer();
public:
	VulkanRenderer();
	int Init(GLFWwindow* window);
	void Draw();
	void Update();
	void Destroy();
};