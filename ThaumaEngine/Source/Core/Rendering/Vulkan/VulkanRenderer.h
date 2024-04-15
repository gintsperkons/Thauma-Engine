#pragma once

#include "define.h"
#include <vector>
#include <optional>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>

#include "Core/Rendering/BaseRenderer/BaseRenderer.h"

class VulkanRenderer : public BaseRenderer
{
	GLFWwindow* glfwWindow;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkSurfaceKHR surface;

	VkQueue graphicsQueue;

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value();
		}
	};



	const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

	#ifdef DEBUG
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
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	void CreateLogicalDevice();
	void CreateSurface();
	//Getter Functions
	std::vector<const char*>GetInstanceExtensions();
	//Checker Functions
	b8 CheckInstanceExtensionSupport(std::vector<const char*>);
	b8 CheckValidationLayerSupport();
	u32 RateDeviceSuitability(VkPhysicalDevice device);
	//SupportCreationAndDestruction Functions
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