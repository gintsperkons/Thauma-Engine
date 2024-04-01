#include "WindowManager.h"

WindowManager *instance = nullptr;

WindowManager* WindowManager::GetInstance()
{
	if (instance == nullptr)
		instance = new WindowManager();
	return instance;
}

WindowManager::WindowManager()
{}

WindowManager::~WindowManager()
{
	delete instance;
	instance = nullptr;
}

b8 WindowManager::Init()
{
	if (true)
	{
				return true;
	}
	return false;
}
