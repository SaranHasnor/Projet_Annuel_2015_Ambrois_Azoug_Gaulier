#include "Renderer.h"

#include "../../Data Models/BaseParticle.h"
#include "../../Data Models/Shader.h"

#include <GL/glew.h>
#include <GL/glut.h>

Renderer::Renderer(void)
{
}


Renderer::~Renderer(void)
{
}


void Renderer::renderParticles(std::list<BaseParticle*>* particles)
{
	for (auto & particle : *particles)
	{
		glUseProgram(particle->shader->program);
		// TODO: Draw particle

	}
}