#pragma once
#include "Defines.h"

namespace ThaumaEngine {
	class BaseRenderer
	{
	public:
		BaseRenderer() = default;
		virtual ~BaseRenderer() = default;

		virtual void Init() = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;
	};
	} // namespace ThaumaEngine