#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);	
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
	glBindVertexArray(m_RendererID);
	vb.Bind();
	const auto& elementes = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elementes.size(); i++)
	{
		const auto& elemente = elementes[i];
		glEnableVertexAttribArray(i);//просто нужно
		glVertexAttribPointer(i, elemente.count, elemente.type,
			elemente.normalized, layout.GetStride(), (const void*)offset);//говорим как хранятся данные в выбранном буффере
		offset += elemente.count * VertexBufferElement::GetSizeOfType(elemente.type);
	}
}
