#pragma once

#include "Core.h"

namespace BulletGL
{
	class Shader
	{
	public:
		unsigned int programID;

		// constructor reads and builds the shader
		Shader(unsigned int id = 0) : programID(id) {}
		~Shader() {
			glDeleteProgram(programID);
		}
		// use/activate the shader
		void use() const;

		static void SetUp();

		static Shader* defaultShader;
		static Shader* emptyShader;


	private:

		friend class Resources;
	};
	

}