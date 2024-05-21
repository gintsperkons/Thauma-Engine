#pragma once

#include "define.h"
#include "VulkanDefines.h"


#include <vector>
#include <optional>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>


namespace ThaumaEngine {

#include "Core/Renderers/BaseRenderer/BaseRenderer.h"
	class VulkanRenderer : public BaseRenderer
	{
		const int MAX_FRAMES_IN_FLIGHT = 2;

		u32 m_currentFrame = 0;
		GLFWwindow* m_glfwWindow;
		bool m_frameBufferResized = false;
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

		std::vector<VkSemaphore> m_imageAvailableSemaphore;
		std::vector<VkSemaphore> m_renderFinishedSemaphore;
		std::vector<VkFence> m_inFlightFence;


#ifdef TDEBUG
		const bool enableValidationLayers = true;
#else
		const bool enableValidationLayers = false;
#endif

	private:
		//CreationSelection Funcions
		void CreateSwapChain();
		void CreateImageViews();
		void CreateRenderPass();
		void CreateGraphicsPipeline();
		void CreateFrameBuffers();
		void CreateCommandPool();
		void CreateCommandBuffers();
		void CreateSyncObject();
		void RecreateSwapChain();





		//SupportCreationAndDestruction Functions
		void StartCommandBufferRecording(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void FinishCommandBufferRecording(VkCommandBuffer commandBuffer, uint32_t imageIndex);






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
}