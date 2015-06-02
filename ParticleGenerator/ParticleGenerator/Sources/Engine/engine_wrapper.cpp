#include "engine_wrapper.h"

#include "Engine.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/ParticleState.h>
#include <Data Models/ParticleEmitter.h>

static Engine* _staticEngine = NULL;

extern "C" void initEngine()
{
	_staticEngine = new Engine();
}

extern "C" void updateEngine(float deltaTime)
{
	_staticEngine->update(deltaTime);
}

extern "C" void renderEngine()
{
	_staticEngine->render();
}

extern "C" void *particleAttribute(char *particleName, particle_attr_t attribute)
{
	BaseParticle *particle = _staticEngine->particleNamed(std::string(particleName));

	if (!particle)
	{
		return NULL;
	}

	switch (attribute)
	{
	case PART_ATTR_NAME:
		return (void*)particle->name.c_str();
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
		return (void*)&particle->defaultState.red;
	case PART_ATTR_START_GREEN:
		return (void*)&particle->defaultState.green;
	case PART_ATTR_START_BLUE:
		return (void*)&particle->defaultState.blue;
	case PART_ATTR_START_ALPHA:
		return (void*)&particle->defaultState.alpha;
	case PART_ATTR_START_SCALE:
		return (void*)&particle->defaultState.scale;
	default:
		return NULL;
	}
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
		return (void*)emitter->particleName.c_str();
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