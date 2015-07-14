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

	std::list<BaseParticle*>* parseParticlesInFile(std::string filePath);
	std::list<ParticleEmitter*>* Parser::parseEmittersInFile(std::string filePath);

	bool saveParticle(const BaseParticle& particle) const;
	bool saveParticleEmitter(const ParticleEmitter& particleEmitter) const;

};

