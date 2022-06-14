#pragma once
#include "Core.h"

namespace BulletGL
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(int w, int h) : width(w), height(h) {}
		virtual ~Texture();


		unsigned int id = 0;

		int width = 0;
		int height = 0;

		int filterMode = 0;
		int nrChannels = 3;
		int mipmapCount = 1;
		unsigned int format = 0;
		unsigned int internalFormat = 0;

		unsigned int wrapModeU = 0;
		unsigned int wrapModeV = 0;
		unsigned int wrapModeW = 0;

		std::string name;

		unsigned char* data = nullptr;
	};

}