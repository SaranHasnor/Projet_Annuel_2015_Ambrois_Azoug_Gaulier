#pragma once

#include <string>
#include <list>
#include <iostream>
#include <fstream>

class BaseParticle;
class ParticleEmitter;

class Parser
{
public:
	Parser(void);
	~Parser(void);

	std::list<BaseParticle*>* parseParticlesInFile(std::string filePath);

	bool saveParticle(const BaseParticle& particle) const;
	bool saveParticleEmitter(const ParticleEmitter& particleEmitter) const;
};

