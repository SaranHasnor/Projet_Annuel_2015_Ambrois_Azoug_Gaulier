#pragma once

#include <string>

class Shader
{
public:
	Shader(void);
	~Shader(void);

	std::string			name;			// Name of the shader


	std::string			shaderText;
	unsigned int		program;
};

