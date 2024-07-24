#pragma once
#include "Defines.h"
#include "Base/BaseRenderer.h"
#include "Vulkan/VulkanRenderer.h"



struct GLFWwindow;
namespace ThaumaEngine
{
	typedef enum RendererType
	{
		None = 0,
		Vulkan,
		OpenGL,
		DirectX
	} RendererType;

	class Renderer
	{

		BaseRenderer* m_currentRenderer = nullptr;

	public:
		Renderer();
		void InitRenderer(ThaumaEngine::RendererType type, GLFWwindow* window);
		~Renderer();

	};


}