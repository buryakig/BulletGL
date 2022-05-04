#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Model
{
public:
    // model data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh*>    meshes;
    string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    Model()
    {
    }

    ~Model()
    {
        for (int i = 0; i < meshes.size(); i++)
            delete meshes[i];
    }

    // draws the model, and thus all its meshes
    void Draw(Material& mat)
    {
        mat.Use();
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i]->Draw();
    }

    friend class ModelLoader;
};
