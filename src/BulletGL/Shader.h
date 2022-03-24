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
	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVector(const std::string& name, float valuex, float valuey, float valuez, float valuew) const;
	void setVector(const std::string& name, float valuex, float valuey, float valuez) const;
	void setMatrix(const std::string& name, glm::mat4 matrix) const;
	
	static void initUniformBuffer();
	static void setGlobalCameraParams(const std::string& name, glm::mat4 projection, glm::mat4 view);

private:
	static std::vector<Shader*> shaderList;
	static int blockBindings;

	static unsigned int uboMatrices;
};

#endif

