#include "IndexBuffer.h"



IndexBuffer::IndexBuffer()	
	:m_Count(0)
{
	glGenBuffers(1, &m_RendererID);	
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetIndices(const unsigned int * data, unsigned int numberOfElements)
{
	m_Count = numberOfElements;	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfElements * sizeof(unsigned int), data, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
