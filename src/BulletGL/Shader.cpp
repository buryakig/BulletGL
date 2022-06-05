#include "Shader.h"
#include "Utils/Resources/Resources.h"

namespace BulletGL
{
	Shader* Shader::defaultShader = nullptr;
	Shader* Shader::emptyShader = nullptr;

	void Shader::use() const
	{
		glUseProgram(programID);
	}

	void Shader::SetUp()
	{
		defaultShader = Resources::LoadShader("res/Shaders/colorShader.vert", "res/Shaders/colorShader.frag");
		emptyShader = Resources::LoadShader("res/Shaders/texShader.vert", "res/Shaders/texShader.frag");
	}
}