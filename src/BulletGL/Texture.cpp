#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* imagePath)
{ 
	data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

Texture::~Texture()
{
	stbi_image_free(data);
}

void Texture::Prepare(int textureType, int filterMode)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, filterMode);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, filterMode);

	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	glTextureStorage2D(id, 1, format, width, height); 
	glTextureSubImage2D(id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
}
