#include "Defines.h"


namespace ThaumaEngine{
	class Window;
	class Renderer;
	class Engine
	{
		Window* m_window;
		Renderer* m_renderer;
	public:
		static Engine* instance;
		TAPI static Engine* GetInstance();
		TAPI int Init();
		TAPI int Init(Window * starterWindow);
		TAPI int Run();
		TAPI int Terminate();



	private:
	};
}
