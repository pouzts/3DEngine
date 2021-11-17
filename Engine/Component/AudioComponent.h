#pragma once
#include "Component.h"
#include "Audio/AudioChannel.h"
#include <string>

namespace PhoenixEngine
{
	class AudioComponent : public Component
	{
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<AudioComponent>(*this); }

		virtual void Update() override;

		void Play();
		void Stop();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::string soundName;
		float volume{ 1 };
		float pitch{ 1 };
		bool loop{ false };
		bool playOnAwake{ false };

	private:
		AudioChannel channel;
		bool played{ false };
	};
}
