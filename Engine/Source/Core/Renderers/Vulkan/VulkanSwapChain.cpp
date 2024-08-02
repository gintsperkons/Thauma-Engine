#include "VulkanSwapChain.h"
#include "Core/Window/Window.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSurface.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <stdexcept>

VkSurfaceFormatKHR ThaumaEngine::VulkanSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
	for (const auto &availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR ThaumaEngine::VulkanSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
{
	for (const auto &availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D ThaumaEngine::VulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			return capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(m_currentWindow->GetWindow(), &width, &height);

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}
}

void ThaumaEngine::VulkanSwapChain::CreateSwapChain()
{
	SwapChainSupportDetails swapChainSupport = m_physicalDevice->QuerySwapChainSupport();

	VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = m_surface->GetSurface();

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = m_physicalDevice->GetQueueFamilyIndices();
	uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
	if (indices.graphicsFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(m_logicalDevice->GetDevice(), &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create swap chain!");
	}

	vkGetSwapchainImagesKHR(m_logicalDevice->GetDevice(), m_swapChain, &imageCount, nullptr);
	m_swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(m_logicalDevice->GetDevice(), m_swapChain, &imageCount, m_swapChainImages.data());

	m_swapChainImageFormat = surfaceFormat.format;
	m_swapChainExtent = extent;
}

void ThaumaEngine::VulkanSwapChain::CreateImageViews()
{
		m_swapChainImageViews.resize(m_swapChainImages.size());

		for (size_t i = 0; i < m_swapChainImages.size(); i++)
		{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = m_swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = m_swapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(m_logicalDevice->GetDevice(), &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create image views!");
		}
	}	
}

ThaumaEngine::VulkanSwapChain::VulkanSwapChain(Window* window, VulkanPhysicalDevice* pDevice, VulkanLogicalDevice* lDevice,VulkanSurface* surface):
	m_currentWindow(window), m_physicalDevice(pDevice), m_logicalDevice(lDevice), m_surface(surface), m_swapChain(VK_NULL_HANDLE)
{
	CreateSwapChain();
	CreateImageViews();
}

ThaumaEngine::VulkanSwapChain::~VulkanSwapChain()
{
	for (auto imageView : m_swapChainImageViews)
	{
		vkDestroyImageView(m_logicalDevice->GetDevice(), imageView, nullptr);
	}
	if (m_swapChain != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(m_logicalDevice->GetDevice(), m_swapChain, nullptr);
	}
}
