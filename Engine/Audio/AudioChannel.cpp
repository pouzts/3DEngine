#include "AudioChannel.h"

namespace PhoenixEngine
{
	bool AudioChannel::IsPlaying()
	{
		if (channel == nullptr) return false;
		
		bool isPlaying = false;
		
		if (channel)
		{
			channel->isPlaying(&isPlaying);
		}

		return isPlaying;
	}

	void AudioChannel::Stop()
	{
		if (IsPlaying())
		{
			channel->stop();
		}
	}
	
	void AudioChannel::SetPitch(float pitch)
	{
		if (IsPlaying())
		{
			channel->setPitch(pitch);
		}
	}

	float AudioChannel::GetPitch()
	{
		float pitch = 0.0f;

		if (IsPlaying())
		{
			channel->setPitch(pitch);
		}

		return pitch;
	}
	
	void AudioChannel::SetVolume(float volume)
	{
		if (IsPlaying())
		{
			channel->setPitch(volume);
		}
	}

	float AudioChannel::GetVolume()
	{
		float volume = 0.0f;
		if (IsPlaying())
		{
			channel->setPitch(volume);
		}
		return volume;
	}
}
