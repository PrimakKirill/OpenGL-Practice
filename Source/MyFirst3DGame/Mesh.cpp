#include "Mesh.h"
#include <iostream>

//»нициализаци€ вектора, хран€щего текстуры дл€ всех мэшей
std::vector<Texture> Mesh::texture_Vector;

Mesh::Mesh():
	m_Matrix(glm::mat4(1.0f)),m_Texture(nullptr)
{
}

void Mesh::SetDataToBuffers(const aiMesh *mesh, const aiScene *scene, std::string modelPath)
{
	std::vector<float> verticec;
	std::vector<unsigned int> index;
	m_lay.Push<float>(3);
	m_lay.Push<float>(3);
	if (mesh->mTextureCoords[0]) // сетка обладает набором текстурных координат?
		m_lay.Push<float>(2);
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		verticec.push_back(mesh->mVertices[i].x);
		verticec.push_back(mesh->mVertices[i].y);
		verticec.push_back(mesh->mVertices[i].z);
		verticec.push_back(mesh->mNormals[i].x);
		verticec.push_back(mesh->mNormals[i].y);
		verticec.push_back(mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0]) // сетка обладает набором текстурных координат?
		{
			verticec.push_back(mesh->mTextureCoords[0][i].x);
			verticec.push_back(mesh->mTextureCoords[0][i].y);
		}
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			index.push_back(face.mIndices[j]);
		}
	}

	m_VB.Bind();
	m_VA.Bind();
	m_VB.SetData(&(verticec[0]), verticec.size() * sizeof(float));
	m_VA.SetBuffer(m_VB, m_lay);
	
	m_IB.Bind();
	m_IB.SetIndices(&(index[0]), index.size());
	m_VB.Unbind();
	m_VA.Unbind();
	m_IB.Unbind();
	
	SetTextures(mesh,scene,modelPath);
}

void Mesh::SetTextures(const aiMesh *mesh, const aiScene *scene, std::string modelPath)
{
	//diffuse texture
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
	aiString str;
	mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
	std::string texPath = modelPath;

	if (texPath.rfind("/") >= 0 && texPath.rfind("/") < 1024)
		texPath.resize(texPath.rfind("/") + 1);
	else texPath.resize(0);
	texPath += str.C_Str();
	
	
	if(texture_Vector.size()==0)
		texture_Vector.reserve(100);
	for (int i = 0; i < texture_Vector.size(); i++)
	{
		if (texPath == texture_Vector[i].GetFilePath())
		{
			m_Texture = &texture_Vector[i];
			break;
		}
	}
	if (m_Texture == nullptr)
	{
		std::cout << texPath << std::endl;
		texture_Vector.resize(texture_Vector.size() + 1);
		texture_Vector[texture_Vector.size() - 1].Bind(texture_Vector[texture_Vector.size() - 1].GetID());
		texture_Vector[texture_Vector.size() - 1].SetTexture(texPath);
		texture_Vector[texture_Vector.size() - 1].Unbind();
		m_Texture = &texture_Vector[texture_Vector.size() - 1];
	}
	
	
	//spec texture
	/*aiString spec;
	mat->GetTexture(aiTextureType_SPECULAR, 1, &spec);
	std::string specTexPath = modelPath;
	
	if (specTexPath.rfind("/") >= 0 && specTexPath.rfind("/") < 1024)
		specTexPath.resize(specTexPath.rfind("/") + 1);
	else specTexPath.resize(0);
	specTexPath += spec.C_Str();
	std::cout << specTexPath << std::endl;

	m_SpecTexture.Bind(m_SpecTexture.GetID());
	m_SpecTexture.SetTexture(specTexPath);
	m_SpecTexture.Unbind();*/
}


Mesh::~Mesh()
{
}



