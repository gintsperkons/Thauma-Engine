#include <stdio.h>
#include <Core/Window/WindowManager.h>

int main()
{
    printf("Hello World\n");
    WindowManager* windowManager = WindowManager::GetInstance();
    printf("Window Manager Initialized: %d\n", windowManager->Init());
    return 0;
}