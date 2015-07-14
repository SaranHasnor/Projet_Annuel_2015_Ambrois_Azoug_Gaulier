#include "Engine.h"

#include "Rendering/Renderer.h"
#include "Parsing/Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/ParticleState.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleEmitter.h>

#include <GL/glew.h>
#include <GL/glut.h>

extern "C" {
#include <Utils/render_utils.h>
}

#include <fstream>
#include <algorithm>

Engine::Engine(void)
{
	_renderer = new Renderer();
	_parser = new Parser();
	
	_shaders = new std::list<Shader*>();

	_particleCount = 0;

	_currentTime = 0;

	Shader *defaultShader = new Shader();
	//defaultShader->loadFile();

	// First item of the list should always be this one
	_shaders->push_back(defaultShader);

	_emitters = new std::list<ParticleEmitter*>();
	
	_particleModels = new std::list<BaseParticle*>(); //_parser->parseParticlesInFile(std::string());
	//std::for_each(_particleModels->begin(), _particleModels->end(), [this](BaseParticle *particle){ this->_processParticle(particle); });

	_activeParticles = new std::list<BaseParticle*>();

	// Demo
	createParticle();
	createEmitter();
}


Engine::~Engine(void)
{
}


void Engine::update(float deltaTime)
{
	_currentTime += (unsigned long)(deltaTime * 1000);
	std::list<BaseParticle*> deleteList = std::list<BaseParticle*>();

	// Compile new shaders
	for (std::list<Shader*>::const_iterator iterator = _shaders->begin(); iterator != _shaders->end(); ++iterator)
	{
		Shader *shader = *iterator;
		
		if (!shader->compiled)
		{
			shader->loadFile();
		}
	}

	// Process new models
	for (std::list<BaseParticle*>::const_iterator iterator = _particleModels->begin(); iterator != _particleModels->end(); ++iterator)
	{
		BaseParticle *particle = *iterator;
		
		if (!particle->processed)
		{
			_processParticle(particle);
		}
	}

	// Update particles
	for (std::list<BaseParticle*>::const_iterator iterator = _activeParticles->begin(); iterator != _activeParticles->end(); ++iterator)
	{
		BaseParticle *particle = *iterator;

		if (_currentTime < particle->spawnTime + particle->lifeTime)
		{
			vectorMA(particle->geometry.position, particle->geometry.position, deltaTime, particle->geometry.velocity);
		}
		else
		{
			deleteList.push_back(particle);
		}
	}

	// Delete particles
	for (std::list<BaseParticle*>::const_iterator iterator = deleteList.begin(); iterator != deleteList.end(); ++iterator)
	{
		BaseParticle *particle = *iterator;
		_activeParticles->remove(particle);
		delete particle;
		_particleCount--;
	}

	// Update emitters
	for (std::list<ParticleEmitter*>::const_iterator iterator = _emitters->begin(); iterator != _emitters->end(); ++iterator)
	{
		ParticleEmitter *emitter = *iterator;

		if (_currentTime - emitter->lastSpawn >= emitter->spawnInterval)
		{ // Time to create a new particle
			BaseParticle *newParticle = emitter->spawnParticle(*emitter->particleModel);
			newParticle->spawnTime = _currentTime;
			_activeParticles->push_back(newParticle);
			emitter->lastSpawn = _currentTime;
			_particleCount++;
		}
	}
}


void Engine::render(float viewMatrix[16])
{
	_renderer->renderParticles(_activeParticles, viewMatrix, _currentTime);

	// Debug: draw emitters
	for (std::list<ParticleEmitter*>::const_iterator iterator = _emitters->begin(); iterator != _emitters->end(); ++iterator)
	{
		ParticleEmitter *emitter = *iterator;
		glPushMatrix();
		glTranslatef(emitter->geometry.position[0], emitter->geometry.position[1], emitter->geometry.position[2]);
		glRotatef(emitter->geometry.angle[0], 1.0f, 0.0f, 0.0f);
		glRotatef(emitter->geometry.angle[1], 0.0f, 1.0f, 0.0f);
		glRotatef(emitter->geometry.angle[2], 0.0f, 0.0f, 1.0f);
		drawAxis();
		glPopMatrix();
	}
}

void Engine::createEmitter()
{
	ParticleEmitter *defaultEmitter = new ParticleEmitter();

	defaultEmitter->particleModel = _particleModels->front();
	vectorClear(defaultEmitter->geometry.position);
	defaultEmitter->randomFacingDirection = true;
	vectorSet(defaultEmitter->geometry.position, 0.0f, 0.0f, 0.0f);
	vectorSet(defaultEmitter->geometry.angle, 0.0f, 0.0f, 0.0f);
	vectorSet(defaultEmitter->geometry.velocity, 1.0f, 0.0f, 0.0f);
	defaultEmitter->lastSpawn = 0;
	defaultEmitter->spawnInterval = 150;

	_emitters->push_back(defaultEmitter);
}

