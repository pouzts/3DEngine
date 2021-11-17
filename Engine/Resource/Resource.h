#pragma once
#include <string>

namespace PhoenixEngine
{
	class Resource
	{
	public:
		virtual bool Load(const std::string& filename, void* data = nullptr) = 0;
	};
}