#pragma once
#include "define.h"
#include "vulkan/vulkan.h"
#include "MeshStructures.h"
#include <vector>
namespace ThaumaEngine {
	void CreateVertexBuffer(std::vector<MeshStructures::Vertex>& vertecies, VkBuffer& vertexBuffer, VkDeviceMemory& vertexBufferMemory);
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
}