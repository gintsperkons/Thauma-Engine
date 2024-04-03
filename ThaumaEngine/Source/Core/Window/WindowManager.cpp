
#include "Window.h"

#include "WindowManager.h"


WindowManager *instance = nullptr;

WindowManager* WindowManager::GetInstance()
{
	if (instance == nullptr)
		instance = new WindowManager();
	return instance;
}

void WindowManager::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
	for (auto window : windowMap)
	{
		delete window.second;
	}
}

Window* WindowManager::CreateWindow(std::string idName, std::string windowTitle, int width, int height)
{
	Window* window = new Window(windowTitle, width, height);
	
	windowMap[idName] = window;
	return window;
}
