#pragma once

#include <string>

class ParticleState;

class BaseParticle
{

public:
	BaseParticle(void);
	~BaseParticle(void);

	std::string		name;						// Name of the particle

	float			posX, posY, posZ;			// Position of the particle
	float			pitch, yaw, roll;			// Rotation of the particle

	float			velX, velY, velZ;			// Velocity of the particle
	float			accelX, accelY, accelZ;		// Acceleration applied to the particle

	bool			useGravity;					// Should the particle be affected by gravity?

	unsigned int	collisionFlags;				// Physical layers the particle can collide with
	std::string		impactParticle;				// Name of the particle to create on death

	unsigned long	spawnTime;					// Time at which the particle was created (in milliseconds)
	unsigned long	lifeTime;					// Duration of the particle (in milliseconds)

	std::string		shaderName;					// Name of the shader used to render the particle
	
	ParticleState	&defaultState;				// Extra graphical data
	ParticleState	&transState;				// Graphical data to use when the particle dies
};

