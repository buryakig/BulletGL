#pragma once
#include "Core.h"

namespace BulletGL
{
	extern std::map<unsigned, unsigned> textureFormatsMap;

	class Texture
	{
	public:
		Texture() = default;
		Texture(int w, int h, unsigned format = GL_RGBA32F, int mipCount = 1, unsigned fMode = GL_LINEAR)
			: width(w), height(h), internalFormat(format), format(textureFormatsMap[format]), mipmapCount(mipCount), filterMode(fMode){}
		
		virtual ~Texture() {}


		unsigned int id = 0;

		int nrChannels = 0;

		int width = 0;
		int height = 0;

		int filterMode = 0;
		int mipmapCount = 1;
		unsigned int format = GL_RGBA;
		unsigned int internalFormat = GL_RGBA32F;

		unsigned int wrapMode = GL_REPEAT;

		std::string name = "";
	};

}