#pragma once

#include <string>

#include "GeometryData.h"

class ParticleState;
class Shader;
class Texture;

class BaseParticle
{

public:
	BaseParticle(std::string name);
	BaseParticle(BaseParticle &copy);
	~BaseParticle(void);

	std::string		name;						// Name of the particle
	bool			processed;					// If true, the particle's shader and texture have been loaded

	GeometryData	geometry;					// Spatial properties of the emitter

	bool			useGravity;					// Should the particle be affected by gravity?

	unsigned int	collisionFlags;				// Physical layers the particle can collide with
	std::string		impactParticle;				// Name of the particle to create on death

	unsigned long	spawnTime;					// Time after which the particle should appear after being created (in milliseconds)
	unsigned long	lifeTime;					// Duration of the particle (in milliseconds)

	std::string		shaderName;					// Name of the shader used to render the particle
	std::string		shaderPath;					// Path to the file of the shader (only used for parsing)
	Shader*			shader;						// Shader used to render the particle (run-time variable)

	std::string		texturePath;				// Path to the texture used for this particle
	Texture*		texture;					// OpenGL texture to use (run-time variable)
	
	ParticleState*	defaultState;				// Extra graphical data
	ParticleState*	transState;					// Graphical data to use when the particle dies
};

