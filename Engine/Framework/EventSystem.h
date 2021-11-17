#pragma once
#include "Framework/System.h"
#include <string>
#include <functional>
#include <map>
#include <list>
#include <variant>

namespace PhoenixEngine
{
	class Object;

	struct Event
	{
		std::string name;
		Object* receiver{ nullptr };
		std::variant<int, bool, float, std::string, void*> data;
	};

	class EventSystem : public System
	{
	public:
		using function_t = std::function<void(const Event&)>;

		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

		void Subscribe(const std::string& name, function_t function, Object* receiver = nullptr);
		void Unsubscribe(const std::string& name, Object* receiver);
		void Notify(const Event& event);
		
	private:
		struct Observer
		{
			function_t function;
			Object* receiver = nullptr;
		};

	private:
		std::map<std::string, std::list<Observer>> observers;
	};
}