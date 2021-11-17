#pragma once
#include "Core/Serializable.h"
#include "Object/Object.h"

namespace PhoenixEngine
{
	class Actor;

	class Component : public Object, public ISerializable
	{
	public:
		virtual void Update() = 0;

	public:
		Actor* owner{nullptr};
	};
}