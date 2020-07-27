#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

#include "Core.h"

namespace Lynton
{
	
	class  Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_core_logger()
		{
			return s_core_logger;
		}

		inline static std::shared_ptr<spdlog::logger>& get_client_logger()
		{
			return s_client_logger;
		}
	};

}

// core log macros
#define LY_CORE_TRACE(...) ::Lynton::Log::get_core_logger()->trace(__VA_ARGS__)
#define LY_CORE_INFO(...)  ::Lynton::Log::get_core_logger()->info(__VA_ARGS__)
#define LY_CORE_WARN(...)  ::Lynton::Log::get_core_logger()->warn(__VA_ARGS__)
#define LY_CORE_ERROR(...) ::Lynton::Log::get_core_logger()->error(__VA_ARGS__)
#define LY_CORE_FATAL(...) ::Lynton::Log::get_core_logger()->fatal(__VA_ARGS__)

// client log macros
#define LY_TRACE(...)      ::Lynton::Log::get_client_logger()->trace(__VA_ARGS__)
#define LY_INFO(...)       ::Lynton::Log::get_client_logger()->info(__VA_ARGS__)
#define LY_WARN(...)       ::Lynton::Log::get_client_logger()->warn(__VA_ARGS__)
#define LY_ERROR(...)      ::Lynton::Log::get_client_logger()->error(__VA_ARGS__)
#define LY_FATAL(...)      ::Lynton::Log::get_client_logger()->fatal(__VA_ARGS__)
