#include "VulkanGraphicsPipeline.h"
#include "Core/Files/FileReader.h"
#include "VulkanLogicalDevice.h"
#include <stdexcept>

VkShaderModule ThaumaEngine::VulkanGraphicsPipeline::CreateShaderModule(const std::vector<char> &code)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(m_logicalDevice->GetDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create shader module!");
	}
	return shaderModule;
}

void ThaumaEngine::VulkanGraphicsPipeline::CreateShaderStage()
{

}

ThaumaEngine::VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanLogicalDevice* lDevice)
{
	auto vertShaderCode = FileReader::ReadFileBinary("Shaders/base-vert.spv");
	auto fragShaderCode = FileReader::ReadFileBinary("Shaders/base-frag.spv");
	m_vertexShaderModule = CreateShaderModule(vertShaderCode);
	m_fragmentShaderModule = CreateShaderModule(fragShaderCode);
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = m_vertexShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = m_fragmentShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

}

ThaumaEngine::VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
	vkDestroyShaderModule(m_logicalDevice->GetDevice(), m_fragmentShaderModule, nullptr);
	vkDestroyShaderModule(m_logicalDevice->GetDevice(), m_vertexShaderModule, nullptr);
}
