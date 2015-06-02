#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(std::string path)
{
	this->path = path;

	this->data = stbi_loadf(path.c_str(), &this->width, &this->height, NULL, 4);

	this->textureID = 0;
}


Texture::~Texture(void)
{
}
