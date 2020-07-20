#pragma once

#include "Core.h"
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
	public:
		Application();
		virtual ~Application();

		void run();

		void on_event(Event& event);
	private:
		bool on_window_close(WindowCloseEvent& event);
	};

	// to be defined in client
	Application* create_application();
	
}
