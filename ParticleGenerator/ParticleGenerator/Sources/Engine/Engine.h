#pragma once

class Renderer;
class Parser;
class BaseParticle;
class Shader;
class ParticleEmitter;

#include <list>

class Engine
{
public:
	Engine(void);
	~Engine(void);

	void update(float deltaTime);		// Logic update loop, deltaTime is in seconds
	void render(float viewMatrix[16]);	// Render function, should be called from an OpenGL rendering context

	BaseParticle* particleNamed(std::string name);
	BaseParticle* particleWithID(int particleID);
	Shader* shaderNamed(std::string name);
	Shader* shaderWithID(int shaderID);
	ParticleEmitter* emitterWithID(int emitterID);

	void toggleTransStateInParticleWithID(int particleID);

	int getParticleModelCount();
	int getActiveParticleCount();
	int getEmitterCount();
	int getShaderCount();

	void createEmitter();
	void destroyEmitter(int emitterID);
	void createParticle();
	void destroyParticle(int particleID);
	void createShader();
	void destroyShader(int shaderID);

	void saveSession();
	void loadSession();

private:
	Renderer* _renderer;
	Parser* _parser;

	std::list<ParticleEmitter*>* _emitters;
	std::list<BaseParticle*>* _particleModels;
	std::list<BaseParticle*>* _activeParticles;
	std::list<Shader*>* _shaders;

	int _particleCount;

	unsigned long _currentTime;

	void _processParticle(BaseParticle *particle);
	void _createProgramForShader(Shader *shader);
};

