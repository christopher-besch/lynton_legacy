// for use in Lynton client application

#pragma once

#include "lypch.h"

#include "Lynton/Application.h"

/////////////////
// entry point //
/////////////////

#ifdef LY_PLATFORM_WINDOWS
extern Lynton::Application* Lynton::create_application();

int main(int argc, char** argv)
{
	Lynton::Log::init();
	LY_CORE_WARN("Initialized Log!");
	
	Lynton::Application* app = Lynton::create_application();
	app->run();
	delete app;
}
#endif