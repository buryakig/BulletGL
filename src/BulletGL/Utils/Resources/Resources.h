#pragma once
#include<string>
#include <fstream>
#include "Shader.h"
#include "Model.h"

class Resources
{
public:
	Resources() = delete;

	static Shader* LoadShader(const char* vertexPath, const char* fragmentPath);
	static Model* LoadModel(const char* path);
	
	static void DeallocateMemory();

	static std::vector<Shader*> shaders;
	static std::vector<Model*> models;
};

