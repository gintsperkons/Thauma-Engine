#include "VertexBuffer.h"
#include "VulkanHelpers.h"
#include "MeshStructures.h"
#include <stdexcept>

void CreateVertexBuffer(std::vector<Vertex>* vertecies,VkBuffer* vertexBuffer, VkDeviceMemory* vertexBufferMemory,VkDevice lDevice, VkPhysicalDevice pDevice)
{

	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(MeshStructures::vertices[0]) * MeshStructures::vertices.size();
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(lDevice, &bufferInfo, nullptr, vertexBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(lDevice, *vertexBuffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = VulkanHelpers::FindMemoryType(pDevice,memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (vkAllocateMemory(lDevice, &allocInfo, nullptr, vertexBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}

	vkBindBufferMemory(lDevice, *vertexBuffer, *vertexBufferMemory, 0);


	void* data;
	vkMapMemory(lDevice, *vertexBufferMemory, 0, bufferInfo.size, 0, &data);
	memcpy(data, MeshStructures::vertices.data(), (size_t)bufferInfo.size);
	vkUnmapMemory(lDevice, *vertexBufferMemory);
}