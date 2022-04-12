#pragma once
#include "Core.h"

class Texture
{
public:
	Texture(const char* imagePath);
		//Texture(int w, int h) : width(w), height(h) { glGenTextures(1, &id); }{
	~Texture();

	void Prepare(int textureType, int filterMode);

	unsigned int id;

	int width;
	int height;
	int nrChannels;
	int format;

	unsigned char* data;
};

