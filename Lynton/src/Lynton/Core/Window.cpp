#include "lypch.h"
#include "Lynton/Core/Window.h"

#ifdef LY_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Lynton
{

	Scope<Window> Window::create(const WindowProperties& props)
	{
#ifdef LY_PLATFORM_WINDOWS
		return create_scope<WindowsWindow>(props);
#else
		LY_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}
