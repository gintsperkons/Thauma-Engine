#pragma once
#include "define.h"
#include <string>
#include <unordered_map>

class Window;

class WindowManager
{
	std::unordered_map<std::string, Window *> windowMap;

	WindowManager();
	~WindowManager();
public:

	TAPI Window* CreateWindow(std::string idName, std::string windowTitle = "Thauma Engine Window Title",int width = 800, int height = 600);

	TAPI b8 ShouldStop();
	TAPI void ProcessInput();
	TAPI void PollEvents();


	TAPI static WindowManager* GetInstance();
	TAPI static void DestroyInstance();
};

