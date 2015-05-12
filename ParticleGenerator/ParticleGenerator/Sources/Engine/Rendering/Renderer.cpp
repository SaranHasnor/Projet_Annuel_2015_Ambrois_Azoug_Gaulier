#include "Renderer.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <Utils/util_types.h>

static const float temp[] = {
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	//-0.5f, 0.5f, 0.0f,
	//0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f
};

static const ubyte temp2[] = {
	0, 1, 2,
	0, 2, 3
};

GLuint vbo, ebo;

Renderer::Renderer(void)
{
	printf("Version Pilote OpenGL : %s\n", glGetString(GL_VERSION));
	printf("Type de GPU : %s\n", glGetString(GL_RENDERER));
	printf("Fabricant : %s\n", glGetString(GL_VENDOR));
	printf("Version GLSL : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(float), temp, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(ubyte), temp2, GL_STATIC_DRAW);
}


Renderer::~Renderer(void)
{
}


void Renderer::renderParticles(std::list<BaseParticle*>* particles)
{
	for (std::list<BaseParticle*>::const_iterator iterator = particles->begin(); iterator != particles->end(); ++iterator)
	{
		BaseParticle* particle = *iterator;

		if (particle->linked)
		{
			glUseProgram(particle->shader->program);

			glActiveTexture(GL_TEXTURE0 + particle->texture->textureID);
			glBindTexture(GL_TEXTURE_2D, particle->texture->textureID);
			glUniform1i(particle->shader->textureLocation, particle->texture->textureID);
			
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

			glVertexAttribPointer(particle->shader->coordsLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
			glEnableVertexAttribArray(particle->shader->coordsLocation);
			glVertexAttribPointer(particle->shader->texCoordsLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(particle->shader->texCoordsLocation);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	glUseProgram(0);
}