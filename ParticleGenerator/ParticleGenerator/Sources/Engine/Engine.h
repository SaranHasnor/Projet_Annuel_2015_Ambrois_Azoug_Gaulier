#pragma once

class Renderer;
class Parser;
class BaseParticle;

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
};

