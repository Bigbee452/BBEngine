#include "openGLWindowManager.h"

#include <iostream>

OpenGLWindow::~OpenGLWindow(){
    glfwTerminate();
}

bool OpenGLWindow::shouldStop(){
    return glfwWindowShouldClose(window);
}

bool OpenGLWindow::getKey(int key){
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool OpenGLWindow::initRenderer(int width, int height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, this->opengl_framebuffer_size_callback);
    glfwSetKeyCallback(window, this->opengl_key_callback);
    glfwSetCharCallback(window, this->opengl_character_callback);
    glfwSetCursorPosCallback(window, this->opengl_cursor_position_callback);
    glfwSetMouseButtonCallback(window, this->opengl_mouse_button_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);  
    glEnable(GL_CULL_FACE);  
    glFrontFace(GL_CW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    return 1;
}

void OpenGLWindow::render_frame(){
    // input
    // -----
    processInput();

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    

    Window::render_frame();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGLWindow::opengl_framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    framebuffer_size_callback(width, height);    
}

void OpenGLWindow::opengl_processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    processInput();
}

void OpenGLWindow::opengl_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    key_callback(key, scancode, action, mods);
}

void OpenGLWindow::opengl_character_callback(GLFWwindow* window, unsigned int codepoint){
    character_callback(codepoint);
}

void OpenGLWindow::opengl_cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    cursor_position_callback(xpos, ypos);
}

void OpenGLWindow::opengl_mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    mouse_button_callback(button, action, mods);
}