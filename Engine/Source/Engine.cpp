#include "Engine.h"
#include "Core/Logger/Logger.h"
#include "Core/MemoryManager.h"
#include "Core/Window/Window.h"
#include "Core/Renderers/Renderer.h"
#include <exception>
#include <stdio.h>

void *operator new(size_t size)
{
	return ThaumaEngine::MemoryManager::Allocate(size);
}

void operator delete(void *ptr, size_t size)
{
	ThaumaEngine::MemoryManager::Free(ptr, size);
}


ThaumaEngine::Engine* ThaumaEngine::Engine::GetInstance()
{
	if (gEngine == nullptr)
	{
		gEngine = new Engine();
	}
	return gEngine;
}

int ThaumaEngine::Engine::Init()
{
	return Init(new Window("Thauma Engine Window", 800, 600));
}

int ThaumaEngine::Engine::Init(Window *starterWindow)
{
	m_window = starterWindow;
	m_renderer = new Renderer();
	m_renderer->InitRenderer(RendererType::Vulkan, m_window);
	LOG_TRACE("Engine Init\n");
	ThaumaEngine::MemoryManager::LogAllocations();
	return 0;
}

int ThaumaEngine::Engine::Run()
{
	while (!m_window->ShouldClose())
	{
		m_window->Update();
	}return 0;
}

int ThaumaEngine::Engine::Terminate()
{
	delete m_window;
	delete gEngine;
	ThaumaEngine::MemoryManager::LogAllocations();
	return 0;
}


