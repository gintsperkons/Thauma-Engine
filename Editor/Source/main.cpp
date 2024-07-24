#include <Engine.h>
#include <Core/Window/Window.h>

int main(int argc, char* argv[])
{
	ThaumaEngine::Engine* engine = ThaumaEngine::Engine::GetInstance();
	engine->Init(new ThaumaEngine::Window("Thauma Engine",800,600));
	engine->Run();
	engine->Terminate();
	return 0;
}