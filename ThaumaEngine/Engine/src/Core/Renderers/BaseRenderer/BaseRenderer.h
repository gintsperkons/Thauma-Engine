#pragma once
#include <GLFW/glfw3.h>


class BaseRenderer
{
public:
	virtual int Init(GLFWwindow* window) = 0;
	virtual void StartRendering() = 0;
	virtual void FinishRendering() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
	virtual void Complete() = 0;


	BaseRenderer() {};
	~BaseRenderer() {};

};
