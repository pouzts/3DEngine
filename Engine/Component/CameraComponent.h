#pragma once
#include "Component.h"


namespace PhoenixEngine
{
	class CameraComponent : public Component
	{
	public:
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update() override;

		void SetPerspective(float fov, float aspectRatio, float near, float far);

	public:
		glm::mat4 projection{ 1 };
		glm::mat4 view{ 1 };
	};
}
