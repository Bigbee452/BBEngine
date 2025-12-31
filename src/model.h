#pragma once
#include <glm/fwd.hpp>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>

#include "shader.h"
#include "mesh.h"

using namespace std;

class Model 
{
    public:
        Model(string path, string name);
        Model(string path, string name, Material* mat);
        ~Model();
        void Draw(Shader &shader);	
        void setPosition(glm::vec3 position);
        void setPosition(float x, float y, float z);
        void setRotation(glm::vec3 rotation);
        void setRotation(float x, float y, float z);

        void setPreTransform(glm::mat4 transform);
        glm::vec3 getPosition();

        string name;
    private:
        // model data
        vector<Mesh> meshes;
        vector<Texture> textures_loaded; 
        string directory;

        glm::vec3 position;
        glm::vec3 rotation;

        struct AssimpImpl;
        std::unique_ptr<AssimpImpl> assimpImpl;

        void loadModel(string path); 

        glm::mat4 pre_transform = glm::mat4(1.0f);

        Material* override_mat = nullptr;
};