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
	void render();						// Render function, should be called from an OpenGL rendering context

	BaseParticle* particleNamed(std::string name);
	Shader* Engine::shaderNamed(std::string name);
	ParticleEmitter* emitterWithID(int emitterID);

	int	particleCount;

private:
	Renderer* _renderer;
	Parser* _parser;

	std::list<ParticleEmitter*>* _emitters;
	std::list<BaseParticle*>* _particles;
	std::list<Shader*>* _shaders;

	std::string _defaultFragShader();
	std::string _defaultVertShader();

	void _processParticle(BaseParticle *particle);
	void _linkParticle(BaseParticle *particle);
	void _createProgramForShader(Shader *shader);
};

