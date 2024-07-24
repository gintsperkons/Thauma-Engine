#include "Defines.h"


namespace ThaumaEngine{
	class Window;
	class Engine
	{
		Window* m_window;
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
