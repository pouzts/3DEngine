#pragma once
#include "Component.h"

namespace PhoenixEngine
{
	class Renderer;

	class GraphicComponent : public Component
	{
	public:
		virtual void Draw(Renderer* renderer) = 0;
	};
}