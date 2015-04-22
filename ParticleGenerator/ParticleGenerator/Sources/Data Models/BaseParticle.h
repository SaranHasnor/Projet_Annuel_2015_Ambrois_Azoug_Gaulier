#pragma once

#include <string>

class ParticleState;
class Shader;
class Texture;

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

	unsigned long	spawnTime;					// Time after which the particle should appear after being created (in milliseconds)
	unsigned long	lifeTime;					// Duration of the particle (in milliseconds)

	std::string		shaderName;					// Name of the shader used to render the particle
	Shader*			shader;						// Shader used to render the particle (run-time variable)

	std::string		texturePath;				// Path to the texture used for this particle
	Texture*		texture;					// OpenGL texture to use (run-time variable)
	
	ParticleState&	defaultState;				// Extra graphical data
	ParticleState&	transState;					// Graphical data to use when the particle dies
};

