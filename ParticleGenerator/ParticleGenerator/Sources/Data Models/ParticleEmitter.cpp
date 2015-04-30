#include "ParticleEmitter.h"

#include "BaseParticle.h"

ParticleEmitter::ParticleEmitter(void)
{
}


ParticleEmitter::~ParticleEmitter(void)
{
}


BaseParticle* ParticleEmitter::spawnParticle(BaseParticle& reference)
{
	BaseParticle *particle = new BaseParticle(reference);

	particle->posX = this->posX;
	particle->posY = this->posY;
	particle->posZ = this->posZ;

	if (this->randomFacingDirection)
	{ // TODO
		particle->pitch = 0.0f;
		particle->yaw = 0.0f;
		particle->roll = 0.0f;
	}

	particle->velX = this->velX;
	particle->velY = this->velY;
	particle->velZ = this->velZ;

	return particle;
}