#include <stdio.h>
#include <iostream>
#include <Core/Window/WindowManager.h>

int main()
{
    WindowManager *windowManager = WindowManager::GetInstance();
    //create a window
    windowManager->CreateWindow("mainWindow", "Test Window",1080,720);
    //main loop
    std::cin.get();
    //rm window
    WindowManager::DestroyInstance();
    return 0;
}