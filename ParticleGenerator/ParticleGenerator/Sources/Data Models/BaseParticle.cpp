#include "BaseParticle.h"

#include "ParticleState.h"

BaseParticle::BaseParticle(void)
	: defaultState(ParticleState()) , transState(ParticleState())
{
}


BaseParticle::~BaseParticle(void)
{
}
