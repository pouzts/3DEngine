#include "VertexIndexBuffer.h"

namespace PhoenixEngine
{
	VertexIndexBuffer::~VertexIndexBuffer()
	{
		if (ibo != 0) glDeleteBuffers(1, &ibo);
	}

	bool VertexIndexBuffer::Load(const std::string& filename, void* data)
	{
		VertexBuffer::Load(filename, data);
		return true;
	}

	void VertexIndexBuffer::CreateIndexBuffer(GLenum indexType, GLsizei count, void* data)
	{
		this->indexType = indexType;
		this->indexCount = count;

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
		size_t indexSize = (indexType == GL_UNSIGNED_SHORT) ? sizeof(GLushort) : sizeof(GLuint);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * indexSize, data, GL_STATIC_DRAW);
	}

	void VertexIndexBuffer::Draw(GLenum primativeType)
	{
		glBindVertexArray(vao);
		glDrawElements(primativeType, indexCount, indexType, 0);
	}
}