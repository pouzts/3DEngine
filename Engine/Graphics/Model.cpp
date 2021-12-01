#include "Model.h"

namespace PhoenixEngine
{
	bool Model::Load(const std::string& name, void* data)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			SDL_Log("ERROR::ASSIMP::%s", importer.GetErrorString());
			return false;
		}

		ProcessNode(scene->mRootNode, scene);

		return true;
	}

	void Model::Draw(GLenum primitiveType)
	{
		vertexBuffer.Draw(primitiveType);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// process the current node meshes
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}
		// process the current node children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<vertex_t> vertices;

		// get model vertex attributes
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			vertex_t vertex;

			vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

			if (mesh->mTextureCoords[0])
			{
				vertex.texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
			}
			else
			{
				vertex.texcoord = { 0, 0 };
			}

			vertices.push_back(vertex);
		}

		// create vertex buffer and attributes
		vertexBuffer.CreateVertexBuffer((GLsizei)(sizeof(vertex_t) * vertices.size()), (GLsizei)vertices.size(), vertices.data());
		vertexBuffer.SetAttribute(0, 3, sizeof(vertex_t), 0);
		vertexBuffer.SetAttribute(1, 3, sizeof(vertex_t), offsetof(vertex_t, normal));
		vertexBuffer.SetAttribute(2, 2, sizeof(vertex_t), offsetof(vertex_t, texcoord));

		// get model index vertices
		std::vector<GLuint> indices;
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// create index vertex buffer
		vertexBuffer.CreateIndexBuffer(GL_UNSIGNED_INT, (GLsizei)indices.size(), indices.data());
	}
}
