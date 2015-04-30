#include "Engine.h"

#include "Rendering/Renderer.h"
#include "Parsing/Parser.h"

#include <Data Models/BaseParticle.h>
#include <Data Models/Shader.h>
#include <Data Models/Texture.h>
#include <Data Models/ParticleEmitter.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <fstream>
#include <algorithm>

Engine::Engine(void)
{
	_renderer = new Renderer();
	_parser = new Parser();
	
	_shaders = new std::list<Shader*>();

	Shader *defaultShader = new Shader();

	defaultShader->name = std::string("Default");
	defaultShader->shaderText = _defaultFragShader();

	// First item of the list should always be this one
	_shaders->push_back(defaultShader);
	_createProgramForShader(defaultShader);

	_particles = _parser->parseParticlesInFile(std::string());
	_emitters = new std::list<ParticleEmitter*>();

	std::for_each(_particles->begin(), _particles->end(), [this](BaseParticle *particle){ this->_processParticle(particle); });

	// Demo
	ParticleEmitter *defaultEmitter = new ParticleEmitter();
	defaultEmitter->particleName = _particles->front()->name;
	defaultEmitter->posX = defaultEmitter->posY = defaultEmitter->posZ = 0.0f;
	defaultEmitter->randomFacingDirection = true;
	defaultEmitter->velX = defaultEmitter->velY = 0.0f;
	defaultEmitter->velZ = 10.0f;
	defaultEmitter->lastSpawn = 0;
	defaultEmitter->spawnInterval = 250;
	_emitters->push_back(defaultEmitter);
}


Engine::~Engine(void)
{
}


void Engine::update(float deltaTime)
{
	unsigned int currentTime = (unsigned int)glutGet(GLUT_ELAPSED_TIME);
	std::list<BaseParticle*> deleteList = std::list<BaseParticle*>();

	// Update particles
	for (std::list<BaseParticle*>::const_iterator iterator = _particles->begin(); iterator != _particles->end(); ++iterator)
	{
		BaseParticle *particle = *iterator;

		if (particle->linked)
		{
			if (currentTime < particle->spawnTime + particle->lifeTime)
			{
				particle->posX += particle->velX * deltaTime;
				particle->posY += particle->velY * deltaTime;
				particle->posZ += particle->velZ * deltaTime;
			}
			else
			{
				particle->linked = false;
				deleteList.push_back(particle);
			}
		}
	}

	// Delete particles
	for (std::list<BaseParticle*>::const_iterator iterator = deleteList.begin(); iterator != deleteList.end(); ++iterator)
	{
		BaseParticle *particle = *iterator;
		_particles->remove(particle);
		delete particle;
	}

	// Update emitters
	for (std::list<ParticleEmitter*>::const_iterator iterator = _emitters->begin(); iterator != _emitters->end(); ++iterator)
	{
		ParticleEmitter *emitter = *iterator;

		if (currentTime - emitter->lastSpawn >= emitter->spawnInterval)
		{
			BaseParticle *newParticle = emitter->spawnParticle(*particleNamed(emitter->particleName));
			_linkParticle(newParticle);
			_particles->push_back(newParticle);
			emitter->lastSpawn = currentTime;
		}
	}
}


void Engine::render()
{
	_renderer->renderParticles(_particles);
}


void Engine::_processParticle(BaseParticle *particle)
{
	particle->shader = shaderNamed(particle->shaderName);
	
	particle->texture = new Texture(particle->texturePath);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &particle->texture->textureID);
	glActiveTexture(GL_TEXTURE0 + particle->texture->textureID);
	glBindTexture(GL_TEXTURE_2D, particle->texture->textureID);
	glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			particle->texture->width,
			particle->texture->height,
			0,
			GL_RGBA,
			GL_FLOAT,
			particle->texture->data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Engine::_linkParticle(BaseParticle *particle)
{
	particle->linked = true;
	particle->spawnTime = (unsigned int)glutGet(GLUT_ELAPSED_TIME);
}


BaseParticle* Engine::particleNamed(std::string name)
{
	std::list<BaseParticle*>::iterator particleIterator = std::find_if(_particles->begin(), _particles->end(), [name](BaseParticle* particle){ return particle->name == name; });
	if (particleIterator != _particles->end())
	{
		return *particleIterator;
	}
	return NULL;
}


Shader* Engine::shaderNamed(std::string name)
{
	std::list<Shader*>::iterator shaderIterator = std::find_if(_shaders->begin(), _shaders->end(), [name](Shader* shader){ return shader->name == name; });
	if (shaderIterator != _shaders->end())
	{
		return *shaderIterator;
	}
	return NULL;
}


std::string Engine::_defaultFragShader()
{
	std::ifstream ifs("../ParticleGenerator/Ressources/Shaders/default_fs.glsl");
	if (ifs)
		return std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	else
		return std::string("");
}


std::string Engine::_defaultVertShader()
{
	std::ifstream ifs("../ParticleGenerator/Ressources/Shaders/default_vs.glsl");
	if (ifs)
		return std::string((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
	else
		return std::string("");
}

void printLog(GLuint obj)
{
	int infologLength = 0;
	int maxLength;
  
	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
  
	char *infoLog = new char[maxLength];
  
	if (glIsShader(obj))
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
  
	if (infologLength > 0)
		printf("%s\n",infoLog);
  
	delete infoLog;
}

void Engine::_createProgramForShader(Shader *shader)
{
	std::string shaderText = _defaultVertShader();
	const char *vShaderText = shaderText.c_str();
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderText, NULL);
	glCompileShader(vShader);
	printLog(vShader);

	const char *fShaderText = shader->shaderText.c_str();
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	glCompileShader(fShader);
	printLog(fShader);

	GLuint prog = glCreateProgram();
	glAttachShader(prog, vShader);
	glAttachShader(prog, fShader);
	glLinkProgram(prog);
	printLog(prog);

	shader->program = prog;
}
