#pragma once

class Renderer;
class Parser;
class BaseParticle;
class Shader;

#include <list>

class Engine
{
public:
	Engine(void);
	~Engine(void);

	void run();

private:
	Renderer* _renderer;
	Parser* _parser;

	std::list<BaseParticle*>* _particles;
	std::list<Shader*>* _shaders;

	std::string _defaultFragShader();
	std::string _defaultVertShader();
};
