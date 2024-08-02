#include "FileReader.h"
#include <fstream>

std::vector<char> ThaumaEngine::FileReader::ReadFileBinary(const std::string &filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open())
    {
		throw std::runtime_error("Failed to open file!");
	}

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}
