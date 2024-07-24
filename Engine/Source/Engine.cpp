#include "Engine.h"
#include <exception>
#include <stdio.h>

ThaumaEngine::Engine* ThaumaEngine::Engine::instance = nullptr;
ThaumaEngine::Engine* ThaumaEngine::Engine::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Engine();
	}
	return instance;
}

int ThaumaEngine::Engine::Init()
{
	return 0;
}

int ThaumaEngine::Engine::Run()
{
	return 0;
}

int ThaumaEngine::Engine::Terminate()
{
	return 0;
}


ThaumaEngine::Engine::Engine()
{
}

ThaumaEngine::Engine::~Engine()
{
}