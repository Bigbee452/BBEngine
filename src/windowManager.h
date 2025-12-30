#pragma once
#include "scene.h"

#include "gui.h"

class Window {
public:
    Window();
    virtual ~Window() = default;
    bool init(int width, int height);
    void setScene(Scene* in_scene);
    virtual void render_frame();
    virtual bool shouldStop();
    virtual bool getKey(int key);

    static inline Gui* gui;
protected:
    static inline Scene* scene;
    virtual bool initRenderer(int width, int height);
    static void framebuffer_size_callback(int width, int height);
    static void processInput();
    static void key_callback(int key, int scancode, int action, int mods);
    static void character_callback(unsigned int codepoint);
    static void cursor_position_callback(double xpos, double ypos);
    static void mouse_button_callback(int button, int action, int mods);
};

Window* getWindow();