#include "Texture.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace BulletGL
{
	Texture::~Texture()
	{
		stbi_image_free(data);
	}
}