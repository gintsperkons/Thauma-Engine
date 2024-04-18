#include "Renderer.h"
#include "Renderers/Vulkan/VulkanRenderer.h"
#include "Renderers/OpenGL/OpenGLRenderer.h"

void Renderer::Init(int renderType,GLFWwindow* window)
{
	if (currentRendererID != 0)
	{
		return;
	}

	switch (renderType)
	{
	case Type::Vulkan:
		currentRenderer = new VulkanRenderer();
		currentRenderer->Init(window);
		currentRendererID = Type::Vulkan;
		break;
	case Type::OpenGL:
		currentRenderer = new OpenGLRenderer();
		currentRenderer->Init(window);
		currentRendererID = Type::OpenGL;
		break;
	default:
		break;
	}
}

void Renderer::Destroy()
{
	currentRenderer->Destroy();
}

Renderer::~Renderer()
{
	Destroy();
}