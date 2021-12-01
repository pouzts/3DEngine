#include "LightComponent.h"

namespace PhoenixEngine
{
	void LightComponent::Update()
	{
	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		return false;
	}
}