#include "ParticleEmitter.h"

#include "BaseParticle.h"

extern "C" {
#include <Utils\utils.h>
#include <Utils\vec3D.h>
}

ParticleEmitter::ParticleEmitter(void)
{
}


ParticleEmitter::~ParticleEmitter(void)
{
}


BaseParticle* ParticleEmitter::spawnParticle(BaseParticle& reference)
{
	BaseParticle *particle = new BaseParticle(reference);
	float axis[3][3];

	vectorCopy(particle->geometry.position, this->geometry.position);

	if (this->randomFacingDirection)
	{
		vectorSet(particle->geometry.angle,
			randomValueBetween(-90.0f, 90.0f),
			randomValueBetween(-180.0f, 180.0f),
			0.0f);
	}
	else
	{
		vectorCopy(particle->geometry.angle, this->geometry.angle);
	}

	AngleVectors(particle->geometry.angle, axis[0], axis[1], axis[2]);

	vectorCopy(particle->geometry.velocity, this->geometry.velocity);
	vectorRotate(particle->geometry.velocity, axis);

	return particle;
}