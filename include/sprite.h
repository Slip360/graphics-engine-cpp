#pragma once

#include "shader.h"
#include <string>
#include <glm/glm.hpp>

/// @brief Represents a 2D sprite with position, scale, rotation, and texture.
class Sprite {
public:
    /// @brief Constructs a Sprite with the given texture.
    /// @param texturePath The file path to the texture image.
    Sprite(const std::string& texturePath);
    /// @brief Destructor to clean up resources.
    ~Sprite();
    /// @brief Sets the position of the sprite.
    /// @param pos The new position of the sprite.
    void setPosition(const glm::vec2& pos);
    /// @brief Sets the scale of the sprite.
    /// @param scl The new scale of the sprite.
    void setScale(const glm::vec2& scl);
    /// @brief Sets the rotation of the sprite.
    /// @param angle The new rotation angle of the sprite.
    void setRotation(float angle);
    /// @brief Draws the sprite using the given shader.
    /// @param shader The shader to use for drawing the sprite.
    void draw(Shader& shader);
    /// @brief Sets the color of the sprite.
    /// @param color The new color of the sprite.
    void setColor(const glm::vec4& color);
    /// @brief Updates the sprite's state.
    /// @param deltaTime The time elapsed since the last update.
    virtual void update(float deltaTime);

private:
    /// @brief The OpenGL texture ID.
    unsigned int textureId;
    /// @brief The Vertex Array Object ID.
    unsigned int VAO;
    /// @brief The Vertex Buffer Object ID.
    unsigned int VBO;
    /// @brief The position of the sprite.
    glm::vec2 position;
    /// @brief The scale of the sprite.
    glm::vec2 scale;
    /// @brief The rotation angle of the sprite.
    float rotation;
    /// @brief The color tint of the sprite (RGBA, white by default).
    glm::vec4 color = glm::vec4(1.0f);
    /// @brief The width of the texture in pixels.
    int textureWidth;
    /// @brief The height of the texture in pixels.
    int textureHeight;
    /// @brief Loads the texture from the given file path.
    /// @param texturePath The file path to the texture image.
    void loadTexture(const std::string& texturePath);
    /// @brief Sets up the quad geometry for the sprite.
    void setupQuad();
};
