#include "lypch.h"

#include "Application.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Log.h"

#include <GLFW/glfw3.h>

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Lynton
{
	Application::Application()
	{
		// create window handler
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(BIND_EVENT_FUNCTION(on_event));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.9, 0.2, 0.9, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->on_update();
		}
	}

	void Application::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);
		// when the event is a WindowCloseEvent -> call on_window_close
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(on_window_close));

	    LY_CORE_TRACE("{0}", event);
	}

	bool Application::on_window_close(WindowCloseEvent& event)
    {
		m_running = false;
		return true;
    }

}
