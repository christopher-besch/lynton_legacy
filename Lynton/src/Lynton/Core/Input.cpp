#include "lypch.h"
#include "Lynton/Core/Input.h"

#ifdef LY_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Lynton
{

	Scope<Input> Input::s_instance = Input::create();

	Scope<Input> Input::create()
	{
#ifdef LY_PLATFORM_WINDOWS
		return create_scope<WindowsInput>();
#else
		LY_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}
