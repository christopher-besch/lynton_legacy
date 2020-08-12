#pragma once

#include "Lynton/Core/Core.h"

namespace Lynton
{

	class  Input
	{
	private:
		static Scope<Input> s_instance;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool is_key_pressed(int keycode) { return s_instance->is_key_pressed_impl(keycode); }

		inline static bool is_mouse_button_pressed(int button) { return s_instance->is_mouse_button_pressed_impl(button); }
		inline static bool get_mouse_x() { return s_instance->get_mouse_x_impl(); }
		inline static std::pair<float, float> get_mouse_position() { return s_instance->get_mouse_position_impl(); }
	protected:
		Input() = default;

		virtual bool is_key_pressed_impl(int keycode) = 0;

		virtual bool is_mouse_button_pressed_impl(int button) = 0;
		virtual float get_mouse_x_impl() = 0;
		virtual float get_mouse_y_impl() = 0;
		virtual std::pair<float, float> get_mouse_position_impl() = 0;
	};

}
