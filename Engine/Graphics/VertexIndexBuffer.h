#pragma once
#include "VertexBuffer.h"

namespace PhoenixEngine
{
	class VertexIndexBuffer : public VertexBuffer
	{
	public:
		~VertexIndexBuffer();
		bool Load(const std::string& filename, void* data = nullptr);

		void CreateIndexBuffer(GLenum indexType, GLsizei count, void* data);

		void Draw(GLenum primativeType = GL_TRIANGLES) override;
	protected:
		GLuint ibo{ 0 }; // index buffer object

		GLuint indexCount{ 0 }; // # of indices in ibo
		GLenum indexType{ 0 }; // data type of index
	};
}