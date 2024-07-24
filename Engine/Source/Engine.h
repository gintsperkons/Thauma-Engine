#include "Defines.h"


namespace ThaumaEngine{
	class Engine
	{
	public:
		static Engine* instance;
		TAPI static Engine* GetInstance();
		TAPI int Init();
		TAPI int Run();
		TAPI int Terminate();



	private:
		Engine();
		~Engine();
	};
}
