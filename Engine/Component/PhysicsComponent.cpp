#include "PhysicsComponent.h"
#include "Engine.h"

namespace PhoenixEngine
{
	void PhysicsComponent::Update()
	{
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
		velocity *= damping;
		acceleration = {0, 0, 0};
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, damping);
		
		return true;
	}
}