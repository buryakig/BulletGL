#pragma once
#include "Core.h"

class Texture
{
public:
	Texture() : width(0), height(0) { glGenTextures(1, &id); }
	Texture(int w, int h) : width(w), height(h) { glGenTextures(1, &id); }
	~Texture();

	void Prepare(int textureType, int filterMode);

	unsigned int id;

	int width;
	int height;
};

