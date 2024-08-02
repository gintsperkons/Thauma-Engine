#include "Defines.h"
#include "VulkanStructures.h"
namespace ThaumaEngine
{
	class Window;
	class VulkanPhysicalDevice;
	class VulkanLogicalDevice;
	class VulkanSurface;
	class VulkanSwapChain
	{
		Window *m_currentWindow;
		VulkanPhysicalDevice* m_physicalDevice;
		VulkanLogicalDevice* m_logicalDevice;
		VulkanSurface* m_surface;
		VkSwapchainKHR m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		std::vector<VkImageView> m_swapChainImageViews;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;


		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		void CreateSwapChain();
		void CreateImageViews();
	public:
		
		VulkanSwapChain(Window *window, VulkanPhysicalDevice *pDevice, VulkanLogicalDevice *lDevice, VulkanSurface *surface);
		~VulkanSwapChain();
	};
} // namespace ThaumaEngine
