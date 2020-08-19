#include "lypch.h"

#include "Log.h"

namespace Lynton
{

	Ref<spdlog::logger> Log::s_core_logger;
	Ref<spdlog::logger> Log::s_client_logger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_core_logger = spdlog::stdout_color_mt("LYNTON");
		s_core_logger->set_level(spdlog::level::trace);
		
		s_client_logger = spdlog::stdout_color_mt("APP");
		s_client_logger->set_level(spdlog::level::trace);

	}
	
}
