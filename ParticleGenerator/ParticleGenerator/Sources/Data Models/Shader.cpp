#include "Shader.h"

#include <GL/glew.h>

#include <fstream>
#include <algorithm>

Shader::Shader(void)
{ // Default shader
	this->name = std::string("Default");
	this->path = std::string("Shaders/default_fs.glsl");

	this->program = 0;
	this->compiled = false;
}

Shader::Shader(std::string name, std::string path)
{
	this->name = name;
	this->path = path;

	this->program = 0;
	this->compiled = false;
}

Shader::~Shader(void)
{
}


void Shader::loadFile()
{
	std::ifstream ifs(this->path);
	if (ifs)
	{
		this->shaderText = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	}
	else
	{
		this->shaderText = std::string();
	}
	_createProgram();
}

std::string Shader::_defaultVertShader()
{
	std::ifstream ifs("Shaders/default_vs.glsl");
	if (ifs)
		return std::string((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
	else
		return std::string("");
}

void printShaderLog(GLuint obj)
{
	int infologLength = 0;
	int maxLength;
  
	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
  
	char *infoLog = new char[maxLength];
  
	if (glIsShader(obj))
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
  
	if (infologLength > 0)
		printf("%s\n",infoLog);
  
	delete infoLog;
}


void Shader::_createProgram()
{
	std::string shaderText = _defaultVertShader();
	const char *vShaderText = shaderText.c_str();
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderText, NULL);
	glCompileShader(vShader);
	printShaderLog(vShader);

	const char *fShaderText = this->shaderText.c_str();
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	glCompileShader(fShader);
	printShaderLog(fShader);

	GLuint prog = glCreateProgram();
	glAttachShader(prog, vShader);
	glAttachShader(prog, fShader);
	glLinkProgram(prog);
	printShaderLog(prog);

	if (this->program != 0)
	{
		glDeleteProgram(this->program);
	}

	this->program = prog;

	printf("Successfully created program %i\n", prog);

	this->textureLocation = glGetUniformLocation(this->program, "tex");
	this->coordsLocation = glGetAttribLocation(this->program, "pos");
	this->texCoordsLocation = glGetAttribLocation(this->program, "texpos");

	this->positionLocation = glGetUniformLocation(this->program, "particlePos");
	this->angleLocation = glGetUniformLocation(this->program, "particleAngle");

	this->viewMatLocation = glGetUniformLocation(this->program, "viewMatrix");

	this->customRGBALocation = glGetUniformLocation(this->program, "customColor");
	this->scaleLocation = glGetUniformLocation(this->program, "scale");

	this->compiled = true;
}