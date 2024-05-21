#include "Buffers.h"
#include "VulkanHelpers.h"
#include <stdexcept>

namespace ThaumaEngine {
	void CreateVertexBuffer(std::vector<MeshStructures::Vertex>& vertecies, VkBuffer& vertexBuffer, VkDeviceMemory& vertexBufferMemory, VkDevice lDevice, VkPhysicalDevice pDevice)
	{

		VkDeviceSize bufferSize = sizeof(vertecies[0]) * vertecies.size();
		CreateBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory, lDevice, pDevice);


		void* data;
		vkMapMemory(lDevice, vertexBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertecies.data(), (size_t)bufferSize);
		vkUnmapMemory(lDevice, vertexBufferMemory);
	}

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, VkDevice lDevice, VkPhysicalDevice pDevice)
	{
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(lDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to create vertex buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(lDevice, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = VulkanHelpers::FindMemoryType(pDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);


		if (vkAllocateMemory(lDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(lDevice, buffer, bufferMemory, 0);



	}
}