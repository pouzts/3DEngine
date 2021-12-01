#pragma once
#include "GraphicComponent.h"
#include "Graphics/Material.h"
#include "Graphics/Model.h"

namespace PhoenixEngine
{
	class Renderer;

	class ModelComponent : public GraphicComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer* renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Program> program;
		std::shared_ptr<Material> material;
		std::shared_ptr<Model> model;
	};
}

