// for use in Lynton client application

#pragma once

#include "Lynton/Application.h"

/////////////////
// entry point //
/////////////////

#ifdef LY_PLATFORM_WINDOWS
extern Lynton::Application* Lynton::create_application();

int main(int argc, char** argv)
{
	auto app = Lynton::create_application();
	app->run();
	delete app;
}
#endif
