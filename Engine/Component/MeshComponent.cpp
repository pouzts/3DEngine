#include "MeshComponent.h"
#include "CameraComponent.h"
#include "Object/Actor.h"

namespace PhoenixEngine
{
	void MeshComponent::Update()
	{

	}
	
	void MeshComponent::Draw(Renderer* renderer)
	{
		program->SetUniform("model", owner->transform.matrix);
		auto actor = owner->scene->FindActor("camera");
		if (actor != nullptr)
		{
			program->SetUniform("view", actor->GetComponent<CameraComponent>()->view);
			program->SetUniform("projection", actor->GetComponent<CameraComponent>()->projection);
		}

		vertexBuffer->Draw();
	}

	bool MeshComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool MeshComponent::Read(const rapidjson::Value& value)
	{
		return true;
	}
}
