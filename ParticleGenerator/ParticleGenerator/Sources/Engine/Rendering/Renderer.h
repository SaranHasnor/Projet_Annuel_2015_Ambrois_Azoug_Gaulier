#pragma once

#include <list>

class BaseParticle;

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	void renderParticles(std::list<BaseParticle*> *particles, float viewMatrix[16]);
};

