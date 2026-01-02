#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <string>
#include <string>
#include <memory>

#include "shader.h"

#define GUI_VERTEX_SHADER_PATH "/shaders/gui_vert.glsl"
#define GUI_FRAGMENT_SHADER_PATH "/shaders/gui_frag.glsl"

using namespace std;

static Shader* guiShader = nullptr;

class Gui {
public:
    Gui();
    ~Gui();
    void init(int width, int height);
    void render();

    void addElement(string path, string name);
    void showElement(string name, bool show);
    void bindStringToElement(string name, string dataName, string* bindString);
    void initElement(string name);
    void deleteElement(string name);
    void bindButtonToElement(string name, bool* callback);
    void SetElementText(string name, string id, string text);

    void changeContextDimensions(int width, int height);
    void processKeyDown(int key);
    void processKeyUp(int key);
    void processChar(unsigned int codepoint);
    void processMouseMove(int x, int y);
    void processMouseButtonDown(int buttonIndex);
    void processMouseButtonUp(int buttonIndex);
private:
    struct RmlImpl;
    std::unique_ptr<RmlImpl> rmlImpl;

    int width;
    int height;
};