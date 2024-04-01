#pragma once
#include "define.h"

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	TAPI b8 Init();

	TAPI static WindowManager* GetInstance();
};

