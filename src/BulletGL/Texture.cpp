#include "Texture.h"

void Texture::Prepare(int textureType, int filterMode)
{
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, textureType,
		width, height, 0, textureType, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, filterMode);
}
