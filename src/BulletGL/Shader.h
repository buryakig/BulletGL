#pragma once

#include "Core.h"

namespace BulletGL
{
	class Shader
	{
	public:
		unsigned int programID;

		// constructor reads and builds the shader
		Shader() {};
		Shader(const char* vertexPath, const char* fragmentPath);
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
		~Shader() {
			glDeleteProgram(programID);
		}
		// use/activate the shader
		void use() const;

		static void SetUp();

		static Shader* defaultShader;
		static Shader* emptyShader;

	private:
		Shader(unsigned int id) : programID(id) {}

		friend class Resources;
	};
	

}