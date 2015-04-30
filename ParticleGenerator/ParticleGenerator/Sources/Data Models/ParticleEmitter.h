#pragma once

#include <string>

class BaseParticle;

class ParticleEmitter
{
public:
	ParticleEmitter(void);
	~ParticleEmitter(void);

	float			posX, posY, posZ;			// Position of the emitter

	std::string		particleName;				// Name of the particle to emit
	float			velX, velY, velZ;			// Velocity at which to emit the particles
	bool			randomFacingDirection;		// Gives the particle a random facing direction (temporary)

	unsigned int	spawnInterval;				// Interval at which to spawn particles (in milliseconds)
	unsigned int	lastSpawn;					// Last time at which a particle was spawned (run-time variable)


	BaseParticle*	spawnParticle(BaseParticle& reference);
};

