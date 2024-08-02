#pragma once
#include "Defines.h"
#include <vector>
#include <string>

namespace ThaumaEngine
{
	namespace FileReader
	{
		std::vector<char> ReadFileBinary(const std::string& filename);
	}
} // namespace ThaumaEngine

