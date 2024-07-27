#pragma once
#include "Defines.h"
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "Core/Window/Window.h"

namespace ThaumaEngine {
	class VulkanInstance;
	class VulkanSwapChain
	{
		VulkanInstance* m_instance;
		Window* m_window;
		VkSurfaceKHR m_surface;
		void CreateSurface();
	public:
		VulkanSwapChain(Window* window, VulkanInstance* instance);
		~VulkanSwapChain();
	};
}