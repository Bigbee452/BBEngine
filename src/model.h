#pragma once
#include <glm/fwd.hpp>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.h"

using namespace std;

class Model 
{
    public:
        Model(std::string path)
        {
            loadModel(path);
        }
        void Draw(Shader &shader);	
        void setPosition(glm::vec3 position);
        void setPosition(float x, float y, float z);
    private:
        // model data
        vector<Mesh> meshes;
        vector<Texture> textures_loaded; 
        string directory;

        glm::vec3 position;

        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName);
};