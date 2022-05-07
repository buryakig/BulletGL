#include "Material.h"

void Material::SetInt(std::string name, int value)
{
	intList[name] = value;
}

void Material::SetFloat(std::string name, float value)
{
	floatList[name] = value;
}


void Material::SetMatrix(std::string name, glm::mat4 value)
{
	matrixList[name] = value;
}

void Material::SetColor(std::string name, glm::vec4 value)
{
	SetVector(name, value);
}

void Material::SetVector(std::string name, glm::vec4 value)
{
	vectorList[name] = value;
}

void Material::SetTexture(std::string name, Texture* value)
{
	textureList[name] = value;
}

unsigned int Material::GetUniformLocation(const std::string &uniformName)
{
	return glGetUniformLocation(shader->programID, uniformName.c_str());
}

void Material::Use()
{
	shader->use();

	// Set all ints
	for (auto const& x : intList)
		glUniform1i(GetUniformLocation(x.first), x.second);
	
	// Set all floats
	for (auto const& x : floatList)
		glUniform1f(GetUniformLocation(x.first), x.second);

	// Set all matricies
	for (auto const& x : matrixList)
		glUniformMatrix4fv(GetUniformLocation(x.first), 1, GL_FALSE, glm::value_ptr(x.second));

	// Set all vectors
	for (auto const& x : vectorList)
		glUniform4fv(GetUniformLocation(x.first), 1, glm::value_ptr(x.second));

	// Set all textures
	int texIdx = 0;
	for (auto const& x : textureList)
	{
		glUniform1i(GetUniformLocation(x.first), texIdx);
		
		//glActiveTexture(GL_TEXTURE0 + texIdx);
		//glBindTexture(GL_TEXTURE_2D, x.second->id);
		
		glBindTextureUnit(texIdx, x.second->id);
		++texIdx;
	}
}
