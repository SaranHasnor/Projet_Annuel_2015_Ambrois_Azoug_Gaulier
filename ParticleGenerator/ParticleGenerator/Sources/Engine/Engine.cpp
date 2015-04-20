#include "Engine.h"

#include "Rendering/Renderer.h"
#include "Parsing/Parser.h"

#include "../Data Models/BaseParticle.h"
#include "../Data Models/Shader.h"

#include <GL/glew.h>

#include <fstream>

Engine::Engine(void)
{
	_renderer = new Renderer();
	_parser = new Parser();
	
	_shaders = new std::list<Shader*>();

	Shader *defaultShader = new Shader();

	defaultShader->name = std::string("Default");
	defaultShader->shaderText = _defaultFragShader();

	// First item of the list should always be this one
	_shaders->push_back(defaultShader);

	_createProgramForShader(defaultShader);

	_particles = _parser->parseFile(std::string());

	_particles->front()->shader = defaultShader;
}


Engine::~Engine(void)
{
}


void Engine::run()
{
	_renderer->renderParticles(_particles);
}


BaseParticle* Engine::particleNamed(std::string name)
{
	// TODO: Return the first particle of _particles with a matching name
	return NULL;
}


std::string Engine::_defaultFragShader()
{
	// TODO: Parse Shaders/default_fs.glsl
	std::ifstream ifs("../ParticleGenerator/Shaders/default_fs.glsl");
	if (ifs)
		return std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	else
		return std::string("");
}


std::string Engine::_defaultVertShader()
{
	// TODO: Parse Shaders/default_vs.glsl
	std::ifstream ifs("../ParticleGenerator/Shaders/default_vs.glsl");
	if (ifs)
		return std::string((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
	else
		return std::string("");
}

void printLog(GLuint obj)
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

void Engine::_createProgramForShader(Shader *shader)
{
	std::string shaderText = _defaultVertShader();
	const char *vShaderText = shaderText.c_str();
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderText, NULL);
	glCompileShader(vShader);
	printLog(vShader);

	const char *fShaderText = shader->shaderText.c_str();
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	glCompileShader(fShader);
	printLog(fShader);

	GLuint prog = glCreateProgram();
	glAttachShader(prog, fShader);
	glAttachShader(prog, vShader);
	glLinkProgram(prog);
	printLog(prog);

	shader->program = prog;
}
