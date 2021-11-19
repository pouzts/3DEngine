#pragma once
#include <string>

namespace PhoenixEngine
{
	void SetFilePath(const std::string& pathname);
	std::string GetFilePath();
	bool ReadFileToString(const std::string& filename, std::string& filestring);
}