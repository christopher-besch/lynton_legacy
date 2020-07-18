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
