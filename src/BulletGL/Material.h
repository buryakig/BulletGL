#pragma once
#include <map>
#include <iostream>
	
#include "Shader.h"
#include "Texture.h"

namespace BulletGL
{
	class Material
	{
	public:
		Material() { std::cout << this << std::endl; addToList(); };
		Material(Shader* s) : shader(s) { addToList(); }
		Material(Material* m) : shader(m->shader) { addToList(); }
		~Material() {}

		void SetInt(std::string name, int value);
		void SetFloat(std::string name, float value);
		void SetMatrix(std::string name, glm::mat4 value);
		void SetColor(std::string name, glm::vec4 value);
		void SetVector(std::string name, glm::vec4 value);
		void SetTexture(std::string name, Texture* value);

		static void SetUp();
		static void CreateDefaultMaterials();

		static void DeallocateMemory();



		unsigned int GetUniformLocation(const std::string& uniformName);

		void Use();

		Shader* shader;

		std::map<std::string, int> intList;
		std::map<std::string, float> floatList;
		std::map<std::string, Texture*> textureList;
		std::map<std::string, glm::mat4> matrixList;
		std::map<std::string, glm::vec4> vectorList;

		static Material* emptyMaterial;
		static Material* defaultMaterial;

	private:
		static std::vector<Material*> materials;
		void addToList() { materials.push_back(this); };
	};
}