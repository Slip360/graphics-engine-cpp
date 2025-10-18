#pragma once

#include <string>
#include <glm/glm.hpp>
#include <iostream>

/// @brief A simple shader program class for handling OpenGL shaders.
class Shader {
public:
    /// @brief Constructs a shader program from vertex and fragment shader source files.
    /// @param vertexPath The file path to the vertex shader.
    /// @param fragmentPath The file path to the fragment shader.
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    /// @brief Destructor to clean up the shader program.
    ~Shader();
    /// @brief Activates the shader program.
    void use() const;
    /// @brief Retrieves the OpenGL ID of the shader program.
    /// @return The OpenGL shader program ID.
    unsigned int getId() const;
    /// @brief Sets a 3x3 matrix uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param mat The 3x3 matrix to set.
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    /// @brief Sets a 4x4 matrix uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param mat The 4x4 matrix to set.
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    /// @brief Sets a boolean uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param value The boolean value to set.
    void setBool(const std::string& name, bool value) const;
    /// @brief Sets an integer uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param value The integer value to set.
    void setInt(const std::string& name, int value) const;
    /// @brief Sets a float uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param value The float value to set.
    void setFloat(const std::string& name, float value) const;
    /// @brief Sets a 2D vector uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param vec The 2D vector to set.
    void setVec2(const std::string& name, const glm::vec2& vec) const;
    /// @brief Sets a 3D vector uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param vec The 3D vector to set.
    void setVec3(const std::string& name, const glm::vec3& vec) const;
    /// @brief Sets a 4D vector uniform in the shader.
    /// @param name The name of the uniform variable in the shader.
    /// @param vec The 4D vector to set.
    void setVec4(const std::string& name, const glm::vec4& vec) const;

private:
    /// @brief The OpenGL shader program ID.
    unsigned int Id;
    /// @brief Loads shader source code from a file.
    /// @param path The file path to the shader source code.
    /// @return The shader source code as a string.
    std::string loadShaderSource(const std::string& path) const;
    /// @brief Checks for shader compilation and linking errors.
    /// @param shader The shader or program ID.
    /// @param type The type of shader ("VERTEX", "FRAGMENT", "PROGRAM").
    void checkCompileErrors(unsigned int shader, const std::string& type) const;
};
