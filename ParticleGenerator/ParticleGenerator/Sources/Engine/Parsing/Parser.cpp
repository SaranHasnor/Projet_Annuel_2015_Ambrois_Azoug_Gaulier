#include "Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleState.h>
#include <Data Models/ParticleEmitter.h>


#include <fstream>
#include <sstream>
#include <algorithm>


Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}

ParticleState* Parser::parseParticleState(std::ifstream& ifs, std::string& line)
{
	ParticleState* tempParticleState = new ParticleState();
	do
	{
		ifs >> line;
		if (line == "colour")
		{
			char chars[] = ":[,";
			std::getline(ifs, line, ']');
			for (unsigned int i = 0; i < strlen(chars); ++i)
				line.erase(std::remove(line.begin(), line.end(), chars[i]), line.end());
			std::stringstream ss(line);
			ss >> tempParticleState->red
				>> tempParticleState->green
				>> tempParticleState->blue
				>> tempParticleState->alpha;
		}
		else if (line == "light")
		{
			ifs >> line >> line;
			if (line.at(line.size() - 1) == ',')
				line.erase(line.end() - 1);
			std::stringstream ss(line);
			ss >> tempParticleState->lightIntensity;
		}
		else if (line == "scale")
		{
			ifs >> line >> line;
			if (line.at(line.size() - 1) == ',')
				line.erase(line.end() - 1);
			std::stringstream ss(line);
			ss >> tempParticleState->scale;
		}
	} while(line != "}," && line != "}");
	return tempParticleState;
}

void Parser::parseStringField(std::ifstream& ifs, std::string& line)
{
	ifs >> line >> line;
	if (line.at(line.size() - 1) == ',')
		line.erase(line.end() - 1);
}

int Parser::parseIntField(std::ifstream& ifs, std::string& line)
{
	int result;
	ifs >> line >> line;
	if (line.at(line.size() - 1) == ',')
		line.erase(line.end() - 1);
	std::stringstream ss(line);
	ss >> result;
	return result;
}

bool Parser::parseBoolField(std::ifstream& ifs, std::string& line)
{
	ifs >> line >> line;
	if (line.at(line.size() - 1) == ',')
		line.erase(line.end() - 1);
	return (line == "false" ? false : true);
}

float* Parser::parseVectorField(std::ifstream& ifs, std::string& line)
{
	float vec[3];
	char chars[] = ":[,";
	std::getline(ifs, line, ']');
	for (unsigned int i = 0; i < strlen(chars); ++i)
		line.erase(std::remove(line.begin(), line.end(), chars[i]), line.end());
	std::stringstream ss(line);
	ss >> vec[0] >> vec[1] >> vec[2];
	return vec;
}


std::list<BaseParticle*>* Parser::parseParticlesInFile(std::string filePath)
{
	std::ifstream ifs(filePath, std::ifstream::in);
	std::list< BaseParticle* >* tempList = new std::list< BaseParticle* >;

	if (!ifs.good())
	{
		delete tempList;
		return nullptr;
	}

	while (!ifs.eof())
	{
		std::string line;
		BaseParticle* tempParticle = nullptr;
		do
		{
			ifs >> line;
		} while (line.find('{') == std::string::npos);

		//New Particle to parse
		ifs >> line;
		if (line != "name")
		{
			for (std::list<BaseParticle*>::const_iterator iterator = tempList->begin(); iterator != tempList->end(); ++iterator)
			{
				delete *iterator;
			}
			delete tempList;
			return nullptr; //Name is the first field of the particle
		}
		parseStringField(ifs, line);
		tempParticle = new BaseParticle(line);//Remove the ','

		do
		{
			ifs >> line;
			if (line == "gravity")
			{
				tempParticle->useGravity = parseBoolField(ifs, line);
			}
			else if (line == "lifetime")
			{
				tempParticle->lifeTime = parseIntField(ifs, line);
			}
			else if (line == "shader")
			{
				parseStringField(ifs, line);
				tempParticle->shaderName = line;
			}
			else if(line == "shaderPath") 
			{
				parseStringField(ifs, line);
				tempParticle->shaderPath = line;
			}
			else if (line == "texture")
			{
				parseStringField(ifs, line);
				tempParticle->texturePath = line;
			}
			else if (line == "defaultState")
			{
				tempParticle->defaultState = parseParticleState(ifs, line);
			}
			else if (line == "transState")
			{
				tempParticle->transState = parseParticleState(ifs, line);
			}
		} while (line != "}");

		tempList->push_back(tempParticle);
	}
	return tempList;
}

