#pragma once

#include <string>

class Shader
{
public:
	Shader(void);
	~Shader(void);

	std::string			name;			// Name of the shader

	std::string			shaderText;		// Shader content
	unsigned int		program;		// OpenGL ID of the program

	int					textureLocation;	// GLSL Uniform location
	int					coordsLocation;		// GLSL Attrib location
	int					texCoordsLocation;	// GLSL Attrib location
	
	int					viewMatLocation;	// GLSL Uniform location
	int					worldMatLocation;	// GLSL Uniform location
};

