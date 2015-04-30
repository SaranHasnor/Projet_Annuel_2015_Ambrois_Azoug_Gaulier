#pragma once

#include <string>
#include <list>

class BaseParticle;
class BaseEmitter;

class Parser
{
public:
	Parser(void);
	~Parser(void);

	std::list<BaseParticle*>* parseParticlesInFile(std::string filePath);
	std::list<BaseEmitter*>* parseEmittersInFile(std::string filePath);
};

