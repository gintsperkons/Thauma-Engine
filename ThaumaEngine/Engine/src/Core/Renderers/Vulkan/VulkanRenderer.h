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
	const int MAX_FRAMES_IN_FLIGHT = 2;

	u32 m_currentFrame = 0;
	GLFWwindow* m_glfwWindow;
	bool m_frameBufferResized = false;
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
	std::vector < VkCommandBuffer> m_commandBuffers;
	uint32_t m_imageIndex = -1;

	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;

	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;
	std::vector<VkSemaphore> m_imageAvailableSemaphore;
	std::vector<VkSemaphore> m_renderFinishedSemaphore;
	std::vector<VkFence> m_inFlightFence;


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
	void CreateFrameBuffers();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSyncObject();
	void RecreateSwapChain();
	




	//Getter Functions
	std::vector<const char*>GetInstanceExtensions();
	//SupportCreationAndDestruction Functions
	void StartCommandBufferRecording(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void FinishCommandBufferRecording(VkCommandBuffer commandBuffer, uint32_t imageIndex);
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




	void CleanSwapChain();
	~VulkanRenderer();
public:
	VulkanRenderer();
	int Init(GLFWwindow* window);
	void StartRendering();
	void FinishRendering();
	void Draw();
	void Update();
	void Destroy();
	void Complete();
};