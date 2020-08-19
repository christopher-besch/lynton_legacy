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
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool is_key_pressed(KeyCode key) { return s_instance->is_key_pressed_impl(key); }

		inline static bool is_mouse_button_pressed(MouseCode button) { return s_instance->is_mouse_button_pressed_impl(button); }
		inline static bool get_mouse_x() { return s_instance->get_mouse_x_impl(); }
		inline static std::pair<float, float> get_mouse_position() { return s_instance->get_mouse_position_impl(); }
	protected:
		Input() = default;

		virtual bool is_key_pressed_impl(KeyCode key) = 0;

		virtual bool is_mouse_button_pressed_impl(MouseCode button) = 0;
		virtual float get_mouse_x_impl() = 0;
		virtual float get_mouse_y_impl() = 0;
		virtual std::pair<float, float> get_mouse_position_impl() = 0;
	};

}
