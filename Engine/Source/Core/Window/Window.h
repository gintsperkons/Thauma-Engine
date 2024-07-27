#pragma once
#include "Defines.h"

struct GLFWwindow;
namespace ThaumaEngine
{

	class Window
	{
		GLFWwindow *m_window;
		bool isResized = false;
		static void FrameBufferResizeCallback(GLFWwindow *window, int width, int height);

	public:
		void Resized()
		{
			isResized = true;
		}
		bool IsResized() const
		{
			return isResized;
		}
		void ResetResize()
		{
			isResized = false;
		}
		TAPI Window(const char *title = "PlaceHolder", int width = 800, int height = 600);
		TAPI bool ShouldClose();
		TAPI void Update();
		TAPI GLFWwindow *GetWindow()
		{
			return m_window;
		};
		TAPI ~Window();
	};
}