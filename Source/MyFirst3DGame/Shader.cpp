#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



Shader::Shader(const std::string & filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	  
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Undind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	glUseProgram(m_RendererID);
	glUniform1i(GetUniformLocation(name), value);
}



void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	glUseProgram(m_RendererID);
	glUniform4f(GetUniformLocation(name), v0, v1, v2 , v3);
}

void Shader::SetUniform3f(const std::string & name, float v0, float v1, float v2)
{
	glUseProgram(m_RendererID);
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniformMat4x3f(const std::string & name, const glm::mat4x3 & matrix)
{
	glUseProgram(m_RendererID);
	glUniformMatrix4x3fv(GetUniformLocation(name),1,GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 & matrix)
{
	glUseProgram(m_RendererID);
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

 int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCash.find(name) != m_UniformLocationCash.end())
		return m_UniformLocationCash[name];
	unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "ERROR" << std::endl;
	
	m_UniformLocationCash[name] = location;
	return location;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


ShaderProgramSource Shader::ParseShader(const std::string& filepath) {

	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}

	}

	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//ERRORS
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_COMPILE_STATUS, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
