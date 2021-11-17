#pragma once
#include <iostream>

namespace PhoenixEngine
{
	template<class T>
	class Singleton
	{
	public:
		Singleton(const Singleton&) = delete;
		Singleton& operator = (const Singleton&) = delete;

		static T& Instance() {
			static T instance;
			return instance;
		}

	protected:
		Singleton() {}
	};

	//extern Singleton singleton;
}