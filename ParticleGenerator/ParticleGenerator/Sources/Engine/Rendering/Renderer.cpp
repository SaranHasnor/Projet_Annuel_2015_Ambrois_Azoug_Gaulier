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
	for (std::list<BaseParticle*>::const_iterator iterator = particles->begin(); iterator != particles->end(); ++iterator)
	{
		glUseProgram((*iterator)->shader->program);
		// TODO: Draw particle

	}
}