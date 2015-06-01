#include "BaseParticle.h"

#include "ParticleState.h"

BaseParticle::BaseParticle(std::string name)
	: defaultState(ParticleState()) , transState(ParticleState())
{
	this->name = name;
	this->linked = false;

	vectorClear(this->geometry.velocity);
	vectorClear(this->geometry.acceleration);

	this->shader = NULL;
	this->texture = NULL;
}

BaseParticle::BaseParticle(BaseParticle &copy)
	: defaultState(copy.defaultState) , transState(copy.transState)
{
	this->name = copy.name;
	this->linked = false;

	vectorClear(this->geometry.velocity);
	vectorClear(this->geometry.acceleration);

	this->lifeTime = copy.lifeTime;

	this->shader = copy.shader;
	this->texture = copy.texture;
}


BaseParticle::~BaseParticle(void)
{
}
