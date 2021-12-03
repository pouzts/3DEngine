#pragma once

#define REGISTER_CLASS(class) PhoenixEngine::ObjectFactory::Instance().Register<class>(#class);
#define CREATE_ENGINE_OBJECT(class) PhoenixEngine::ObjectFactory::Instance().Create<PhoenixEngine::class>(#class);

// Core
#include "Core/Json.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Utilities.h"
#include "Core/Serializable.h"

// Framework
#include "Framework/EventSystem.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"

// Math
#include "Math/MathTypes.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

// Audio
#include "Audio/AudioSystem.h"

// Component
#include "Component/PhysicsComponent.h"
#include "Component/AudioComponent.h"
#include "Component/CameraComponent.h"
#include "Component/FreeCameraController.h"
#include "Component/MeshComponent.h"
#include "Component/ModelComponent.h"
#include "Component/LightComponent.h"

// Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/Model.h"
#include "Graphics/Program.h"
#include "Graphics/VertexBuffer.h"

// Resource
#include "Resource/ResourceSystem.h"

// Objects
#include "Object/Scene.h"
#include "Object/Actor.h"

//Input
#include "Input/InputSystem.h"

#include <vector>
#include <memory>
#include <algorithm>

namespace PhoenixEngine
{
	using ObjectFactory = Singleton<Factory<std::string, Object>>;

	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Renderer* renderer);

		template <typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}