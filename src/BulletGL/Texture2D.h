#pragma once
#include "Core.h"
#include "Texture.h"

namespace BulletGL
{
	class Texture2D : public Texture
	{
	public:
		Texture2D() = default;
		Texture2D(int w, int h, unsigned iformat, int mipCount = 1, unsigned fMode = GL_LINEAR);
		virtual ~Texture2D();

		void SetPixels(unsigned char* pixels);
		void SetPixels(unsigned int* pixels);
		void SetPixels(float* pixels);

		void Apply();

		unsigned int dataType;

		void* data = nullptr;
	};

}