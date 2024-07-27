#pragma once
#include "Defines.h"
#include "vulkan/vulkan.h"
#include <optional>
#include <vector>

namespace ThaumaEngine {
	struct QueueFamilyIndices {
		std::optional<uint32_t>  graphicsFamily;
		std::optional<uint32_t>  presentFamily;
		bool isComplete() const {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

	#ifdef TDEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif // TDEBUG
}