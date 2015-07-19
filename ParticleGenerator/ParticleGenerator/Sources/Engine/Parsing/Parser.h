#pragma once

#include <string>
#include <list>
#include <iostream>
#include <fstream>

class BaseParticle;
class ParticleEmitter;
class ParticleState;

class Parser
{
public:
	Parser(void);
	~Parser(void);

	ParticleState* parseParticleState(std::ifstream&, std::string&);
	/* Parse the value of a string field, the string parameter contains the return value */
	void parseStringField(std::ifstream&, std::string&);
	int parseIntField(std::ifstream&, std::string&);
	bool parseBoolField(std::ifstream&, std::string&);
	float* parseVectorField(std::ifstream&, std::string&);

	std::list<BaseParticle*>* parseParticlesInFile(const std::string filePath);
	std::list<ParticleEmitter*>* Parser::parseEmittersInFile(const std::string filePath);

	bool saveParticle(const BaseParticle& particle, const std::string path) const;
	bool saveParticleEmitter(const ParticleEmitter& particleEmitter, const std::string path) const;

	bool saveParticles(const std::list<BaseParticle*>* particles, const std::string path) const;
	bool saveParticleEmitters(const std::list<ParticleEmitter*>* emitters, const std::string path) const;
};