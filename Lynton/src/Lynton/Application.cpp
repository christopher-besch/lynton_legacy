#include "lypch.h"

#include "Application.h"
#include "Core.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Log.h"

#include <Glad/glad.h>

namespace Lynton
{

	// make Application a singleton
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		LY_CORE_ASSERT(!s_instance, "Application already exists!")
		s_instance = this;

		// create window handler
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(LY_BIND_EVENT_FUNCTION(Application::on_event));
	}

	Application::~Application()
	{
	}

	void Application::push_layer(Layer* layer)
    {
		m_layer_stack.push_layer(layer);
		layer->on_attach();
    }

	void Application::push_overlay(Layer* layer)
    {
		m_layer_stack.push_overerlay(layer);
		layer->on_attach();
    }



	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.9, 0.2, 0.9, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layer_stack)
				layer->on_update();

			m_window->on_update();
		}
	}

	void Application::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);
		// when the event is a WindowCloseEvent -> call on_window_close
		dispatcher.dispatch<WindowCloseEvent>(LY_BIND_EVENT_FUNCTION(Application::on_window_close));

	    LY_CORE_TRACE("{0}", event);

		// sending the event through every layer until one handles it -> overlays get events first
		for ( auto iterator = m_layer_stack.end(); iterator != m_layer_stack.begin(); )
		{
			(*--iterator)->on_event(event);
			if (event.m_handled)
				break;
		}
	}

	bool Application::on_window_close(WindowCloseEvent& event)
    {
		m_running = false;
		return true;
    }

}
