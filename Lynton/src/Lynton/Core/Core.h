#pragma once

#include <memory>

// platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
    #ifdef _WIN64
	/* Windows x64  */
        #define LY_PLATFORM_WINDOWS
    #else
	    /* Windows x86 */
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so all of them must be checked(in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
	    #error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
	    #define LY_PLATFORM_IOS
	    #error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
	    #define LY_PLATFORM_MACOS
	    #error "MacOS is not supported!"
	#else
	    #error "Unknown Apple platform!"
	    #endif
/* __ANDROID__ also hath to be checked before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define LY_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define LY_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* unknown compiler/platform */
#error "Unknown platform!"
#endif


#ifdef LY_DEBUG
	#define LY_ENABLE_ASSERTS
	#define LY_PROFILE 1
#endif

#ifdef LY_DEBUG
    #if defined(LY_PLATFORM_WINDOWS)
        #define LY_DEBUGBREAK() __debugbreak()
    #elif defined(LY_PLATFORM_LINUX)
        #include <signal.h>
        #define LY_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define LY_ENABLE_ASSERTS
#else
    #define LY_DEBUGBREAK()
#endif


#ifdef LY_ENABLE_ASSERTS
	#define LY_ASSERT(x, ...) { if(!x) { LY_ERROR("Assertion Failed: {0}", __VA_ARGS__); LY_DEBUGBREAK(); } }
	#define LY_CORE_ASSERT(x, ...) { if(!(x)) { LY_CORE_ERROR("Core Assertion Failed: {0}", __VA_ARGS__); LY_DEBUGBREAK(); } }
#else
	#define LY_ASSERT(x, ...)
	#define LY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LY_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)

namespace Lynton
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> create_scope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> create_ref(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
