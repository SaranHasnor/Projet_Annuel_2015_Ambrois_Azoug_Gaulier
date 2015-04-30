#include "Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/BaseEmitter.h>
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
	BaseParticle *tempParticle = new BaseParticle();

	tempParticle->shaderName = std::string("Default");
	tempParticle->texturePath = std::string("../ParticleGenerator/Ressources/Textures/flare_white.jpg");

	std::list<BaseParticle*> *tempList = new std::list<BaseParticle*>;
	tempList->push_back(tempParticle);
	return tempList;
}

std::list<BaseEmitter*>* Parser::parseEmittersInFile(std::string filePath)
{
	// Temporary
	//BaseEmitter *tempEmitter = new BaseEmitter();


	std::list<BaseEmitter*> *tempList = new std::list<BaseEmitter*>;
	//tempList->push_back(tempEmitter);
	return tempList;
}