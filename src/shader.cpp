#include "shader.h"
#include <glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Shader Program
    Id = glCreateProgram();
    glAttachShader(Id, vertex);
    glAttachShader(Id, fragment);
    glLinkProgram(Id);
    checkCompileErrors(Id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(Id);
}

void Shader::use() const {
    glUseProgram(Id);
}

unsigned int Shader::getId() const  {
    return Id;
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (mat3): " << name << std::endl;
        return;
    }
    glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (mat4): " << name << std::endl;
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setBool(const std::string& name, bool value) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (bool): " << name << std::endl;
        return;
    }
    glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (int): " << name << std::endl;
        return;
    }
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (float): " << name << std::endl;
        return;
    }
    glUniform1f(location, value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& vec) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (vec2): " << name << std::endl;
        return;
    }
    glUniform2f(location, vec.x, vec.y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (vec3): " << name << std::endl;
        return;
    }
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& vec) const {
    int location = glGetUniformLocation(Id, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING::SHADER::UNIFORM_NOT_FOUND (vec4): " << name << std::endl;
        return;
    }
    glUniform4f(location, vec.r, vec.g, vec.b, vec.a);
}

std::string Shader::loadShaderSource(const std::string& path) const {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) const {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n";
        }
    }
}


