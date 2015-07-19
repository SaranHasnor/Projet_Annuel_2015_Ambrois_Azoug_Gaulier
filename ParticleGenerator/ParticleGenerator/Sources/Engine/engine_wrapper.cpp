#include "engine_wrapper.h"

#include "Engine.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/ParticleState.h>
#include <Data Models/ParticleEmitter.h>
#include <Data Models/Shader.h>
#include <Data Models/ParticleState.h>
#include <Data Models/Texture.h>

static Engine* _staticEngine = NULL;

extern "C" void initEngine()
{
	_staticEngine = new Engine();
}

extern "C" void updateEngine(float deltaTime)
{
	_staticEngine->update(deltaTime);
}

extern "C" void renderEngine(float viewMatrix[16])
{
	_staticEngine->render(viewMatrix);
}

extern "C" void *particleAttribute(int particleID, particle_attr_t attribute)
{
	BaseParticle *particle = _staticEngine->particleWithID(particleID);

	if (!particle)
	{
		return NULL;
	}

	switch (attribute)
	{
	case PART_ATTR_NAME:
		return (void*)&particle->name;
	case PART_ATTR_POS_X:
		return (void*)&particle->geometry.position[0];
	case PART_ATTR_POS_Y:
		return (void*)&particle->geometry.position[1];
	case PART_ATTR_POS_Z:
		return (void*)&particle->geometry.position[2];
	case PART_ATTR_VEL_X:
		return (void*)&particle->geometry.velocity[0];
	case PART_ATTR_VEL_Y:
		return (void*)&particle->geometry.velocity[1];
	case PART_ATTR_VEL_Z:
		return (void*)&particle->geometry.velocity[2];
	case PART_ATTR_ACCEL_X:
		return (void*)&particle->geometry.acceleration[0];
	case PART_ATTR_ACCEL_Y:
		return (void*)&particle->geometry.acceleration[1];
	case PART_ATTR_ACCEL_Z:
		return (void*)&particle->geometry.acceleration[2];
	case PART_ATTR_LIFETIME:
		return (void*)&particle->lifeTime;
	case PART_ATTR_START_RED:
		return (void*)&particle->defaultState->red;
	case PART_ATTR_START_GREEN:
		return (void*)&particle->defaultState->green;
	case PART_ATTR_START_BLUE:
		return (void*)&particle->defaultState->blue;
	case PART_ATTR_START_ALPHA:
		return (void*)&particle->defaultState->alpha;
	case PART_ATTR_START_SCALE:
		return (void*)&particle->defaultState->scale;
	case PART_ATTR_END_RED:
		return (void*)&particle->transState->red;
	case PART_ATTR_END_GREEN:
		return (void*)&particle->transState->green;
	case PART_ATTR_END_BLUE:
		return (void*)&particle->transState->blue;
	case PART_ATTR_END_ALPHA:
		return (void*)&particle->transState->alpha;
	case PART_ATTR_END_SCALE:
		return (void*)&particle->transState->scale;
	case PART_ATTR_SHADER:
		return (void*)&particle->shaderName;
	case PART_ATTR_TEXTURE:
		return (void*)&particle->texturePath;
	default:
		return NULL;
	}
}

extern "C" short particleHasTransition(int particleID)
{
	return _staticEngine->particleWithID(particleID)->transState != NULL;
}

extern "C" void toggleParticleTransition(int particleID)
{
	_staticEngine->toggleTransStateInParticleWithID(particleID);
}

extern "C" void *emitterAttribute(int emitterID, emitter_attr_t attribute)
{
	ParticleEmitter *emitter = _staticEngine->emitterWithID(emitterID);

	if (!emitter)
	{
		return NULL;
	}

	switch (attribute)
	{
	case EMIT_ATTR_PARTICLE_NAME:
		return (void*)&emitter->particleModel->name;
	case EMIT_ATTR_POS_X:
		return (void*)&emitter->geometry.position[0];
	case EMIT_ATTR_POS_Y:
		return (void*)&emitter->geometry.position[1];
	case EMIT_ATTR_POS_Z:
		return (void*)&emitter->geometry.position[2];
	case EMIT_ATTR_VEL_X:
		return (void*)&emitter->geometry.velocity[0];
	case EMIT_ATTR_VEL_Y:
		return (void*)&emitter->geometry.velocity[1];
	case EMIT_ATTR_VEL_Z:
		return (void*)&emitter->geometry.velocity[2];
	case EMIT_ATTR_PITCH:
		return (void*)&emitter->geometry.angle[0];
	case EMIT_ATTR_YAW:
		return (void*)&emitter->geometry.angle[1];
	case EMIT_ATTR_ROLL:
		return (void*)&emitter->geometry.angle[2];
	case EMIT_ATTR_SPAWN_INTERVAL:
		return (void*)&emitter->spawnInterval;
	case EMIT_ATTR_RANDOM_DIR:
		return (void*)&emitter->randomFacingDirection;
	default:
		return NULL;
	}
}

extern "C" void *shaderName(int shaderID)
{
	return &_staticEngine->shaderWithID(shaderID)->name;
}

extern "C" void *shaderPath(int shaderID)
{
	return &_staticEngine->shaderWithID(shaderID)->path;
}

extern "C" int getActiveParticleCount()
{
	return _staticEngine->getActiveParticleCount();
}

extern "C" int getParticleModelCount()
{
	return _staticEngine->getParticleModelCount();
}

extern "C" int getEmitterCount()
{
	return _staticEngine->getEmitterCount();
}

extern "C" int getShaderCount()
{
	return _staticEngine->getShaderCount();
}

extern "C" void createEmitter()
{
	_staticEngine->createEmitter();
}

extern "C" void destroyEmitter(int emitterID)
{
	_staticEngine->destroyEmitter(emitterID);
}

extern "C" void setEmitterParticle(int emitterID, int particleID)
{
	_staticEngine->emitterWithID(emitterID)->particleModel = _staticEngine->particleWithID(particleID);
}

extern "C" void createParticle()
{
	_staticEngine->createParticle();
}

extern "C" void destroyParticle(int particleID)
{
	_staticEngine->destroyParticle(particleID);
}

extern "C" void setParticleShader(int particleID, int shaderID)
{
	Shader *shader = _staticEngine->shaderWithID(shaderID);
	BaseParticle *particle = _staticEngine->particleWithID(particleID);
	particle->shaderName = shader->name;
	particle->shader = shader;
}

extern "C" void createShader()
{
	_staticEngine->createShader();
}

extern "C" void destroyShader(int shaderID)
{
	_staticEngine->destroyShader(shaderID);
}

extern "C" void reloadShader(int shaderID)
{
	_staticEngine->shaderWithID(shaderID)->compiled = false;
}

extern "C" void reloadParticleTexture(int particleID)
{
	BaseParticle *particle = _staticEngine->particleWithID(particleID);
	particle->processed = false; // Just reprocess it, that will reload the texture
}

extern "C" void saveCurrentSession(void)
{
	_staticEngine->saveSession();
}

extern "C" void loadNewSession(void)
{
	_staticEngine->loadSession();
}

extern "C" void exportEmitters(char *path)
{
	_staticEngine->exportEmitters(std::string(path));
}

extern "C" void importEmitters(char *path)
{
	_staticEngine->importEmitters(std::string(path));
}

extern "C" void exportParticles(char *path)
{
	_staticEngine->exportParticles(std::string(path));
}

extern "C" void importParticles(char *path)
{
	_staticEngine->importParticles(std::string(path));
}
