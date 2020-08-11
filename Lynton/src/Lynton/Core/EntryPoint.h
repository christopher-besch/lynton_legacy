#pragma once

#ifdef LY_PLATFORM_WINDOWS

extern Lynton::Application* Lynton::create_application();

int main(int argc, char** argv)
{
	Lynton::Log::init();
	LY_CORE_INFO("Initialized Log!");

	auto app = Lynton::create_application();
	app->run();
	delete app;
}

#endif
