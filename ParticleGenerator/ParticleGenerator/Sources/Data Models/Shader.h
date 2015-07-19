#pragma once

#include <string>

class Shader
{
public:
	Shader(void);
	Shader(std::string name, std::string path);
	~Shader(void);

	std::string			name;				// Name of the shader
	std::string			path;				// Path to the file containing the shader
	bool				compiled;			// True if the file has been parsed and compiled into a program. If false, it will be compiled on the next loop

	std::string			shaderText;			// Shader content
	unsigned int		program;			// OpenGL ID of the shader's program

	int					textureLocation;	// GLSL Uniform location
	int					coordsLocation;		// GLSL Attrib location
	int					texCoordsLocation;	// GLSL Attrib location
	
	int					positionLocation;	// GLSL Uniform location
	int					angleLocation;		// GLSL Uniform location

	int					viewMatLocation;	// GLSL Uniform location

	int					customRGBALocation;	// GLSL Uniform location
	int					scaleLocation;		// GLSL Uniform location

	void				loadFile();

private:
	void				_createProgram();
	std::string			_defaultVertShader();
};

