#pragma once

#include <string>

class Texture
{
public:
	Texture(std::string path);
	~Texture(void);

	std::string			path;			// Path to the file containing this texture


	void*				data;			// Pointer to the decoded data of the texture
	unsigned int		width, height;	// Size of the image


	unsigned int		textureID;		// OpenGL ID of the texture
};

