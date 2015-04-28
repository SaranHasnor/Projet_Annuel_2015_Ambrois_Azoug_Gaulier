#include "Renderer.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>

#include <GL/glew.h>
#include <GL/glut.h>

static const float temp[] = {
	-1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f
};

GLuint vao, vbo;

Renderer::Renderer(void)
{
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * 3 * 3 * sizeof(float), temp, GL_STATIC_DRAW);

	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	
	glVertexAttribPointer(0, 6, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}


Renderer::~Renderer(void)
{
}


void Renderer::renderParticles(std::list<BaseParticle*>* particles)
{
	for (std::list<BaseParticle*>::const_iterator iterator = particles->begin(); iterator != particles->end(); ++iterator)
	{
		BaseParticle* particle = *iterator;
		glUseProgram(particle->shader->program);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}