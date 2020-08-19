#pragma once
#include "Lynton/Core/Core.h"

#ifdef LY_PLATFORM_WINDOWS

extern Lynton::Application* Lynton::create_application();

int main(int argc, char** argv)
{
	Lynton::Log::init();

	LY_PROFILE_BEGIN_SESSION("Startup", "LyntonProfile-Startup.json");
	auto app = Lynton::create_application();
	LY_PROFILE_END_SESSION();

	LY_PROFILE_BEGIN_SESSION("Runtime", "LyntonProfile-Runtime.json");
	app->run();
	LY_PROFILE_END_SESSION();

	LY_PROFILE_BEGIN_SESSION("Shutdown", "LyntonProfile-Shutdown.json");
	delete app;
	LY_PROFILE_END_SESSION();
}

#endif
