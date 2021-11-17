#pragma once
namespace PhoenixEngine
{
	const float Pi = 3.14159265359f;
	const float TwoPi = 6.28318530718f;
	const float HalfPi = 1.57079632679f;
	const float QuarterPi = 0.78539816339f;

	inline float RadToDeg(float radians) 
	{
		return radians * 180.0f / Pi;
	}

	inline float DegToRad(float degree)
	{
		return degree * Pi / 180.0f;
	}

	template<typename T>
	T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}

	template<typename T>
	T Wrap(T value, T min, T max)
	{
		if (value < min) return max;
		if (value > max) return min;

		return value;
	}

	template<typename T>
	T Lerp(T a, T b, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return a + ((b - a) * t);
	}
}