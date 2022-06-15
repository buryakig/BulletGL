#include "Texture2D.h"

#include "stb_image.h"


namespace BulletGL
{
	Texture2D::~Texture2D()
	{
		if (data)
			stbi_image_free(data);
	}
}