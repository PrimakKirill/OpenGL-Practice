#pragma once

#include "GLEW/include/GL/glew.h"

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, unsigned int sizeInBytes);

private:
	unsigned int m_RendererID;
};

