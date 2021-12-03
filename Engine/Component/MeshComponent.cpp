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
		material->shader->SetUniform("model", owner->transform.matrix);
		auto actor = owner->scene->FindActor("camera");
		if (actor != nullptr)
		{
			material->shader->SetUniform("view", actor->GetComponent<CameraComponent>()->view);
			material->shader->SetUniform("projection", actor->GetComponent<CameraComponent>()->projection);
		}

		material->Set();
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
