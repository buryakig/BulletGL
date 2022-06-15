#pragma once
#include "Core.h"
#include "Texture.h"

namespace BulletGL
{
	class Texture2D : public Texture
	{
	public:
		Texture2D() = default;
		Texture2D(int w, int h) : Texture(w, h) {}
		virtual ~Texture2D();

		int nrChannels = 0;
		unsigned char* data = nullptr;
	};

}