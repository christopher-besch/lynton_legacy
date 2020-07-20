#include "lypch.h"

#include "Application.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Log.h"

namespace Lynton
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		LY_TRACE(e);
		
		while (true);
	}
}
