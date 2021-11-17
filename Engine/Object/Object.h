#pragma once
#include <memory>

namespace PhoenixEngine
{
	class Object
	{
	public:
		virtual ~Object() {}

		virtual void Create() {}
		virtual std::unique_ptr<Object> Clone() const { return std::unique_ptr<Object>(); }
	};
}