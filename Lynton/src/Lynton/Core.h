#pragma once

#include <memory>

#ifdef LY_PLATFORM_WINDOWS
	
#else
	#error The used platform is not supported!
#endif

#ifdef LY_DEBUG
    #define LY_ENABLE_ASSERTS
#endif

#ifdef LY_ENABLE_ASSERTS
	#define LY_ASSERT(x, ...) { if(!x) { LY_ERROR("Assertioin Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LY_CORE_ASSERT(x, ...) { if(!x) { LY_CORE_ERROR("Assertioin Failed: {0}", __VA_ARGS__); __debugbreak(); } }
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

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
