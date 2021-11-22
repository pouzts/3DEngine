#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"
#include <vector>

namespace PhoenixEngine
{
	class VertexBuffer : public Resource
	{
	public:
		virtual ~VertexBuffer();
		
		bool Load(const std::string& filename, void* data = nullptr) override;
		
		void CreateVertexBuffer(GLsizei size, GLsizei vertexCount, void* data);
		void SetAttribute(int index, GLint size, GLsizei stride, size_t offset);

		virtual void Draw(GLenum primativeType = GL_TRIANGLES);

		void Bind() { glBindVertexArray(vao); }
	protected:
		GLuint vao{ 0 }; // vertex array object
		GLuint vbo{ 0 }; // vertex buffer object
		
		GLuint vertexCount{ 0 }; // number of vertices in vertex buffer
	};
}