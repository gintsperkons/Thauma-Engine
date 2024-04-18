#include "define.h"

class Window;
class Renderer;
class ThaumaEngine
{
	static ThaumaEngine *instance;
	Window *window;
	Renderer* renderer;
public:
	TAPI static ThaumaEngine* GetInstance();
	TAPI int Init();
	TAPI int Run();
	TAPI int Terminate();

	

private:
	ThaumaEngine()
	{}
	~ThaumaEngine()
	{}
};
