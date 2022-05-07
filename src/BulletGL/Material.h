#pragma once
#include <map>
	
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material() = default;
	Material(Shader* s) : shader(s) {}
	~Material() {}

	void SetInt		(std::string name, int value);
	void SetFloat	(std::string name, float value);
	void SetMatrix	(std::string name, glm::mat4 value);
	void SetColor	(std::string name, glm::vec4 value);
	void SetVector	(std::string name, glm::vec4 value);
	void SetTexture	(std::string name, Texture* value);

	unsigned int GetUniformLocation(const std::string& uniformName);

	void Use();

	Shader *shader;

	std::map<std::string, int> intList;
	std::map<std::string, float> floatList;
	std::map<std::string, Texture*> textureList;
	std::map<std::string, glm::mat4> matrixList;
	std::map<std::string, glm::vec4> vectorList;
};