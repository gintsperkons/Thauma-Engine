#include <Engine.h>



int main(int argc, char *argv[])
{
	ThaumaEngine::GetInstance()->Init();
	ThaumaEngine::GetInstance()->Run();
	ThaumaEngine::GetInstance()->Terminate();
}