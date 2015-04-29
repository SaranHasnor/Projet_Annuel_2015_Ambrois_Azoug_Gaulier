#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(std::string path)
{
	this->path = path;

	this->data = stbi_loadf(path.c_str(), &this->width, &this->height, NULL, 4);
	for (int i = 0; i < this->width * this->height * 4; i += 4)
	{
		((float*)this->data)[i+0] = fmodf(i, this->width * 4);
		((float*)this->data)[i+1] = fmodf(i, this->width * 4);
		((float*)this->data)[i+2] = fmodf(i, this->width * 4);
		((float*)this->data)[i+3] = 1.0f;
	}

	this->textureID = 0; // TEMP
}


Texture::~Texture(void)
{
}
