#pragma once
#include "Program.h"
#include "Texture.h"

namespace PhoenixEngine
{
	struct Material : public Resource
	{
	public:
		bool Load(const std::string& filename, void* data = nullptr) override;

		void Set();
		void SetShader(const std::shared_ptr<Program>& shader) { this->shader = shader; }
		void AddTexture(const std::shared_ptr<Texture>& texture) { textures.push_back(texture); }

	public:
		glm::vec3 ambient{ 0 };
		glm::vec3 diffuse{ 1 };
		glm::vec3 specular{ 1 };
		float shininess{ 100 };

		std::shared_ptr<Program> shader;
		std::vector<std::shared_ptr<Texture>> textures;
	};

}
