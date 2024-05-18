#pragma once
#include "define.h"
#include "vulkan/vulkan.h"
#include "MeshStructures.h"
#include <vector>
void CreateVertexBuffer(std::vector<MeshStructures::Vertex>& vertecies, VkBuffer& vertexBuffer, VkDeviceMemory& vertexBufferMemory, VkDevice lDevice, VkPhysicalDevice pDevice);
void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, VkDevice lDevice, VkPhysicalDevice pDevice);