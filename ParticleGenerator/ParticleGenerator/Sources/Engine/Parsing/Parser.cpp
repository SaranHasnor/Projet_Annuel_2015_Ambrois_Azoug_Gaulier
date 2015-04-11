#include "Parser.h"
#include "../../Data Models/BaseParticle.h"


Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}


std::list<BaseParticle*>* Parser::parseFile(std::string filePath)
{
	// Temporary
	BaseParticle *tempParticle = new BaseParticle();
	std::list<BaseParticle*> *tempList = new std::list<BaseParticle*>;

	tempList->push_back(tempParticle);
	
	return tempList;
}