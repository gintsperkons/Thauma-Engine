#include <stdio.h>
#include <iostream>
#include <Core/Window/WindowManager.h>

int main()
{
    WindowManager *windowManager = WindowManager::GetInstance();
    //create a window
    windowManager->CreateWindow("mainWindow", "Test Window",1080,720);
    windowManager->CreateWindow("testWindow", "Test Window2", 1080, 720);
    //main loop
    while (!windowManager->ShouldStop())
    {
        windowManager->ProcessInput();

        windowManager->PollEvents();
    }
    //rm window
    WindowManager::DestroyInstance();
    return 0;
}