void Engine::destroyEmitter(int emitterID)
{
	ParticleEmitter *emitter = emitterWithID(emitterID);
	_emitters->remove(emitter);
	delete emitter;
}

void Engine::createParticle()
{
	/*BaseParticle *tempParticle = new BaseParticle(std::string("Default"));

	tempParticle->texturePath = std::string("../ParticleGenerator/Ressources/Textures/flare_white.jpg");
	tempParticle->shaderName = std::string("Default");
	tempParticle->lifeTime = 1000;
	tempParticle->defaultState = new ParticleState();
	tempParticle->transState = new ParticleState();
	tempParticle->transState->alpha = 0.0f;*/
	_particleModels = _parser->parseParticlesInFile("C:/Users/asusasus/Documents/4A3DJV/Projet Annuel/Documentation/model.txt");
	//_particleModels->push_back(tempParticle);

	//TEMP
	_parser->saveParticle(*(_particleModels->front()));
}

void Engine::destroyParticle(int particleID)
{
	BaseParticle *particle = particleWithID(particleID);
	_particleModels->remove(particle);

	// Find the emitters that used it and update them
	for (std::list<ParticleEmitter*>::const_iterator iterator = _emitters->begin(); iterator != _emitters->end(); ++iterator)
	{
		ParticleEmitter *emitter = *iterator;

		if (emitter->particleModel == particle)
		{
			emitter->particleModel = _particleModels->front();
		}
	}

	if (particle->defaultState)
	{
		delete particle->defaultState;
	}
	
	if (particle->transState)
	{
		delete particle->transState;
	}

	delete particle;
}

void Engine::_processParticle(BaseParticle *particle)
{
	particle->shader = shaderNamed(particle->shaderName);
	
	particle->texture = new Texture(particle->texturePath);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &particle->texture->textureID);
	glActiveTexture(GL_TEXTURE0 + particle->texture->textureID);
	glBindTexture(GL_TEXTURE_2D, particle->texture->textureID);
	glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			particle->texture->width,
			particle->texture->height,
			0,
			GL_RGBA,
			GL_FLOAT,
			particle->texture->data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	particle->processed = true;
}

void Engine::createShader()
{
	Shader *shader = new Shader();
	_shaders->push_back(shader);
}

void Engine::destroyShader(int shaderID)
{
	Shader *shader = shaderWithID(shaderID);
	_shaders->remove(shader);

	// Find the particles that used it and update them
	for (std::list<BaseParticle*>::const_iterator iterator = _particleModels->begin(); iterator != _particleModels->end(); ++iterator)
	{
		BaseParticle *emitter = *iterator;

		if (emitter->shader == shader)
		{
			emitter->shader = _shaders->front();
		}
	}

	glDeleteProgram(shader->program);

	delete shader;
}

BaseParticle* Engine::particleNamed(std::string name)
{
	std::list<BaseParticle*>::iterator particleIterator = std::find_if(_particleModels->begin(), _particleModels->end(), [name](BaseParticle* particle){ return particle->name == name; });
	if (particleIterator != _particleModels->end())
	{
		return *particleIterator;
	}
	return NULL;
}

BaseParticle* Engine::particleWithID(int particleID)
{
	std::list<BaseParticle*>::iterator iter = _particleModels->begin();
	std::advance(iter, particleID);
	return *iter;
}


Shader* Engine::shaderNamed(std::string name)
{
	std::list<Shader*>::iterator shaderIterator = std::find_if(_shaders->begin(), _shaders->end(), [name](Shader* shader){ return shader->name == name; });
	if (shaderIterator != _shaders->end())
	{
		return *shaderIterator;
	}
	return NULL;
}

Shader* Engine::shaderWithID(int shaderID)
{
	std::list<Shader*>::iterator iter = _shaders->begin();
	std::advance(iter, shaderID);
	return *iter;
}


ParticleEmitter* Engine::emitterWithID(int emitterID)
{
	std::list<ParticleEmitter*>::iterator iter = _emitters->begin();
	std::advance(iter, emitterID);
	return *iter;
}

int Engine::getParticleModelCount()
{
	return _particleModels->size();
}

int Engine::getActiveParticleCount()
{
	return _activeParticles->size();
}

int Engine::getEmitterCount()
{
	return _emitters->size();
}

int Engine::getShaderCount()
{
	return _shaders->size();
}
