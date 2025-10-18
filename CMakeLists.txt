cmake_minimum_required(VERSION 3.10)
project(graphics-engine-cpp)

# Definir macro con la ruta absoluta al directorio del proyecto
add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definir macro con la ruta absoluta al directorio del proyecto
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/shader.cpp
    src/sprite.cpp
    src/glad.c
    src/stb_image.cpp
)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/include
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

find_path(GLM_INCLUDE_DIR glm/glm.hpp)
if (GLM_INCLUDE_DIR)
    include_directories(${GLM_INCLUDE_DIR})
else()
    message(WARNING "No se encontró GLM, asegúrate de instalar libglm-dev")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
)

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
