#include "Timer.h"

namespace PhoenixEngine
{
	Timer::clock_tick_type Timer::ElapsedTicks()
	{
		clock_duration duration = clock::now() - timePoint;
		return duration.count();
	}

	float Timer::ElapsedSeconds()
	{
		return ElapsedTicks() / static_cast<float>(clock_duration::period::den);
	}
	
	void FrameTimer::Tick()
	{
		clock_duration duration = clock::now() - startTimePoint;
		time = duration.count() / static_cast<float>(clock_duration::period::den);

		duration = clock::now() - frameTimePoint;
		deltaTime = duration.count() / static_cast<float>(clock_duration::period::den) * timeScale;

		frameTimePoint = clock::now();
	}
}