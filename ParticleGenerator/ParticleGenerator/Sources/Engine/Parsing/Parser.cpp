#include "Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleState.h>

#include <fstream>
#include <sstream>


Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}


std::list<BaseParticle*>* Parser::parseParticlesInFile(std::string filePath)
{
	std::ifstream ifs(filePath, std::ifstream::in);
	std::list< BaseParticle* >* tempList = new std::list< BaseParticle* >;

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

		//New Particle to parse
		ifs >> line;
		if (line != "name")
			return nullptr; //Name is the first field of the particle
		ifs >> line >> line;
		if (line.at(line.size() - 1) == ',')
			line.erase(line.end() - 1);
		tempParticle = new BaseParticle(line);//Remove the ','

		do
		{
			ifs >> line;
			if (line == "gravity")
			{
				ifs >> line >> line; 
				if (line.at(line.size() - 1) == ',')
					line.erase(line.end() - 1);
				tempParticle->useGravity = (line == "false" ? false : true);
			}
			else if (line == "lifetime")
			{
				int lifetime;
				ifs >> line >> line;
				if (line.at(line.size() - 1) == ',')
					line.erase(line.end() - 1);
				std::stringstream ss(line);
				ss >> tempParticle->lifeTime;
			}
			else if (line == "shader")
			{
				ifs >> line >> line;
				if (line.at(line.size() - 1) == ',')
					line.erase(line.end() - 1);
				tempParticle->shaderName = line;
			}
			else if (line == "texture")
			{
				ifs >> line >> line;
				if (line.at(line.size() - 1) == ',')
					line.erase(line.end() - 1);
				tempParticle->texturePath = line;
			}
			else if (line == "defaultState")
			{
				std::getline(ifs, line, '}');
				ifs >> line >> line;
				if (line.at(line.size() - 1) == ',')
					line.erase(line.end() - 1);
				tempParticle->shaderName = line;
			}
			else if (line == "transState")
			{

			}
		} while (line != "}");

		tempList->push_back(tempParticle);
	}



	BaseParticle *tempParticle = new BaseParticle(std::string("Default"));

	tempParticle->texturePath = std::string("../ParticleGenerator/Ressources/Textures/flare_white.jpg");
	tempParticle->shaderName = std::string("Default");
	tempParticle->lifeTime = 1000;
	tempParticle->defaultState = new ParticleState();
	tempParticle->transState = new ParticleState();
	tempParticle->transState->alpha = 0.0f;

	std::list< BaseParticle* >* tempList = new std::list< BaseParticle* >;
	tempList->push_back(tempParticle);
	return tempList;
}