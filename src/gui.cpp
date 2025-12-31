#include "gui.h"
#include <memory>
#include <vector>
#include <RmlUi/Core.h>


#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <vector>
#include "mesh.h"
#include "opengl/openGLRenderInterface.h"

class GuiObject {
public:
    GuiObject(Rml::Context* context, string path, string name);
    ~GuiObject();
    void makeDocument(Rml::Context* context);
    void showObject(bool show);
    void bindString(string name, string* bindString);
    void bindButton(bool* callback);

    string name = "None";
private:
    Rml::ElementDocument* document;
    Rml::Context* context;
    Rml::DataModelConstructor constructor;

    string path;
};

GuiObject::GuiObject(Rml::Context* context, string path, string name){
    constructor = context->CreateDataModel(name);

    this->name = name;
    this->path = path;
    this->context = context;
}

GuiObject::~GuiObject(){
    context->RemoveDataModel(name);
    if(!document){
        return;
    }
    document->Close();
    
}

void GuiObject::makeDocument(Rml::Context* context){
    document = context->LoadDocument(path);    
    if(!document){
        cerr << "Failed to make GuiObject" << endl;
    }
}

void GuiObject::bindString(string name, string* bindString){
    constructor.Bind(name, bindString);
}

void GuiObject::showObject(bool show){
    if(!document){
        return;
    }
    if(show){
        document->Show();
        return;
    }
    document->Hide();
}

void GuiObject::bindButton(bool* callback){
    Rml::Element* button = document->GetElementById("manageClick");
    if(button){
        button->AddEventListener("click", new ButtonListener(callback));
    } else {
        std::cout << "No buttons found" << endl;
    }
}

Gui::Gui(){
    
}

Gui::~Gui(){

}

struct Gui::RmlImpl {
    OpenGLRenderInterface* render_interface;
	Rml::SystemInterface* system_interface;

    Rml::Context* context;    

    vector<GuiObject*> objects;
};

void Gui::init(int width, int height){
    rmlImpl = std::make_unique<RmlImpl>();
	// Begin by installing the custom interfaces.
    rmlImpl->render_interface = new OpenGLRenderInterface();
    rmlImpl->system_interface = new Rml::SystemInterface();
	Rml::SetRenderInterface(rmlImpl->render_interface);
	Rml::SetSystemInterface(rmlImpl->system_interface);    
    Rml::Initialise();
    rmlImpl->context = Rml::CreateContext("main", Rml::Vector2i(width, height));
	if (!rmlImpl->context)
	{
		Rml::Shutdown();
        std::cerr << "failed to create Rml context" << std::endl;
	}

    struct FontFace {
		const char* filename;
		bool fallback_face;
	};

	FontFace font_faces[] = {
		{"LatoLatin-Regular.ttf", false},
		{"LatoLatin-Italic.ttf", false},
		{"LatoLatin-Bold.ttf", false},
		{"LatoLatin-BoldItalic.ttf", false},
		{"NotoEmoji-Regular.ttf", true},
	};

    for (const FontFace& face : font_faces){
        Rml::LoadFontFace(execute_path + "/fonts/" + face.filename, face.fallback_face);
    }    
}

void Gui::render(){
    rmlImpl->context->Update();
    rmlImpl->context->Render();
}

void Gui::addElement(string path, string name){
    for(GuiObject* element : rmlImpl->objects){
        if(element->name == name){
            std::cerr << "trying to add GUI element with the same name as another. name: " << name << endl;
            return;
        }
    }
    GuiObject* object = new GuiObject(rmlImpl->context, path, name);
    rmlImpl->objects.push_back(object);
}

void Gui::initElement(string name){
    for(GuiObject* element : rmlImpl->objects){
        if(element->name == name){
            element->makeDocument(rmlImpl->context);
            return;
        }
    }    
}

void Gui::deleteElement(string name){
    for(int i = 0; i < rmlImpl->objects.size(); i++){
        if(rmlImpl->objects[i]->name == name){
            delete rmlImpl->objects[i];
            rmlImpl->objects.erase(rmlImpl->objects.begin()+i);
        }
    }  
}

void Gui::bindStringToElement(string name, string dataName, string* bindString){
    for(GuiObject* element : rmlImpl->objects){
        if(element->name == name){
            element->bindString(dataName, bindString);
            return;
        }
    }       
}

void Gui::bindButtonToElement(string name, bool* callback){
    for(GuiObject* element : rmlImpl->objects){
        if(element->name == name){
            element->bindButton(callback);
            return;
        }
    }       
}

void Gui::showElement(string name, bool show){
    for(GuiObject* element : rmlImpl->objects){
        if(element->name == name){
            element->showObject(show);
            return;
        }
    }    
}

void Gui::changeContextDimensions(int width, int height){
    rmlImpl->context->SetDimensions(Rml::Vector2i(width, height));
}

void Gui::processKeyDown(int key){
    Rml::Input::KeyIdentifier KeyIdentifier;
    if(key == 258){
        KeyIdentifier = Rml::Input::KI_TAB;
    } else if(key == 259){
        KeyIdentifier = Rml::Input::KI_BACK;
    }
    rmlImpl->context->ProcessKeyDown(KeyIdentifier, 0);
}

void Gui::processKeyUp(int key){
    Rml::Input::KeyIdentifier KeyIdentifier;
    if(key == 258){
        KeyIdentifier = Rml::Input::KI_TAB;
    } else if(key == 259){
        KeyIdentifier = Rml::Input::KI_BACK;
    }

    rmlImpl->context->ProcessKeyUp(KeyIdentifier, 0);
}

void Gui::processChar(unsigned int codepoint){
    rmlImpl->context->ProcessTextInput((Rml::Character)codepoint);
}

void Gui::processMouseMove(int x, int y){
    rmlImpl->context->ProcessMouseMove(x, y, 0);
}

void Gui::processMouseButtonUp(int buttonIndex){
    if(buttonIndex < 3){
        rmlImpl->context->ProcessMouseButtonUp(buttonIndex, 0);
    }
}

void Gui::processMouseButtonDown(int buttonIndex){
    if(buttonIndex < 3){
        rmlImpl->context->ProcessMouseButtonDown(buttonIndex, 0);
    }
}