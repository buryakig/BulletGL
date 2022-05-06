#pragma once

#include "Model.h"
using namespace std;

class ModelLoader
{
public:

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    static Model* loadModel(string const& path)
    {   

        std::cout << "Processing model file " << std::endl;
        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return nullptr;
        }

        Model* model = new Model();
        std::cout << "Done model file " << std::endl;
        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene, model);
        
        return model;
    }

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    static void processNode(aiNode* node, const aiScene* scene, Model* model)
    {
        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            model->meshes.push_back(processMesh(mesh, scene));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, model);
        }

    }

    static Mesh* processMesh(aiMesh* aMesh, const aiScene* scene)
    {
        std::cout << "Loading Mesh" << std::endl;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;
        std::vector<unsigned int> indices;

        bool hasPositions = aMesh->HasPositions();
        bool hasNormals = aMesh->HasNormals();
        bool hasTextureCoords0 = aMesh->HasTextureCoords(0);
        bool hasTangentsAndBitangents = aMesh->HasTangentsAndBitangents();
        bool hasIndices = aMesh->HasFaces();
        
        if (hasPositions) vertices.reserve(aMesh->mNumVertices);
        if (hasNormals) normals.reserve(aMesh->mNumVertices);
        if (hasTextureCoords0) uv.reserve(aMesh->mNumVertices);
        if (hasTangentsAndBitangents)
        {
            tangents.reserve(aMesh->mNumVertices);
            bitangents.reserve(aMesh->mNumVertices);
        }

        if(hasIndices) indices.reserve(static_cast<int>(aMesh->mNumFaces) * 3);

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < aMesh->mNumVertices; ++i)
        {
            // positions
            if (hasPositions)
            {
                vertices.push_back(glm::vec3(aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z));
            }
            // normals
            if (hasNormals)
            {
                normals.push_back(glm::vec3(aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z));
            }
            // texture coordinates
            if (hasTextureCoords0) // does the mesh contain texture coordinates?
            {
                uv.push_back(glm::vec2(aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y));
            }
            if (hasTangentsAndBitangents)
            {
                tangents.push_back(glm::vec3(aMesh->mTangents[i].x, aMesh->mTangents[i].y, aMesh->mTangents[i].z));
                bitangents.push_back(glm::vec3(aMesh->mBitangents[i].x, aMesh->mBitangents[i].y, aMesh->mBitangents[i].z));
            }
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < aMesh->mNumFaces; ++i)
        {
            aiFace face = aMesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; ++j)
                indices.push_back(aMesh->mFaces[i].mIndices[j]);
        }
        // process materials

        Mesh* modelmesh = new Mesh();
        modelmesh->vertices = vertices;
        modelmesh->normals = normals;
        modelmesh->tangents = tangents;
        modelmesh->bitangents = bitangents;
        modelmesh->uv = uv;
        modelmesh->indices = indices;

        std::cout << "Done Loading Mesh" << std::endl;
        modelmesh->Prepare();
        // return a mesh object created from the extracted mesh data
        return modelmesh;
    }
};
