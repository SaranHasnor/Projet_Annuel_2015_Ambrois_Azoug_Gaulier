#include "Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleState.h>

#include <fstream>


Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}


std::list<BaseParticle*>* Parser::parseParticlesInFile(std::string filePath)
{
	std::ifstream ifs(filePath, std::ifstream::in);

	if (!ifs.good())
		return nullptr;

	while (!ifs.eof())
	{
		std::string line;
		BaseParticle* tempParticle = nullptr;
		do
		{
			ifs >> line;
		} while (line.find('{') != std::string::npos);
		if (std::getline(ifs, line, ':'))
		{
			if (line.find("name"))
			{

				tempParticle = new BaseParticle();
			}
		}

	}



	BaseParticle *tempParticle = new BaseParticle(std::string("Default"));

	tempParticle->texturePath = std::string("../ParticleGenerator/Ressources/Textures/flare_white.jpg");
	tempParticle->shaderName = std::string("Default");
	tempParticle->lifeTime = 1000;
	tempParticle->defaultState = new ParticleState();
	tempParticle->transState = new ParticleState();
	tempParticle->transState->alpha = 0.0f;

	std::list<BaseParticle*> *tempList = new std::list<BaseParticle*>;
	tempList->push_back(tempParticle);
	return tempList;
}