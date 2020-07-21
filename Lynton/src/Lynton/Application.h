#pragma once

#include "Core.h"
#include "Lynton/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Lynton
{

	class LYNTON_API Application
	{
	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layer_stack;
	public:
		Application();
		virtual ~Application();

		void run();

		void on_event(Event& event);

		void push_layer(Layer* layer);
		void push_overlay(Layer* layer);
	private:
		bool on_window_close(WindowCloseEvent& event);
	};

	// to be defined in client
	Application* create_application();
	
}
