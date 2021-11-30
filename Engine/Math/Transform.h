#pragma once
#include "Math/MathTypes.h"
#include "Core/Serializable.h"

namespace PhoenixEngine
{
	struct Transform : public ISerializable
	{
		glm::vec3 position{ 0 };
		glm::vec3 rotation{ 0 };
		glm::vec3 scale{ 1 };

		glm::vec3 localPosition{ 0 };
		glm::vec3 localRotation{ 0 };
		glm::vec3 localScale{ 1 };

		glm::mat4 matrix{ 1 };

		Transform() {}
		Transform(const glm::vec3& position, const glm::vec3& rotation = glm::vec3{ 0 }, const glm::vec3& scale = glm::vec3{ 1 }) :
			position{ position }, rotation{ rotation }, scale{ scale } {}

		void Update();
		void Update(const glm::mat4& mx);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		static void DecomposeTransform(const Transform& transform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
	};
}