#pragma once


class ParticleState
{
public:
	ParticleState(void);
	~ParticleState(void);

	float			red, green, blue, alpha;	// RGBA values of the particle (applied to the shader)
	float			lightIntensity;				// Intensity of the light emitted by this particle (uses RGB)
	float			scale;						// Scale of the particle (applied to the shader)

	ParticleState&	Lerp(ParticleState& target, float percentage);
};

