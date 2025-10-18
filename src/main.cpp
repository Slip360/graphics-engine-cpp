#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "shader.h"
#include "sprite.h"
#include <string>

#ifndef PROJECT_SOURCE_DIR
#define PROJECT_SOURCE_DIR "."
#endif

const std::string DIRECTORY_PATH = PROJECT_SOURCE_DIR;
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error: no se pudo inicializar GLFW" << std::endl;
        return -1;
    }

    // Configurar contexto OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Motor 2D", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: no se pudo crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error: no se pudo inicializar GLAD" << std::endl;
        return -1;
    }

    // Configurar viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Activar transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Cargar shaders
    std::string shadersPath = DIRECTORY_PATH + "/shaders/";
    Shader shader(shadersPath + "sprite.vert", shadersPath + "sprite.frag");

    // Configurar matrices de cámara
    glm::mat4 projection = glm::ortho(
        0.0f, (float)SCREEN_WIDTH,
        (float)SCREEN_HEIGHT, 0.0f,
        -1.0f, 1.0f
    );
    glm::mat4 view = glm::mat4(1.0f);

    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setInt("spriteTexture", 0); // textura en unidad 0

    // Crear sprite
    std::string assetsPath = DIRECTORY_PATH + "/assets/";
    Sprite sprite(assetsPath + "ejemplo.png");
    sprite.setPosition(glm::vec2(200.0f, 150.0f));
    sprite.setScale(glm::vec2(0.25f, 0.25f));
    sprite.setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Entrada
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sprite.draw(shader);

        // Intercambiar buffers y poll de eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
