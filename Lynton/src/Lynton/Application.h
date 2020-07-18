#pragma once

#include "Core.h"

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
