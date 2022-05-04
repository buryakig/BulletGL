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
    const int uv_size_bytes = uv.size() * sizeof(uv[0]);
    const int normals_size_bytes = normal.size() * sizeof(normal[0]);

    const int total_size = verticies_size_bytes + uv_size_bytes + normals_size_bytes;

    glCreateVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);
    glNamedBufferStorage(VBO, total_size, nullptr, GL_DYNAMIC_STORAGE_BIT);

    int offset = 0;
    glNamedBufferSubData(VBO, 0, verticies_size_bytes, vertices.data());
    offset += verticies_size_bytes;
    glNamedBufferSubData(VBO, offset, uv_size_bytes, uv.data());
    offset += uv_size_bytes;
    glNamedBufferSubData(VBO, offset, normals_size_bytes, normal.data());

    if (!indices.empty())
    {
        const int indices_size_bytes = indices.size() * sizeof(indices[0]);
        glCreateBuffers(1, &EBO);

        glNamedBufferStorage(EBO, indices_size_bytes, nullptr, GL_DYNAMIC_STORAGE_BIT);
        glNamedBufferSubData(EBO, 0, indices_size_bytes, indices.data());

        glVertexArrayElementBuffer(VAO, EBO);
    }

    offset = 0;
    glVertexArrayVertexBuffer(VAO, 0, VBO, offset, sizeof(vertices[0]));
    offset += verticies_size_bytes;
    glVertexArrayVertexBuffer(VAO, 1, VBO, offset, sizeof(uv[0]));
    offset += uv_size_bytes;
    glVertexArrayVertexBuffer(VAO, 2, VBO, offset, sizeof(normal[0]));

    glEnableVertexArrayAttrib(VAO, 0);
    glEnableVertexArrayAttrib(VAO, 1);
    glEnableVertexArrayAttrib(VAO, 2);
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(VAO, 3, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribBinding(VAO, 1, 1);
    glVertexArrayAttribBinding(VAO, 2, 2);
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