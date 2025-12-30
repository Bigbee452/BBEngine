#pragma once
#include "../windowManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLWindow : public Window {
public:
    ~OpenGLWindow();
    void render_frame() override;

    bool shouldStop() override;
    bool getKey(int key) override;
protected:
    GLFWwindow* window;
    bool initRenderer(int width, int height) override;

    static void opengl_framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void opengl_processInput(GLFWwindow *window);
    static void opengl_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void opengl_character_callback(GLFWwindow* window, unsigned int codepoint);
    static void opengl_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void opengl_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};