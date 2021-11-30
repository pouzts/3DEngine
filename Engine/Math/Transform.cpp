#include "Transform.h"

namespace PhoenixEngine
{
	void Transform::Update()
	{
		glm::mat4 mxt = glm::translate(position);
		glm::mat4 mxr = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
		glm::mat4 mxs = glm::scale(scale);

		matrix = mxt * mxr * mxs;
	}

	void Transform::Update(const glm::mat4& mx)
	{
		Update();

		// multiply matrix by parent matrix
		matrix = mx * matrix;
	}

	bool Transform::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool Transform::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, position);
		JSON_READ(value, rotation);
		JSON_READ(value, scale);

		return true;
	}

	void Transform::DecomposeTransform(const Transform& transform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
	{
		position = glm::vec3{ transform.matrix[3] };
		scale = glm::vec3{ transform.matrix[0][0], transform.matrix[1][1], transform.matrix[2][2] };
		glm::extractEulerAngleYXZ(transform.matrix, rotation.y, rotation.x, rotation.z);
	}
}