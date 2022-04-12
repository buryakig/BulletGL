#pragma once
#include "Core.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Prepare();
	void CreateBuffers();
	void Draw();

	void SetVertices();
	void SetIndices();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normal;
	std::vector<glm::vec2> uv;
	//std::vector<Vector2> uv;
	std::vector<unsigned int> indices;

private:
	void Release();

	unsigned int VBO, EBO, VAO;

};

