#include "CameraComponent.h"
#include "Object/Actor.h"

namespace PhoenixEngine
{
	void CameraComponent::Update()
	{
		glm::vec4 direction = owner->transform.matrix * glm::vec4{ 0, 0, -1, 0 };
		view = glm::lookAt(owner->transform.position, owner->transform.position + glm::vec3{ direction }, glm::vec3{ 0, 1, 0 });
	}

	void CameraComponent::SetPerspective(float fov, float aspectRatio, float near, float far)
	{
		projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
	}

	bool CameraComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool CameraComponent::Read(const rapidjson::Value& value)
	{
		return true;
	}
}