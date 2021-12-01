#pragma once
#include "Component.h"

namespace PhoenixEngine
{
	class LightComponent : public Component
	{
	public:
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 ambient{ 0 };
		glm::vec3 diffuse{ 1 };
		glm::vec3 specular{ 1 };
	};
}