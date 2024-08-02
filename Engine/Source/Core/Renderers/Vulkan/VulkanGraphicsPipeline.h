#pragma once
#include "Defines.h"
#include <vulkan/vulkan.h>
#include <vector>
namespace ThaumaEngine
{	class VulkanLogicalDevice;
	class VulkanGraphicsPipeline
	{
		VkShaderModule m_vertexShaderModule;
		VkShaderModule m_fragmentShaderModule;
		VulkanLogicalDevice *m_logicalDevice;
		VkShaderModule CreateShaderModule(const std::vector<char> &code);
		void CreateShaderStage();
	public:
		VulkanGraphicsPipeline(VulkanLogicalDevice *lDevice);
		~VulkanGraphicsPipeline();
	};
} // namespace ThaumaEngine