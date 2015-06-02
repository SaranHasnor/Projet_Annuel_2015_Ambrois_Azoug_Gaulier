#include "Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>


Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}


std::list<BaseParticle*>* Parser::parseParticlesInFile(std::string filePath)
{
	// Temporary
	BaseParticle *tempParticle = new BaseParticle(std::string("Default"));

	tempParticle->texturePath = std::string("../ParticleGenerator/Ressources/Textures/flare_white.jpg");
	tempParticle->shaderName = std::string("Default");
	tempParticle->lifeTime = 1000;

	std::list<BaseParticle*> *tempList = new std::list<BaseParticle*>;
	tempList->push_back(tempParticle);
	return tempList;
}