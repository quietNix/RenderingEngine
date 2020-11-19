#pragma once
#include <string>
#include <unordered_map>
#include "GLCheckError.h"
using namespace std;
#include "glm/glm.hpp"


struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader {
private:
	unsigned int m_ShaderID;
	std::string m_filepath;
	//caching for uniforms
	std::unordered_map<std::string, int>m_uniformLocationCase;
	

public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;

	//Set Uniform
	void SetUniform1i(const std::string& name, int v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	

	
private:
	void Shaders(unsigned int& shader);
	ShaderProgramSource ParseShader(const string& filePath);
	unsigned int CreateShader(const string& vertextShader, const string& fragmentShader);
	unsigned int CompileShader(const unsigned int& type, const string& source);
	int GetUniformLocation(const std::string& name);
};