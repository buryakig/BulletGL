#pragma once
#include "Core.h"
#include "Texture.h"

namespace BulletGL
{
	class RenderTexture : public Texture
	{
	public:
		RenderTexture() = default;
		RenderTexture(int w, int h, int depth, unsigned format, unsigned graphicsFormat);
		~RenderTexture();

		void Bind() {}

		unsigned int FBO;
		unsigned int rboDepth;
	};

}