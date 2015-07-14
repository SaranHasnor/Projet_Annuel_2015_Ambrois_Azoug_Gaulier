#include "Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleState.h>

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
	} while (line != "},");
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
		} while (line.find('{') == std::string::npos);

		//New Particle to parse
		ifs >> line;
		if (line != "name")
			return nullptr; //Name is the first field of the particle
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

bool Parser::saveParticle(const BaseParticle& particle) const {
	std::string fileName = "particle_" + particle.name + ".save";

	std::ofstream particleSaveFile(fileName, std::ios::out | std::ios::trunc);

	if(!particleSaveFile.good()) {
		return false;
	}
	else {
		particleSaveFile << "{" << std::endl
			<< "\tname : " << particle.name << "," << std::endl
			<< std::endl
			<< "\tgravity : " << (particle.useGravity ? "true" : "false") << "," << std::endl
			<< std::endl
			<< "\tlifetime : " << particle.lifeTime << "," << std::endl
			<< std::endl
			<< "\tshader : " << particle.shaderName << "," << std::endl
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
			<< "\t}," << std::endl
			<< "}" << std::endl;

		particleSaveFile.close();
	}

	return true;
}

bool Parser::saveParticleEmitter(const ParticleEmitter& particleEmitter) const 
{
	//TODO: ajouter la date ?
	std::string fileName = "particleEmitter.save";

	std::ofstream particleEmitterSaveFile(fileName, std::ios::out | std::ios::trunc);

	if(!particleEmitterSaveFile.good()) {
		return false;
	}
	else {
		//particleEmitterSaveFile << "{" << std::endl
		//	<< "\tname : \"" << particle.name << "\"," << std::endl
		//	<< std::endl
		//	<< "\tstartPos : [" << particle.geometry.position[0] << ", " << particle.geometry.position[1] << ", " << particle.geometry.position[2] << "]," << std::endl
		//	<< "\tstartAngle : [" << particle.geometry.angle[0] << ", " << particle.geometry.angle[1] << ", " << particle.geometry.angle[2] << "]," << std::endl
		//	<< "\tvelocitiy : [" << particle.geometry.velocity[0] << ", " << particle.geometry.velocity[1] << ", " << particle.geometry.velocity[2] << "]," << std::endl
		//	<< "\trotation : [" << particle.geometry.rotation[0] << ", " << particle.geometry.rotation[1] << ", " << particle.geometry.rotation[2] << "]," << std::endl
		//	<< "\tacceleration : [" << particle.geometry.acceleration[0] << ", " << particle.geometry.acceleration[1] << ", " << particle.geometry.acceleration[2] << "]," << std::endl
		//	<< std::endl
		//	<< "\tgravity : " << (particle.useGravity ? "true" : "false") << "," << std::endl
		//	<< std::endl
		//	<< "\tlifetime : " << particle.lifeTime << "," << std::endl
		//	<< std::endl
		//	<< "\tshader : \"" << particle.shaderName << "\"," << std::endl
		//	<< std::endl
		//	<< "\ttexture : \"" << particle.texturePath << "\"," << std::endl
		//	<< std::endl
		//	<< "\tdefaultState : {" << std::endl
		//	<< "\t\tcolour : [" << particle.defaultState->red << ", " << particle.defaultState->green << ", " << particle.defaultState->blue << ", " << particle.defaultState->alpha << "]," << std::endl
		//	<< "\t\tlight : " << particle.defaultState->lightIntensity << "," << std::endl
		//	<< "\t\tscale : " << particle.defaultState->scale << "," << std::endl
		//	<< "\t}," << std::endl
		//	<< "\ttransState : {" << std::endl
		//	<< "\t\tcolour : [" << particle.transState->red << ", " << particle.transState->green << ", " << particle.transState->blue << ", " << particle.transState->alpha << "]," << std::endl
		//	<< "\t\tlight : " << particle.transState->lightIntensity << "," << std::endl
		//	<< "\t\tscale : " << particle.transState->scale << "," << std::endl
		//	<< "\t}," << std::endl
		//	<< "}" << std::endl;

		particleEmitterSaveFile.close();
	}

	return true;
}
