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

	std::list<BaseParticle*>* parseParticlesInFile(const std::string filePath = "../../Documentation/particlesSaved.txt");
	std::list<ParticleEmitter*>* Parser::parseEmittersInFile(const std::string filePath= "../../Documentation/particleEmittersSaved.txt");

	bool saveParticle(const BaseParticle& particle, const std::string path = "../../Documentation/particlesSaved.txt") const;
	bool saveParticleEmitter(const ParticleEmitter& particleEmitter, const std::string path = "../../Documentation/particleEmittersSaved.txt") const;
};