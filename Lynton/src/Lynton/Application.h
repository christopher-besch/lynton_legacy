#pragma once

#include "Core.h"
#include "Events/Event.h"
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
	};

	// to be defined in client
	Application* create_application();
	
}
