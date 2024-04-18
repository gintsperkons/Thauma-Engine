#include "Define.h"

struct GLFWwindow;

class Window
{
	GLFWwindow* window;
	
public:
	TAPI Window();

	TAPI void Init(const char *title = "Thauma Engine Window", int width = 800, int height = 600);

	TAPI ~Window();
};