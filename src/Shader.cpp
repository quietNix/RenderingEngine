#include <iostream>
#include "Shader.h"
#include <fstream>
#include <sstream>


Shader::Shader(const string& filepath)
	:m_filepath(filepath), m_ShaderID(0)
{
    Shaders(m_ShaderID);
}

Shader::~Shader() {
    //glDeleteProgram(m_ShaderID);
}

void Shader::Bind() const{
    glUseProgram(m_ShaderID);
}

void Shader::Unbind() const{
    glUseProgram(0); 

}

void Shader::SetUniform1i(const std::string& name, int v0) {
    GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


int Shader::GetUniformLocation(const std::string& name) {
    if (m_uniformLocationCase.find(name) != m_uniformLocationCase.end())
        return m_uniformLocationCase[name];

    int location = glGetUniformLocation(m_ShaderID, name.c_str());
    if (location == -1)
        cout << "warning uniform" + name + "doesnt exist"<<location;
    else
        cout<<"uniform exist" + name<<location;
    m_uniformLocationCase[name] = location;
    return location;
}


void Shader::Shaders(unsigned int& shader)
{
    ShaderProgramSource source = ParseShader(m_filepath);
    string vertexShader = source.VertexSource;
    string fragmentShader = source.FragmentSource;
    cout << endl << vertexShader << endl;
    cout << fragmentShader << endl;
    shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);       //binding shader with shaderId
}

ShaderProgramSource Shader::ParseShader(const string& filePath) {
    ifstream stream(filePath);
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const string& vertextShader, const string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertextShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

unsigned int Shader:: CompileShader(const unsigned int& type, const string& source) {
    unsigned int id = glCreateShader(type);
    //source must be alive, else garbage
    //const char* str = source.c_str();
    const char* str = &source[0];
    glShaderSource(id, 1, &str, nullptr);
    glCompileShader(id);

    //Error handling code
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message{ nullptr };
        message = new char[length * sizeof(char)];
        glGetShaderInfoLog(id, length, &length, message);
        cout << endl << "failed to compile: ";
        cout << message << endl << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << endl;
        glDeleteShader(id);
        return 1;
    }
    return id;
}










