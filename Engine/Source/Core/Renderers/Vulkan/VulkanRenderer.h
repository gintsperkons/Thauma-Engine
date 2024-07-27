#pragma once
#include "Defines.h"
#include "../Base/BaseRenderer.h"


namespace ThaumaEngine
{
	class Window;
	class VulkanInstance;
	class VulkanPhysicalDevice;
	class VulkanLogicalDevice;
	class VulkanSwapChain;
	class VulkanRenderer: public BaseRenderer
	{
		Window* m_window;
		VulkanInstance* m_instance;
		VulkanPhysicalDevice* m_physicalDevice;
		VulkanLogicalDevice* m_logicalDevice;
		VulkanSwapChain* m_swapChain;
	public:
		VulkanRenderer();
		~VulkanRenderer();

		void Init(Window* window);
		void Render();
		void Shutdown();
	};
} // namespace TextureGen