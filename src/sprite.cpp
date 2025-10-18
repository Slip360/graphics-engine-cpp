#include "sprite.h"
#include <glad.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Sprite::Sprite(const std::string& texturePath)
    : position(0.0f), scale(1.0f), rotation(0.0f) {
    loadTexture(texturePath);
    setupQuad();
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &textureId);
}

void Sprite::setPosition(const glm::vec2& pos) {
    position = pos;
}

void Sprite::setScale(const glm::vec2& scl) {
    scale = scl;
}

void Sprite::setRotation(float angle) {
    rotation = angle;
}

void Sprite::draw(Shader& shader) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f)); // centro
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0f));

    shader.use();
    shader.setMat4("model", model);
    shader.setVec4("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Sprite::setColor(const glm::vec4& col) {
    color = col;
}

void Sprite::update(float deltaTime) {
    // Aquí puedes animar, mover, etc.
}

void Sprite::loadTexture(const std::string& path) {
    // Opcional: invertir verticalmente las imágenes (útil para coord. de textura convencionales)
    // stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Parámetros de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // o GL_REPEAT según tu caso
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // o GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // mejor sampling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width = 0, height = 0, channels = 0;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4); // fuerza RGBA

    if (!data) {
        std::cerr << "Error: no se pudo cargar la textura " << path << std::endl;
        // Limpia el objeto de textura para evitar usos posteriores inválidos
        glDeleteTextures(1, &textureId);
        textureId = 0;
        textureWidth = 0;
        textureHeight = 0;
        return;
    }

    // Guarda tamaño para el quad
    textureWidth = width;
    textureHeight = height;

    // Sube la imagen a GPU
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    // Libera la imagen en CPU
    stbi_image_free(data);

    // Desvincula textura (opcional, por orden)
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::setupQuad() {
    float vertices[] = {
        // Posición             // TexCoords
        0.0f, (float)textureHeight, 0.0f, 1.0f,
        (float)textureWidth, 0.0f,  1.0f, 0.0f,
        0.0f, 0.0f,             0.0f, 0.0f,

        0.0f, (float)textureHeight, 0.0f, 1.0f,
        (float)textureWidth, (float)textureHeight, 1.0f, 1.0f,
        (float)textureWidth, 0.0f,  1.0f, 0.0f
    };

    std::cout << "Quad setup with size: "
              << textureWidth << "x" << textureHeight << std::endl;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // TexCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Desvincular
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
