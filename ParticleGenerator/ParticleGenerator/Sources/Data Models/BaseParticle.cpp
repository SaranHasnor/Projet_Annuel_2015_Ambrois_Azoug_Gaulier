#include "BaseParticle.h"

#include "ParticleState.h"

BaseParticle::BaseParticle(std::string name)
{
	this->name = name;
	this->processed = false;

	this->useGravity = false;

	vectorClear(this->geometry.velocity);
	vectorClear(this->geometry.acceleration);

	this->shader = NULL;
	this->texture = NULL;

	this->defaultState = NULL;
	this->transState = NULL;
}

BaseParticle::BaseParticle(BaseParticle &copy)
	: defaultState(copy.defaultState) , transState(copy.transState)
{
	this->name = copy.name;
	this->processed = copy.processed;

	this->useGravity = copy.useGravity;

	vectorClear(this->geometry.velocity);
	vectorClear(this->geometry.acceleration);

	this->lifeTime = copy.lifeTime;

	this->shader = copy.shader;
	this->texture = copy.texture;
}


BaseParticle::~BaseParticle(void)
{
}
