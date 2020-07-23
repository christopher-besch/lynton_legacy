#pragma once

#include "Lynton/Layer.h"
#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Events/KeyEvent.h"
#include "Lynton/Events/MouseEvent.h"

namespace Lynton
{

	class LYNTON_API ImGuiLayer : public Layer
	{
	private:
		float m_time = 0;
	private:
		bool on_mouse_button_pressed_event(MouseButtonPressedEvent& event);
		bool on_mouse_button_released_event(MouseButtonReleasedEvent& event);
		bool on_mouse_moved_event(MouseMovedEvent& event);
		bool on_mouse_scrolled_event(MouseScrolledEvent& event);
		
		bool on_key_pressed(KeyPressedEvent& event);
		bool on_released_pressed(KeyReleasedEvent& event);
		bool on_key_typed_event(KeyTypedEvent& event);

		bool on_window_resized_event(WindowResizedEvent& event);
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void on_attach() override;
		void on_detach() override;

		virtual void on_update() override;
		virtual void on_event(Event& event) override;
	};

}
