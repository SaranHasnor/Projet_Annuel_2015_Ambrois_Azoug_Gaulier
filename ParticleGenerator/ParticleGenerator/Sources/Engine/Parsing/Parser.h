#pragma once

#include <string>
#include <list>

class BaseParticle;

class Parser
{
public:
	Parser(void);
	~Parser(void);

	std::list<BaseParticle*>* parseFile( std::string filePath);
};

