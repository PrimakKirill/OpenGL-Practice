#pragma once
#include <string>
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "assimp\config.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"


class Mesh
{
public:
	Mesh();
	void SetDataToBuffers(const aiMesh *mesh, const aiScene *scene, std::string modelPath);
	void SetTextures(const aiMesh *mesh, const aiScene *scene, std::string modelPath);
	~Mesh();
	IndexBuffer m_IB;
	VertexArray m_VA;
	VertexBuffer m_VB;
	
	inline Mesh SetMesh(Mesh mesh) {return mesh; };
	glm::mat4 m_Matrix;
	Texture* m_Texture;
	Texture m_SpecTexture;
	VertexBufferLayout m_lay;

	static std::vector<Texture> texture_Vector;//¬ектор текстур всех мешей(общий дл€ всех)
	
};

