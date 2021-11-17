#include "Actor.h"
#include "Engine.h"
#include "Graphics/Renderer.h"
#include "Component/GraphicComponent.h"
#include <algorithm>

namespace PhoenixEngine
{
	Actor::Actor(const Actor& other)
	{
		tag = other.tag;
		name = other.name;
		transform = other.transform;
		scene = other.scene;

		for (auto& component : other.components)
		{
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			clone->owner = this;
			clone->Create();
			AddComponent(std::move(clone));
		}
	}

	void Actor::Update(float dt)
	{
		if (!active)
		{
			return;
		}

		std::for_each(components.begin(), components.end(), [](auto& component) { component->Update(); });
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Renderer* renderer)
	{
		if (!active)
		{
			return;
		}

		std::for_each(components.begin(), components.end(), [renderer](auto& component) {
			if (dynamic_cast<GraphicComponent*>(component.get()))
			{
				dynamic_cast<GraphicComponent*>(component.get())->Draw(renderer);
			}
		});
		std::for_each(children.begin(), children.end(), [renderer](auto& child) {child->Draw(renderer); });
	}

	void Actor::BeginContact(Actor* other)
	{
		Event event;

		event.name = "collision_enter";
		event.data = other;
		event.receiver = this;

		scene->engine->Get<EventSystem>()->Notify(event);

		//std::cout << "begin: " << other->tag << std::endl;
	}

	void Actor::EndContact(Actor* other)
	{
		Event event;

		event.name = "collision_exit";
		event.data = other;
		event.receiver = this;

		scene->engine->Get<EventSystem>()->Notify(event);

		//std::cout << "end: " << other->tag << std::endl;
	}

	void Actor::AddChild(std::unique_ptr<Actor> child)
	{
		child->parent = this;
		children.push_back(std::move(child));
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		components.push_back(std::move(component));
	}

	bool Actor::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	
	bool Actor::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, tag);
		JSON_READ(value, name);

		if (value.HasMember("transform"))
		{
			transform.Read(value["transform"]);
		}

		if (value.HasMember("components") && value["components"].IsArray())
		{
			for (auto& componentValue : value["components"].GetArray())
			{
				std::string type;
				JSON_READ(componentValue, type);

				auto component = ObjectFactory::Instance().Create<Component>(type);
				if (component)
				{
					component->owner = this;
					component->Read(componentValue);
					component->Create();
					AddComponent(std::move(component));
				}
			}
		}

		return true;
	}
}