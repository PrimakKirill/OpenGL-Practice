#pragma once

#include "GLEW/include/GL/glew.h"

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetIndices(const unsigned int* data, unsigned int numberOfElements);
	inline unsigned int GetCount() const { return m_Count; }

	inline unsigned int GetID() const { return m_RendererID; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};

