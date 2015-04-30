#pragma once

#include <string>
#include <list>
#include <map>

class BaseParticle;

class BaseEmitter 
{

public:
	BaseEmitter(void);
	~BaseEmitter(void);

	std::string		name;						// Name of the particle emitter

	BaseParticle*	baseParticle;				// Type of particle emitted

	float			posX, posY, posZ;			// Position of the emitter
	float			pitch, yaw, roll;			// Rotation of the emitter

	int				particleCreationRate;		// Speed of emission(?) of the particles (particles created per second)

	float			accelX, accelY, accelZ;		// Initial acceleration applied to the particles

	bool			useGravity;					// Should the emitter be affected by gravity?

	unsigned long	spawnTime;					// Time after which the emitter should start emitting after being created (in milliseconds)
	unsigned long	lifeTime;					// Duration of the emitter (in milliseconds)

	// TODO
	//std::list<BaseParticle*>* baseParticles;			// Alternative, list of particles randomly emitted
	//std::map<BaseParticle*, float>* baseParticles;	// Alternative, map of particles and associated rate of appearance (ex: sum of all weights = 1)
};