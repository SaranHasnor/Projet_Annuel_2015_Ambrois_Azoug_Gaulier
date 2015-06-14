#include "Renderer.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleState.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <Utils/util_types.h>

static const float defaultParticleCoords[] = {
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f
};

static const ubyte defaultParticleElements[] = {
	0, 1, 2,
	0, 2, 3
};

static GLuint defaultParticleVBO, defaultParticleEBO;

Renderer::Renderer(void)
{
	printf("Version Pilote OpenGL : %s\n", glGetString(GL_VERSION));
	printf("Type de GPU : %s\n", glGetString(GL_RENDERER));
	printf("Fabricant : %s\n", glGetString(GL_VENDOR));
	printf("Version GLSL : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glGenBuffers(1, &defaultParticleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, defaultParticleVBO);
	glBufferData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(float), defaultParticleCoords, GL_STATIC_DRAW);

	glGenBuffers(1, &defaultParticleEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, defaultParticleEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(ubyte), defaultParticleElements, GL_STATIC_DRAW);
}


Renderer::~Renderer(void)
{
}


void Renderer::renderParticles(std::list<BaseParticle*>* particles, float viewMatrix[16], unsigned long currentTime)
{
	for (std::list<BaseParticle*>::const_iterator iterator = particles->begin(); iterator != particles->end(); ++iterator)
	{
		BaseParticle* particle = *iterator;

		if (particle->linked)
		{
			ParticleState *particleState;
			bool tempState = false;
			
			if (particle->defaultState)
			{
				if (particle->transState)
				{
					particleState = particle->defaultState->Lerp(*particle->transState, (float)(currentTime - particle->spawnTime) / (float)particle->lifeTime);
					tempState = true;
				}
				else
				{
					particleState = particle->defaultState;
				}
			}
			else
			{ // Shouldn't happen pleaaaase
				particleState = new ParticleState();
				tempState = true;
			}

			glUseProgram(particle->shader->program);

			glActiveTexture(GL_TEXTURE0 + particle->texture->textureID);
			glBindTexture(GL_TEXTURE_2D, particle->texture->textureID);
			glUniform1i(particle->shader->textureLocation, particle->texture->textureID);
			
			glBindBuffer(GL_ARRAY_BUFFER, defaultParticleVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, defaultParticleEBO);

			glVertexAttribPointer(particle->shader->coordsLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
			glEnableVertexAttribArray(particle->shader->coordsLocation);
			glVertexAttribPointer(particle->shader->texCoordsLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(particle->shader->texCoordsLocation);

			glUniformMatrix4fv(particle->shader->worldMatLocation, 1, GL_TRUE, particle->modelMatrix);
			glUniformMatrix4fv(particle->shader->viewMatLocation, 1, GL_TRUE, viewMatrix);

			glUniform4f(particle->shader->customRGBALocation, particleState->red, particleState->green, particleState->blue, particleState->alpha);
			// TODO: Scale

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

			if (tempState)
			{
				delete particleState;
			}
		}
	}
	glUseProgram(0);
}