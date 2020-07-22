#pragma once

#include "Event.h"

namespace Lynton
{
	class LYNTON_API KeyEvent : public Event
	{
	protected:
		int m_key_code;
	public:
		inline int get_key_code() const { return m_key_code; }

		EVENT_CLASS_CATEGORY(event_category_keyboard | event_category_input)
	protected:
		KeyEvent(int keycode)
			: m_key_code(keycode) {}
	};

	
	class LYNTON_API KeyPressedEvent : public KeyEvent
	{
	private:
		int m_repeat_count;
	public:
		KeyPressedEvent(int keycode, int repeat_count)
			: KeyEvent(keycode), m_repeat_count(repeat_count) {}

		inline int get_repeat_count() const { return m_repeat_count; }

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "KeyPressedEvent: " << " (" << m_repeat_count << " repeats)";
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(key_pressed)
	};


	class LYNTON_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "KeyReleasedEvent: " << m_key_code;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(key_released);
	};


	class LYNTON_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "KeyTypedEvent: " << m_key_code;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(key_typed)
	};
	
}
