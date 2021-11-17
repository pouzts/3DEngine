#include "Core\FileSystem.h"
#include <filesystem>

void PhoenixEngine::SetFilePath(const std::string& pathname)
{
	std::filesystem::current_path(pathname);
}

std::string PhoenixEngine::GetFilePath()
{
	return std::filesystem::current_path().string();
}
