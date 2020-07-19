#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Lynton
{

	class LYNTON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// to be defined in client
	Application* create_application();
	
}
