#include "VulkanRenderer.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"

ThaumaEngine::VulkanRenderer::VulkanRenderer(): m_instance(nullptr), m_physicalDevice(nullptr)
{}

ThaumaEngine::VulkanRenderer::~VulkanRenderer()
{
	Shutdown();
}

void ThaumaEngine::VulkanRenderer::Init()
{
	m_instance = new VulkanInstance();
	m_physicalDevice = new VulkanPhysicalDevice(m_instance);
	m_logicalDevice = new VulkanLogicalDevice(m_physicalDevice);
}

void ThaumaEngine::VulkanRenderer::Render()
{}

void ThaumaEngine::VulkanRenderer::Shutdown()
{
	delete m_instance;
	delete m_physicalDevice;
	delete m_logicalDevice;
}
