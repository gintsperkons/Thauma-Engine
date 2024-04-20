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
	allocationData.allocationTypeDataArray[static_cast<int>(memoryType)].AllocatedAmount += size;
}




void MemoryManager::RemoveAllocation(size_t size, MemoryManager::MemoryType memoryType)
{
allocationData.totalAllocated -= size;
allocationData.allocationTypeDataArray[static_cast<int>(memoryType)].AllocatedAmount -= size;
}

void MemoryManager::LogAllocations()
{
	return;
	LOG_DEBUG("Total Allocated: %d\n", allocationData.totalAllocated);
	for (auto &typeData : allocationData.allocationTypeDataArray)
	{
		LOG_DEBUG("Allocated for type %s: %d\n", typeData.Name, typeData.AllocatedAmount);
	}
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

