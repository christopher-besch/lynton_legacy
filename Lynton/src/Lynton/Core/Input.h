#pragma once

#include "Lynton/Core/Core.h"
#include "Lynton/Core/KeyCodes.h"
#include "Lynton/Core/MouseCodes.h"

namespace Lynton
{

	class  Input
	{
	private:
		static Scope<Input> s_instance;
	public:

		static bool is_key_pressed(KeyCode key);

		static bool is_mouse_button_pressed(MouseCode button);
		static std::pair<float, float> get_mouse_position();
		static float get_mouse_x();
		static float get_mouse_y();
	};

}
