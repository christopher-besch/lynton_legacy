#include "lypch.h"

#include "Application.h"
#include "Core.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Core/Log.h"

#include "Lynton/Renderer/Renderer.h"

#include "Input.h"
#include "GLFW/glfw3.h"

namespace Lynton
{

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		LY_CORE_ASSERT(!s_instance, "Application already exists!")
		s_instance = this;

		// create window handler
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(LY_BIND_EVENT_FUNCTION(Application::on_event));

		Renderer::init();

		// ImGui
		m_imgui_layer = new ImGuiLayer();
		push_overlay(m_imgui_layer);
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
		m_layer_stack.push_overlay(layer);
		layer->on_attach();
    }

	void Application::run()
	{
		while (m_running)
		{
			// ToDo: temporary
			float time = (float)glfwGetTime();
			TimeStep time_step = time - m_last_frame_time;
			m_last_frame_time = time;

			if (!m_minimized)
			{
		        for (Layer* layer : m_layer_stack)
				    layer->on_update(time_step);
			}

			m_imgui_layer->begin();
			for (Layer* layer : m_layer_stack)
				layer->on_imgui_render();
			m_imgui_layer->end();

			m_window->on_update();
		}
	}

	void Application::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);
		// when the event is a WindowCloseEvent -> call on_window_close
		dispatcher.dispatch<WindowCloseEvent>(LY_BIND_EVENT_FUNCTION(Application::on_window_close));
		dispatcher.dispatch<WindowResizedEvent>(LY_BIND_EVENT_FUNCTION(Application::on_window_resize));

		// ToDo: put break into loop instead of if?
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

	bool Application::on_window_resize(WindowResizedEvent& event)
	{
		m_minimized = event.get_width() == 0 || event.get_height() == 0;

		Renderer::on_window_resize(event.get_width(), event.get_height());

		return false;
	}

}
