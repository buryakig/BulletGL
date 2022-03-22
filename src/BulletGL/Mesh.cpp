#include "Mesh.h"

float vertices_quad[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f,   // top left 
     0.5f,  0.5f, 0.0f,  // top right
};

unsigned int indices_quad[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

Mesh::Mesh() : VBO(0), VAO(0), EBO(0) 
{

}

Mesh::~Mesh()
{
    Release();
}

void Mesh::Prepare()
{

    if (vertices.empty())
    {
        std::cout << "NO VERTICES DETECTED WHILE PREPARING MESH" << std::endl;
        return;
    }

    const int verticies_size_bytes = vertices.size() * sizeof(vertices[0]);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies_size_bytes, vertices.data(), GL_STATIC_DRAW);

    if (!indices.empty())
    {
        const int indices_size_bytes = indices.size() * sizeof(indices[0]);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size_bytes, indices.data(), GL_STATIC_DRAW);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}



void Mesh::Draw()
{
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    if (indices.empty())
    {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    else
    {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void Mesh::SetVertices()
{
    
}

void Mesh::SetIndices()
{

}

void Mesh::Release()
{
    glDeleteBuffers(1, &VBO);
    VBO = 0;

    glDeleteBuffers(1, &EBO);
    EBO = 0;

    glDeleteVertexArrays(1, &VAO);
    VAO = 0;
}