#include "Core/memoryManagment.h"
#include "Core/logger.h"
#include "Engine.h"
#include "Core/Window/Window.h"
#include "Core/Renderer.h"
#include <malloc.h>
#include <stdio.h>

void * operator new(size_t size)
{
	return MemoryManager::Allocate(size);
}

void operator delete(void* ptr, size_t size)
{
	MemoryManager::Free(ptr, size);
}

ThaumaEngine * ThaumaEngine::instance = nullptr;


ThaumaEngine* ThaumaEngine::GetInstance()
{
	if (ThaumaEngine::instance == nullptr)
		ThaumaEngine::instance = new ThaumaEngine();
	return ThaumaEngine::instance;
}

int ThaumaEngine::Init()
{
	window = new Window();
	window->Init();
	renderer = new Renderer();
	renderer->Init(Renderer::Type::Vulkan,window->GetWindow());
	//create triangle
	return 0;
}

int ThaumaEngine::Run()
{
	while (!window->ShouldClose())
	{

		window->Update();
		renderer->Update();
		renderer->StartRendering();
		// //draw triangle
		//render finish
		
		renderer->Draw();
		renderer->FinishRendering();
		MemoryManager::LogAllocations();
	}
	
	return 0;
}

int ThaumaEngine::Terminate()
{
	//destroy triangle
	renderer->Complete();
	delete renderer;
	delete window;
	delete ThaumaEngine::instance;
	return 0;
}
