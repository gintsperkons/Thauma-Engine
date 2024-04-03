#pragma once
#include <GLFW/glfw3.h>


class Renderer
{
public:
	virtual int Init(GLFWwindow* window) = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;


	Renderer() {};
	~Renderer() {};

	enum RenderType
	{
		None,
		Vulkan,
		OpenGL
	};
};
