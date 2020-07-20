#include "lypch.h"

#include "Application.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Log.h"

#include <GLFW/glfw3.h>

namespace Lynton
{
	Application::Application()
	{
		// create window handler
		m_window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->on_update();
		}
	}
}
