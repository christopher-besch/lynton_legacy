#pragma once

#include "Event.h"

namespace Lynton
{
	
	class LYNTON_API MouseMovedEvent : public Event
	{
	private:
		float m_mouse_x, m_mouse_y;
	public:
		MouseMovedEvent(float x, float y)
			: m_mouse_x(x), m_mouse_y(y) {}

		inline float get_x() const { return m_mouse_x; }
		inline float get_y() const { return m_mouse_y; }

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "MouseMovedEvent: " << m_mouse_x << ", " << m_mouse_y;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(mouse_moved)
		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	};


	class LYNTON_API MouseScrolledEvent : public Event
	{
	private:
		float m_mouse_offset_x, m_mouse_offset_y;
	public:
		MouseScrolledEvent(float x, float y)
			: m_mouse_offset_x(x), m_mouse_offset_y(y) {}

		inline float get_x() const { return m_mouse_offset_x; }
		inline float get_y() const { return m_mouse_offset_y; }

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "MouseScrolledEvent: " << m_mouse_offset_x << ", " << m_mouse_offset_y;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(mouse_scrolled)
		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	};


	class LYNTON_API MouseButtonEvent : public Event
	{
	protected:
		int m_button;
	public:
		inline float get_mouse_button() const { return m_button; }

		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}
	};


	class LYNTON_API MouseButtonPressed : public MouseButtonEvent
	{
	public:
		MouseButtonPressed(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "MouseButtonPressed: " << m_button;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(mouse_button_pressed)
		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	};


	class LYNTON_API MouseButtonReleased : public MouseButtonEvent
	{
	public:
		MouseButtonReleased(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "MouseButtonReleased: " << m_button;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(mouse_button_released)
			EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	};
	
}
