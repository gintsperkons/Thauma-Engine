#pragma once
#include "Defines.h"
#include "../Base/BaseRenderer.h"


namespace ThaumaEngine
{
	class VulkanInstance;
	class VulkanPhysicalDevice;
	class VulkanLogicalDevice;
	class VulkanRenderer: public BaseRenderer
	{
		VulkanInstance* m_instance;
		VulkanPhysicalDevice* m_physicalDevice;
		VulkanLogicalDevice* m_logicalDevice;
	public:
		VulkanRenderer();
		~VulkanRenderer();

		void Init();
		void Render();
		void Shutdown();
	};
} // namespace TextureGen