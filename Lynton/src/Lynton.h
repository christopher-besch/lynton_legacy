// for use in Lynton client application

#pragma once

#include "Lynton/Application.h"
#include "Lynton/Log.h"

/////////////////
// entry point //
/////////////////

#ifdef LY_PLATFORM_WINDOWS
extern Lynton::Application* Lynton::create_application();

int main(int argc, char** argv)
{
	Lynton::Log::init();
	LY_CORE_WARN("Initialized Log!");
	int a = 5;
	LY_INFO("Hello! Var={0}", a);
	
	auto app = Lynton::create_application();
	app->run();
	delete app;
}
#endif
