#ifndef SHADER_H
#define SHADER_H

#include "Core.h"

class Shader
{
public:
	unsigned int programID;

	// constructor reads and builds the shader
	Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	~Shader() {
		remove(shaderList.begin(), shaderList.end(), this);
		glDeleteProgram(programID); 
	
	}
	// use/activate the shader
	void use() const;

private:
	static std::vector<Shader*> shaderList;
	static int blockBindings;

	static unsigned int uboMatrices;
};

#endif

