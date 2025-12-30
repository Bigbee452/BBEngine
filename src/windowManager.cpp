#include "windowManager.h"
#include "mesh.h"
#include "scene.h"

#include "opengl/openGLWindowManager.h"

Window::Window(){
     
}

bool Window::init(int width, int height){
    initRenderer(width, height);

    stbi_set_flip_vertically_on_load(true);

    gui = new Gui;
    gui->init(width, height);
    return true;
}

void Window::setScene(Scene* in_scene){
    scene = in_scene;    
}

void Window::render_frame(){
    if(scene != nullptr){
        scene->draw();
    }

    gui->render();
}

void Window::framebuffer_size_callback(int width, int height){
    if(scene != nullptr){
        scene->set_projection(width, height);
    }
    gui->changeContextDimensions(width, height);
}

void Window::processInput()
{
    
}

void Window::key_callback(int key, int scancode, int action, int mods){
    if(action == 1){
        gui->processKeyDown(key);
    }
}

void Window::character_callback(unsigned int codepoint){
    gui->processChar(codepoint);
}

void Window::cursor_position_callback(double xpos, double ypos){
    gui->processMouseMove((int)xpos, (int)ypos);
}

void Window::mouse_button_callback(int button, int action, int mods){
    if(action == 1){
        gui->processMouseButtonDown(button);
    } else if(action == 0){
        gui->processMouseButtonUp(button);
    }
}

Window* getWindow(){
    OpenGLWindow* window = new OpenGLWindow();
    return window;
}