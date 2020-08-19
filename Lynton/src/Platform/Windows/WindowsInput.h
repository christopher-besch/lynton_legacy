#pragma once

#include "Lynton/Core/Input.h"

namespace Lynton
{

	class WindowsInput : public Input
	{
	protected:
	    virtual bool is_key_pressed_impl(KeyCode key) override;

		virtual bool is_mouse_button_pressed_impl(MouseCode button) override;
		virtual float get_mouse_x_impl() override;
		virtual float get_mouse_y_impl() override;
		virtual std::pair<float, float> get_mouse_position_impl() override;
	};

}
