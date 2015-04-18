#include "Engine.h"

#include "Rendering/Renderer.h"
#include "Parsing/Parser.h"

#include "../Data Models/BaseParticle.h"
#include "../Data Models/Shader.h"


Engine::Engine(void)
{
	_renderer = new Renderer();
	_parser = new Parser();

	_particles = _parser->parseFile(std::string());
	
	_shaders = new std::list<Shader*>();

	Shader *defaultShader = new Shader();

	defaultShader->name = std::string("Default");
	defaultShader->shaderText = _defaultFragShader();

	// First item of the list should always be this one
	_shaders->push_back(defaultShader);
}


Engine::~Engine(void)
{
}


void Engine::run()
{
	_renderer->renderParticles(_particles);
}


std::string Engine::_defaultFragShader()
{
	// TODO: Parse Shaders/default_fs.glsl
	return std::string("");
}


std::string Engine::_defaultVertShader()
{
	// TODO: Parse Shaders/default_vs.glsl
	return std::string("");
}