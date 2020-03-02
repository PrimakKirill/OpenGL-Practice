#pragma once

//#include "Renderer.h"
#include "GLEW/include/GL/glew.h"
#include "Res/stb_image/stb_image.h"
#include <string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	

public:
	Texture();
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void SetTexture(const std::string& path);

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetID() const { return m_RendererID; }

	inline std::string GetFilePath() const { return m_FilePath; }
};

