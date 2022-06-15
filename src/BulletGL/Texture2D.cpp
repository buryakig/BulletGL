#include "Texture2D.h"

#include "stb_image.h"


namespace BulletGL
{
	Texture2D::Texture2D(int w, int h, unsigned iformat, int mipCount, unsigned fMode)
		: Texture(w, h, iformat, mipCount, fMode)
	{
		glDeleteTextures(1, &id);

		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, iformat, width, height);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, fMode);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, fMode);
	}

	void Texture2D::SetPixels(unsigned char* pixels)
	{
		data = pixels;
		dataType = GL_UNSIGNED_BYTE;
	}

	void Texture2D::SetPixels(unsigned int* pixels)
	{
		data = pixels;
		dataType = GL_UNSIGNED_INT;
	}

	void Texture2D::SetPixels(float* pixels)
	{
		data = pixels;
		dataType = GL_FLOAT;
	}

	void Texture2D::Apply()
	{
		glTextureSubImage2D(id, 0, 0, 0, width, height, format, dataType, data);
	}

	Texture2D::~Texture2D()
	{
		if (data)
			free(data);
	}
}