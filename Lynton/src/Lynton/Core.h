#pragma once

#ifdef LY_PLATFORM_WINDOWS
	#ifdef LY_BUILD_DLL
		#define LYNTON_API __declspec(dllexport)
	#else
		#define LYNTON_API __declspec(dllimport)
	#endif
#else
	#error The used platform is not supported!
#endif

#ifdef LY_ENABLE_ASSERTS
	#define LY_ASSERT(x, ...) { if(!x) { LY_ERROR("Assertioin Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LY_CORE_ASSERT(x, ...) { if(!x) { LY_CORE_ERROR("Assertioin Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LY_ASSERT(x, ...)
	#define LY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
