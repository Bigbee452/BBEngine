set(ENGINE_SRC  "camera.cpp"
                "indexBuffer.cpp"
                "mesh.cpp"
                "model.cpp"
                "scene.cpp"
                "shader.cpp"
                "utils.cpp"
                "vertexBuffer.cpp"
                "windowManager.cpp"
                "windowManager.h"
                "gui.cpp"
                "opengl/openGLWindowManager.cpp"
                "../include/stb_image.h"
                "../include/stb_image.cpp")

add_library(BBEngine STATIC ${ENGINE_SRC})