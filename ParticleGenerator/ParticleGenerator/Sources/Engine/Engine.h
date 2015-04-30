#pragma once

class Renderer;
class Parser;
class BaseParticle;
class BaseEmitter;
class Shader;

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

private:
	Renderer* _renderer;
	Parser* _parser;

	std::list<BaseParticle*>* _particles;
	std::list<Shader*>* _shaders;
	std::list<BaseEmitter*>* _emitters;

	std::string _defaultFragShader();
	std::string _defaultVertShader();

	void _processParticle(BaseParticle *particle);
	void _processEmitter(BaseEmitter *emitter);
	void _createProgramForShader(Shader *shader);
};

