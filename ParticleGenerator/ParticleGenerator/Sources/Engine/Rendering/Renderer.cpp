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
	for (int i = 0; i < particles->size(); i++)
	{
		BaseParticle *particle;// = particles[i];
		glUseProgram(particle->shader->program);

		// TODO: Draw particle
	}
}