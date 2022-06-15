#pragma once
#include "Core.h"

namespace BulletGL
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(int w, int h) : width(w), height(h) {}
		virtual ~Texture() {}


		unsigned int id = 0;

		int width = 0;
		int height = 0;

		int filterMode = 0;
		int mipmapCount = 1;
		unsigned int format = GL_RGBA;
		unsigned int internalFormat = GL_RGBA32F;

		unsigned int wrapModeU = GL_REPEAT;
		unsigned int wrapModeV = GL_REPEAT;
		unsigned int wrapModeW = GL_REPEAT;

		std::string name = "";
	};

}