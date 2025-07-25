cmake_minimum_required(VERSION 3.10)

# Create a library target
add_library(PokerEngine
    "camera.cpp"
    "indexBuffer.cpp"
    "mesh.cpp"
    "model.cpp"
    "scene.cpp"
    "shader.cpp"
    "utils.cpp"
    "vertexBuffer.cpp"
    "windowManager.cpp"
    "windowManager.h"
)

target_link_libraries(PokerEngine PRIVATE glad glfw glfw)