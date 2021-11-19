#pragma once
#include "Program.h"
#include "Texture.h"

namespace PhoenixEngine
{
	struct Material
	{
	public:
		Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess) :
			ambient{ ambient },
			diffuse{ diffuse },
			specular{ specular },
			shininess{ shininess }
		{}

		void Bind();
		void SetProgram(Program& program);
		void AddTexture(const std::shared_ptr<Texture>& texture) { textures.push_back(texture); }

	public:
		glm::vec3 ambient = glm::vec3{ 0 };
		glm::vec3 diffuse = glm::vec3{ 1 };
		glm::vec3 specular = glm::vec3{ 1 };
		float shininess = 100.0f;

		std::vector<std::shared_ptr<Texture>> textures;
	};
}
