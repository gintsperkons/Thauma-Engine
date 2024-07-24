#include <Engine.h>


int main(int argc, char* argv[])
{
	ThaumaEngine::Engine* engine = ThaumaEngine::Engine::GetInstance();
	engine->Init();
	engine->Run();
	engine->Terminate();
	return 0;
}