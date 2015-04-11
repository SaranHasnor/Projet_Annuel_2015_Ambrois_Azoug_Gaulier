#include "engine_wrapper.h"
#include "Engine.h"

static Engine* _staticEngine;

extern "C" void initEngine()
{
	_staticEngine = new Engine();
}

extern "C" void runEngine()
{
	_staticEngine->run();
}