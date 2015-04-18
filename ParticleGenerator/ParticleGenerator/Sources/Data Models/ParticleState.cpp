#include "ParticleState.h"


ParticleState::ParticleState(void)
{
}


ParticleState::~ParticleState(void)
{
}


ParticleState& ParticleState::Lerp(ParticleState& target, float percentage)
{
	ParticleState &result = ParticleState();
	float oldPercentage = 1.0f - percentage;

	target.red = this->red * oldPercentage + target.red * percentage;
	target.green = this->green * oldPercentage + target.green * percentage;
	target.blue = this->blue * oldPercentage + target.blue * percentage;
	target.alpha = this->alpha * oldPercentage + target.alpha * percentage;

	target.lightIntensity = this->lightIntensity * oldPercentage + target.lightIntensity * percentage;

	target.scale = this->scale * oldPercentage + target.scale * percentage;

	return result;
}