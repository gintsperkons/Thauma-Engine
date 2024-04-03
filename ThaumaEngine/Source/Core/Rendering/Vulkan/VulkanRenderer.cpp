#include "VulkanRenderer.h"
#include <stdio.h>

VulkanRenderer::~VulkanRenderer()
{

	printf("Destroyed Vulkan Renderer\n");
}

VulkanRenderer::VulkanRenderer()
{
}

int VulkanRenderer::Init(GLFWwindow* window)
{
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
