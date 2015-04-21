#include "engine_wrapper.h"

#include "Engine.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/ParticleState.h>

static Engine* _staticEngine;

extern "C" void initEngine()
{
	_staticEngine = new Engine();
}

extern "C" void runEngine()
{
	_staticEngine->run();
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
		return (void*)&particle->posX;
	case PART_ATTR_POS_Y:
		return (void*)&particle->posY;
	case PART_ATTR_POS_Z:
		return (void*)&particle->posZ;
	case PART_ATTR_VEL_X:
		return (void*)&particle->velX;
	case PART_ATTR_VEL_Y:
		return (void*)&particle->velX;
	case PART_ATTR_VEL_Z:
		return (void*)&particle->velX;
	case PART_ATTR_ACCEL_X:
		return (void*)&particle->accelX;
	case PART_ATTR_ACCEL_Y:
		return (void*)&particle->accelX;
	case PART_ATTR_ACCEL_Z:
		return (void*)&particle->accelX;
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