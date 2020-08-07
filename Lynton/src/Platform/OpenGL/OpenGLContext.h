#pragma once

#include "Lynton/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lynton
{

	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_window_handle;
	public:
		OpenGLContext(GLFWwindow* window_handle);

		virtual void init() override;
		virtual void swap_buffers() override;
	};

}
