#include "VulkanRenderer.h"
#include "Core/Window/Window.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSurface.h"
#include "VulkanSwapChain.h"
#include "VulkanGraphicsPipeline.h"
#include <Core/Window/Window.h>

ThaumaEngine::VulkanRenderer::VulkanRenderer():
	m_instance(nullptr), m_physicalDevice(nullptr), m_logicalDevice(nullptr), 
	m_surface(nullptr), m_swapChain(nullptr), m_graphicsPipeline(nullptr), m_window(nullptr)
{}

ThaumaEngine::VulkanRenderer::~VulkanRenderer()
{
	Shutdown();
}

void ThaumaEngine::VulkanRenderer::Init(Window* window)
{
	m_window = window;
	m_instance = new VulkanInstance();
	m_surface = new VulkanSurface(m_window,m_instance);
	m_physicalDevice = new VulkanPhysicalDevice(m_instance,m_surface);
	m_logicalDevice = new VulkanLogicalDevice(m_physicalDevice);
	m_swapChain = new VulkanSwapChain(m_window,m_physicalDevice,m_logicalDevice,m_surface);
	m_graphicsPipeline = new VulkanGraphicsPipeline(m_logicalDevice);
}

void ThaumaEngine::VulkanRenderer::Render()
{}

void ThaumaEngine::VulkanRenderer::Shutdown()
{
	delete m_swapChain;
	delete m_surface;
	delete m_logicalDevice;
	delete m_physicalDevice;
	delete m_instance;
}