std::list<ParticleEmitter*>* Parser::parseEmittersInFile(std::string filePath)
{
	std::ifstream ifs(filePath, std::ifstream::in);
	std::list< ParticleEmitter* >* tempList = new std::list< ParticleEmitter* >;

	if (!ifs.good())
	{
		delete tempList;
		return nullptr;
	}

	while (!ifs.eof())
	{
		std::string line;
		ParticleEmitter *tempEmitter = new ParticleEmitter();
		do
		{
			ifs >> line;
		} while (line.find('{') == std::string::npos);
		do
		{
			ifs >> line;
			if (line == "model")
			{
				parseStringField(ifs, line);
				tempEmitter->particleName = line;
			}
			else if (line == "randomDirection")
			{
				tempEmitter->randomFacingDirection = parseBoolField(ifs, line);
			}
			else if (line == "position")
			{
				float* vec = parseVectorField(ifs, line);
				vectorSet(tempEmitter->geometry.position, vec[0], vec[1], vec[2]);
			}
			else if (line == "angle")
			{
				float* vec = parseVectorField(ifs, line);
				vectorSet(tempEmitter->geometry.angle, vec[0], vec[1], vec[2]);
			}
			else if (line == "velocity")
			{
				float* vec = parseVectorField(ifs, line);
				vectorSet(tempEmitter->geometry.velocity, vec[0], vec[1], vec[2]);
			}
			else if (line == "acceleration")
			{
				float* vec = parseVectorField(ifs, line);
				vectorSet(tempEmitter->geometry.acceleration, vec[0], vec[1], vec[2]);
			}
			else if (line == "spawnInterval")
			{
				tempEmitter->spawnInterval = parseIntField(ifs, line);
			}
		} while (line != "}");

		tempList->push_back(tempEmitter);
	}
	return tempList;
}


bool Parser::saveParticle(const BaseParticle& particle, const std::string path) const
{
	std::ofstream particleSaveFile(path, std::ios::out | std::ios::trunc);

	if (!particleSaveFile.good())
		return false;

	particleSaveFile << "{" << std::endl
		<< "\tname : " << particle.name << "," << std::endl
		<< std::endl
		<< "\tgravity : " << (particle.useGravity ? "true" : "false") << "," << std::endl
		<< std::endl
		<< "\tlifetime : " << particle.lifeTime << "," << std::endl
		<< std::endl
		<< "\tshader : " << particle.shaderName << "," << std::endl
		<< "\tshaderPath : " << (particle.shader?particle.shader->path:particle.shaderPath) << "," << std::endl
		<< std::endl
		<< "\ttexture : " << particle.texturePath << "," << std::endl
		<< std::endl
		<< "\tdefaultState : {" << std::endl
		<< "\t\tcolour : [" << particle.defaultState->red << ", " << particle.defaultState->green << ", " << particle.defaultState->blue << ", " << particle.defaultState->alpha << "]," << std::endl
		<< "\t\tlight : " << particle.defaultState->lightIntensity << "," << std::endl
		<< "\t\tscale : " << particle.defaultState->scale << std::endl
		<< "\t}," << std::endl
		<< "\ttransState : {" << std::endl
		<< "\t\tcolour : [" << particle.transState->red << ", " << particle.transState->green << ", " << particle.transState->blue << ", " << particle.transState->alpha << "]," << std::endl
		<< "\t\tlight : " << particle.transState->lightIntensity << "," << std::endl
		<< "\t\tscale : " << particle.transState->scale << std::endl
		<< "\t}" << std::endl
		<< "}" << std::endl;

	particleSaveFile.close();

	return true;
}

bool Parser::saveParticleEmitter(const ParticleEmitter& particleEmitter, const std::string path) const
{
	std::ofstream particleEmitterSaveFile(path, std::ios::out | std::ios::trunc);

	if(!particleEmitterSaveFile.good())
		return false;

	particleEmitterSaveFile << std::fixed << "{" << std::endl
		<< "\tmodel : " << particleEmitter.particleName << "," << std::endl
		<< std::endl
		<< "\trandomDirection : " << (particleEmitter.randomFacingDirection ? "true" : "false") << ", " << std::endl
		<< std::endl
		<< "\tposition : [" << particleEmitter.geometry.position[0] << ", " << particleEmitter.geometry.position[1] << ", " << particleEmitter.geometry.position[2] << "]," << std::endl
		<< "\tangle : [" << particleEmitter.geometry.angle[0] << ", " << particleEmitter.geometry.angle[1] << ", " << particleEmitter.geometry.angle[2] << "]," << std::endl
		<< "\tvelocity : [" << particleEmitter.geometry.velocity[0] << ", " << particleEmitter.geometry.velocity[1] << ", " << particleEmitter.geometry.velocity[2] << "]," << std::endl
		<< "\tacceleration : [" << particleEmitter.geometry.acceleration[0] << ", " << particleEmitter.geometry.acceleration[1] << ", " << particleEmitter.geometry.acceleration[2] << "]," << std::endl
		<< std::endl
		<< "\tspawnInterval : " << particleEmitter.spawnInterval << std::endl
		<< "}";

		particleEmitterSaveFile.close();

	return true;
}