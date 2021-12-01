#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"
#include <vector>

namespace PhoenixEngine
{
	class VertexBuffer : public Resource
	{
	public:
		VertexBuffer();
		virtual ~VertexBuffer();
		
		bool Load(const std::string& filename, void* data = nullptr) override;
		
		// vertex buffer
		void CreateVertexBuffer(GLsizei size, GLsizei vertexCount, void* data);
		void SetAttribute(int index, GLint size, GLsizei stride, size_t offset);

		// vertex index buffer
		void CreateIndexBuffer(GLenum indexType, GLsizei count, void* data);

		virtual void Draw(GLenum primativeType = GL_TRIANGLES);

		void Bind() { glBindVertexArray(vao); }
	protected:
		GLuint vao{ 0 }; // vertex array object
		GLuint vbo{ 0 }; // vertex buffer object
		GLuint vertexCount{ 0 }; // number of vertices in vertex buffer

		GLuint ibo = 0; 		// index buffer object
		GLuint indexCount = 0;  // number of indices in index buffer
		GLenum indexType = 0;	// data type of index (GLushort or GLuint)

	};
}