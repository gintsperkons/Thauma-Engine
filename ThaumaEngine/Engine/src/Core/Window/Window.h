#include "Define.h"

struct GLFWwindow;

class Window
{
	GLFWwindow* m_window;
	bool isResized = false;
	static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);
	
public:
	void Resized() {
		isResized = true;
	}
	bool IsResized() { return isResized; }
	void ResetResize() { isResized = false; }
	TAPI Window();
	
	TAPI void Init(const char *title = "Thauma Engine Window", int width = 800, int height = 600);
	TAPI b8 ShouldClose();
	TAPI void Update();
	TAPI GLFWwindow *GetWindow()
	{
		return m_window;
	};
	TAPI ~Window();
};