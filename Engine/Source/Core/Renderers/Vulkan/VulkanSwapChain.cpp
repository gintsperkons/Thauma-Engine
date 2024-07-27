#include "VulkanSwapChain.h"
#include "VulkanInstance.h"
#include <stdexcept>

void ThaumaEngine::VulkanSwapChain::CreateSurface()
{
	if (glfwCreateWindowSurface(m_instance->GetInstance(), m_window->GetWindow(), nullptr, &m_surface)) {

		throw std::runtime_error("failed to create window surface!");
	}
}

ThaumaEngine::VulkanSwapChain::VulkanSwapChain(Window* window,VulkanInstance* instance)
	:m_window(window), m_instance(instance),m_surface(VK_NULL_HANDLE)
{
	CreateSurface();
}

ThaumaEngine::VulkanSwapChain::~VulkanSwapChain()
{
	vkDestroySurfaceKHR(m_instance->GetInstance(), m_surface, nullptr);
}
