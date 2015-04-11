#include "Engine.h"

#include "Rendering/Renderer.h"
#include "Parsing/Parser.h"
#include "../Data Models/BaseParticle.h"


Engine::Engine(void)
{
	_renderer = new Renderer();
	_parser = new Parser();

	_particles = _parser->parseFile(std::string());
}


Engine::~Engine(void)
{
}


void Engine::run()
{
	_renderer->renderParticles(_particles);
}