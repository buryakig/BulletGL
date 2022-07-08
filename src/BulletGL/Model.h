#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Material.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

namespace BulletGL
{
    class Model
    {
    public:
        // model data 
        map<Mesh*, Material*>    meshes;
        string directory;

        // constructor, expects a filepath to a 3D model.
        Model()
        {
        }

        ~Model()
        {
            for (auto meshmatpair : meshes)
            {
                delete meshmatpair.first;
                //delete meshmatpair.second;
            }
        }

        // draws the model, and thus all its meshes
        void Draw(Material* mat, const glm::mat4& modelMatrix)
        {
            mat->SetMatrix("model", modelMatrix);
            mat->Use();
            for (auto meshmatpair : meshes)
                meshmatpair.first->Draw();
        }

        void Draw(const glm::mat4& modelMatrix)
        {
            for (auto meshmatpair : meshes)
            {
                if (meshmatpair.second)
                {
                    meshmatpair.second->SetMatrix("model", modelMatrix);
                    meshmatpair.second->Use();
                }
                meshmatpair.first->Draw();
            }
        }

        friend class ModelLoader;
    };
}