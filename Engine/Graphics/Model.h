#pragma once
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace PhoenixEngine
{
	class Model : public Resource
	{
	public:
		struct vertex_t
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texcoord;
			glm::vec3 tangent;
		};

	public:
		~Model() {}

		bool Load(const std::string& name, void* data) override;
		void Draw(GLenum primitiveType = GL_TRIANGLES);

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	public:
		VertexBuffer vertexBuffer;
	};
}

