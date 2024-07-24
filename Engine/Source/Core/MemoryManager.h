#pragma once
#include "Defines.h"
#include <malloc.h>
#include <stdio.h>

namespace ThaumaEngine
{
	namespace MemoryManager
	{



		struct AllocationTypeData
		{
			char Name[16];
			i64 AllocatedAmount = 0;
		};

		enum class MemoryType
		{
			Unknown = 0,
			Rendering
		};

		struct AllocationData
		{
			char Name[6] = "Total";
			//Bytes
			i64 totalAllocated = 0;
			AllocationTypeData allocationTypeDataArray[2] = {
		{"Unknown", 0},
		{"Rendering", 0}
			};

		};
		void AddAllocation(size_t size, MemoryType memoryType);
		void RemoveAllocation(size_t size, MemoryType memoryType);
		void LogAllocations();

		i64 GetTotalAllocated();

		void *Allocate(size_t size, MemoryType memoryType = MemoryType::Unknown);
		void Free(void *ptr, size_t size, MemoryType memoryType = MemoryType::Unknown);
	}
}