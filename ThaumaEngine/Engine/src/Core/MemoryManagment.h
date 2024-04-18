#pragma once
#include "Define.h"
#include <malloc.h>
#include <stdio.h>

namespace MemoryManager
{

	enum class MemoryType
	{
		Unknown = 0
	};

	struct AllocationData
	{
		i64 totalAllocated = 0;
	};

	void AddAllocation(size_t size, MemoryType memoryType);
	void RemoveAllocation(size_t size, MemoryType memoryType);


	i64 GetTotalAllocated();

	void *Allocate(size_t size, MemoryType memoryType = MemoryType::Unknown);
	void Free(void *ptr, size_t size, MemoryType memoryType = MemoryType::Unknown);
}