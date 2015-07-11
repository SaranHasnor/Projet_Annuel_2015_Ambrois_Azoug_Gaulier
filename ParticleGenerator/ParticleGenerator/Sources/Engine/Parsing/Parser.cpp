#include "Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleState.h>


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
	tempParticle->defaultState = new ParticleState();
	tempParticle->transState = new ParticleState();
	tempParticle->transState->alpha = 0.0f;

	std::list<BaseParticle*> *tempList = new std::list<BaseParticle*>;
	tempList->push_back(tempParticle);
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
			<< "\tname : \"" << particle.name << "\"," << std::endl
			<< std::endl
			<< "\tstartPos : [" << particle.geometry.position[0] << ", " << particle.geometry.position[1] << ", " << particle.geometry.position[2] << "]," << std::endl
			<< "\tstartAngle : [" << particle.geometry.angle[0] << ", " << particle.geometry.angle[1] << ", " << particle.geometry.angle[2] << "]," << std::endl
			<< "\tvelocitiy : [" << particle.geometry.velocity[0] << ", " << particle.geometry.velocity[1] << ", " << particle.geometry.velocity[2] << "]," << std::endl
			<< "\trotation : [" << particle.geometry.rotation[0] << ", " << particle.geometry.rotation[1] << ", " << particle.geometry.rotation[2] << "]," << std::endl
			<< "\tacceleration : [" << particle.geometry.acceleration[0] << ", " << particle.geometry.acceleration[1] << ", " << particle.geometry.acceleration[2] << "]," << std::endl
			<< std::endl
			<< "\tgravity : " << (particle.useGravity ? "true" : "false") << "," << std::endl
			<< std::endl
			<< "\tlifetime : " << particle.lifeTime << "," << std::endl
			<< std::endl
			<< "\tshader : \"" << particle.shaderName << "\"," << std::endl
			<< std::endl
			<< "\ttexture : \"" << particle.texturePath << "\"," << std::endl
			<< std::endl
			<< "\tdefaultState : {" << std::endl
			<< "\t\tcolour : [" << particle.defaultState->red << ", " << particle.defaultState->green << ", " << particle.defaultState->blue << ", " << particle.defaultState->alpha << "]," << std::endl
			<< "\t\tlight : " << particle.defaultState->lightIntensity << "," << std::endl
			<< "\t\tscale : " << particle.defaultState->scale << "," << std::endl
			<< "\t}," << std::endl
			<< "\ttransState : {" << std::endl
			<< "\t\tcolour : [" << particle.transState->red << ", " << particle.transState->green << ", " << particle.transState->blue << ", " << particle.transState->alpha << "]," << std::endl
			<< "\t\tlight : " << particle.transState->lightIntensity << "," << std::endl
			<< "\t\tscale : " << particle.transState->scale << "," << std::endl
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
