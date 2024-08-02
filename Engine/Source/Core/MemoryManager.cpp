#include "MemoryManager.h"
#include "Core/Logger/Logger.h"


ThaumaEngine::MemoryManager::AllocationData allocationData;

i64 ThaumaEngine::MemoryManager::GetTotalAllocated()
{
	return (allocationData.totalAllocated);
}



void ThaumaEngine::MemoryManager::AddAllocation(size_t size, MemoryManager::MemoryType memoryType)
{
	allocationData.totalAllocated += size;
	allocationData.allocationTypeDataArray[static_cast<int>(memoryType)].AllocatedAmount += size;
}




void ThaumaEngine::MemoryManager::RemoveAllocation(size_t size, ThaumaEngine::MemoryManager::MemoryType memoryType)
{
	allocationData.totalAllocated -= size;
	allocationData.allocationTypeDataArray[static_cast<int>(memoryType)].AllocatedAmount -= size;
}

void ThaumaEngine::MemoryManager::LogAllocations()
{
	LOG_TRACE("Total Allocated: %d\n", allocationData.totalAllocated);
	for (auto &typeData : allocationData.allocationTypeDataArray)
	{
		//LOG_TRACE("Allocated for type %s: %d\n", typeData.Name, typeData.AllocatedAmount);
	}
}


void *ThaumaEngine::MemoryManager::Allocate(size_t size, MemoryManager::MemoryType memoryType)
{
	MemoryManager::AddAllocation(size, memoryType);
	//LOG_DEBUG("Allocated %d bytes\n", size);
	return malloc(size);
}

void ThaumaEngine::MemoryManager::Free(void *ptr, size_t size, MemoryManager::MemoryType memoryType)
{
	MemoryManager::RemoveAllocation(size, memoryType);
	//LOG_DEBUG("Deallocated %d bytes\n", size);
	free(ptr);
}
