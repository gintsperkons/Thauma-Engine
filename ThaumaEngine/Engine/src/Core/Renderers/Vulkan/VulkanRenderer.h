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
	GLFWwindow* m_glfwWindow;
	VkPhysicalDevice m_pDevice = VK_NULL_HANDLE;
	VkDevice m_lDevice = VK_NULL_HANDLE;
	VkSurfaceKHR m_vSurface;
	VkSwapchainKHR m_swapChain;
	std::vector<VkImage> m_swapChainImages;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;
	std::vector<VkImageView> m_swapChainImageViews;
	VkRenderPass m_renderPass;
	VkPipelineLayout m_piplineLayout;
	VkPipeline m_graphicsPipeline;
	std::vector<VkFramebuffer> m_swapChainFramebuffers;
	VkCommandPool m_commandPool;
	VkCommandBuffer m_commandBuffer;

	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;



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
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	void CreateFrameBuffer();
	void CreateCommandPool();
	void CreateCommandBuffer();
	




	//Getter Functions
	std::vector<const char*>GetInstanceExtensions();
	//SupportCreationAndDestruction Functions
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	u32 RateDeviceSuitability(VkPhysicalDevice device);
	VulkanDefines::QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	VulkanDefines::SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
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