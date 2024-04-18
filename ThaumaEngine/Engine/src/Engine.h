#include "define.h"

class Window;
class ThaumaEngine
{
	static ThaumaEngine *instance;
	Window *window;
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
