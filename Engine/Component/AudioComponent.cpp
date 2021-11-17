#include "Component/AudioComponent.h"
#include "Engine.h"

namespace PhoenixEngine
{
	void AudioComponent::Update()
	{
		if (playOnAwake && !played)
		{
			played = true;
			Play();
		}
	}

	void AudioComponent::Play()
	{
		channel.Stop();
		channel = owner->scene->engine->Get<AudioSystem>()->PlayAudio(soundName, volume, pitch, loop);
	}

	void AudioComponent::Stop()
	{
		channel.Stop();
	}

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, soundName);
		JSON_READ(value, volume);
		JSON_READ(value, pitch);
		JSON_READ(value, loop);
		JSON_READ(value, playOnAwake);

		// add the audio to the audio system if there's a valid soundName string
		if (soundName != "") owner->scene->engine->Get<AudioSystem>()->AddAudio(soundName, soundName);

		return true;
	}
}
