#include "MemoryManagment.h"
#include "Core/Logger.h"



MemoryManager::AllocationData allocationData;

i64 MemoryManager::GetTotalAllocated()
{
	return (allocationData.totalAllocated);
}

void MemoryManager::AddAllocation(size_t size, MemoryManager::MemoryType memoryType)
{
	allocationData.totalAllocated += size;
}



void MemoryManager::RemoveAllocation(size_t size, MemoryManager::MemoryType memoryType)
{
allocationData.totalAllocated -= size;
}


void *MemoryManager::Allocate(size_t size, MemoryManager::MemoryType memoryType)
{
	MemoryManager::AddAllocation(size, memoryType);
	LOG_DEBUG("Allocated %d bytes\n",size);
	return malloc(size);
}

void MemoryManager::Free(void *ptr, size_t size, MemoryManager::MemoryType memoryType)
{
	MemoryManager::RemoveAllocation(size, memoryType);
	LOG_DEBUG("Deallocated %d bytes\n", size);
	free(ptr);
}

