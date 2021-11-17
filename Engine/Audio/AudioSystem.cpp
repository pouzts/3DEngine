#include "AudioSystem.h"
#include"Core/Utilities.h"

namespace PhoenixEngine
{
	void AudioSystem::Startup()
	{
		FMOD::System_Create(&fmodSystem);

		void* extradriverdata = nullptr;
		fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void AudioSystem::Shutdown()
	{
		for (auto& sound : sounds)
		{
			sound.second->release();
		}
		sounds.clear();

		fmodSystem->close();
		fmodSystem->release();
	}

	void AudioSystem::Update(float dt)
	{
		fmodSystem->update();
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{
		if (sounds.find(string_tolower(name)) == sounds.end())
		{
			FMOD::Sound* sound{ nullptr };
			fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			sounds[string_tolower(name)] = sound;
		}
	}

	AudioChannel AudioSystem::PlayAudio(const std::string& name, float volume, float pitch, bool loop)
	{
		auto iter = sounds.find(string_tolower(name));
		if (iter != sounds.end())
		{
			FMOD::Sound* sound = iter->second;
			sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
			FMOD::Channel* channel;
			fmodSystem->playSound(sound, 0, true, &channel);
			channel->setVolume(volume);
			channel->setPitch(pitch);
			channel->setPaused(false);
			return AudioChannel{ channel };
		}

		return AudioChannel{};
	}
}
