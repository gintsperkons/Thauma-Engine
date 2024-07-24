#pragma once
#include "Defines.h"
#include "vulkan/vulkan.h"
#include <optional>

namespace ThaumaEngine {
	struct QueueFamilyIndices {
		std::optional<uint32_t>  graphicsFamily;
		bool isComplete() const {
			return graphicsFamily.has_value();
		}
	};
}