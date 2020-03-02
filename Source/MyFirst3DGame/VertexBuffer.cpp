#include "VertexBuffer.h"



VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_RendererID);	
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, unsigned int sizeInBytes)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
}
