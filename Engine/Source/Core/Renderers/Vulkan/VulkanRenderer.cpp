#include "VulkanRenderer.h"
#include "Core/Window/Window.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSurface.h"
#include <Core/Window/Window.h>

ThaumaEngine::VulkanRenderer::VulkanRenderer(): m_instance(nullptr), m_physicalDevice(nullptr)
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
}

void ThaumaEngine::VulkanRenderer::Render()
{}

void ThaumaEngine::VulkanRenderer::Shutdown()
{
	delete m_surface;
	delete m_logicalDevice;
	delete m_physicalDevice;
	delete m_instance;
}
