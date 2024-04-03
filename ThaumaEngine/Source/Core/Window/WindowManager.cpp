
#include "Window.h"

#include <GLFW/glfw3.h>
#include <vector>
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
	glfwTerminate();
}

Window* WindowManager::CreateWindow(std::string idName, std::string windowTitle, int width, int height)
{
	Window* window = new Window(windowTitle, width, height);
	
	windowMap[idName] = window;
	return window;
}

b8 WindowManager::ShouldStop()
{
	if (windowMap.empty())
	{
		return true;
	}
	else
	{
		b8 shouldClose = true;
		std::vector<std::string> windowsToClose;
		
		for (auto window : windowMap)
		{
			if (window.second->ShouldClose())
			{
				windowsToClose.push_back(window.first);
				delete window.second;
			}
			else
			{
				shouldClose = false;
			}

		}
		for (std::string window : windowsToClose)
		{
			windowMap.erase(window);
		}
		return shouldClose;
	}
}

void WindowManager::ProcessInput()
{
	for (auto window : windowMap)
	{
		window.second->ProcessInput();
	}
}

void WindowManager::PollEvents()
{
	for (auto window : windowMap)
	{
		window.second->PollEvents();
	}
}
