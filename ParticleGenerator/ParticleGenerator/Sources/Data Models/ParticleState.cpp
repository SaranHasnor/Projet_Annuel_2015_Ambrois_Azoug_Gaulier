#include "ParticleState.h"


ParticleState::ParticleState(void)
{
	this->red = 1.0f;
	this->green = 1.0f;
	this->blue = 1.0f;
	this->alpha = 1.0f;
	this->scale = 1.0f;
	this->lightIntensity = 0.0f;
}


ParticleState::~ParticleState(void)
{
}


ParticleState* ParticleState::Lerp(ParticleState& target, float percentage)
{
	ParticleState *result = new ParticleState();
	float oldPercentage = 1.0f - percentage;

	result->red = this->red * oldPercentage + target.red * percentage;
	result->green = this->green * oldPercentage + target.green * percentage;
	result->blue = this->blue * oldPercentage + target.blue * percentage;
	result->alpha = this->alpha * oldPercentage + target.alpha * percentage;

	result->lightIntensity = this->lightIntensity * oldPercentage + target.lightIntensity * percentage;

	result->scale = this->scale * oldPercentage + target.scale * percentage;

	return result;
}