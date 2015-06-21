#pragma once

#include <string>

#include "GeometryData.h"

class BaseParticle;

class ParticleEmitter
{
public:
	ParticleEmitter(void);
	~ParticleEmitter(void);

	GeometryData	geometry;					// Spatial properties of the emitter

	BaseParticle	*particleModel;				// Model of the particle to emit
	bool			randomFacingDirection;		// Gives the particle a random facing direction (temporary)

	unsigned int	spawnInterval;				// Interval at which to spawn particles (in milliseconds)
	unsigned int	lastSpawn;					// Last time at which a particle was spawned (run-time variable)


	BaseParticle*	spawnParticle(BaseParticle& reference);
};

