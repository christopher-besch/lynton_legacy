#pragma once

#include "Lynton/Events/Event.h"
#include "Lynton/Core/Input.h"

namespace Lynton
{
	class  KeyEvent : public Event
	{
	protected:
		KeyCode m_key_code;
	public:
		inline KeyCode get_key_code() const { return m_key_code; }

		EVENT_CLASS_CATEGORY(event_category_keyboard | event_category_input)
	protected:
		KeyEvent(KeyCode key)
			: m_key_code(key) {}
	};

	
	class  KeyPressedEvent : public KeyEvent
	{
	private:
		int m_repeat_count;
	public:
		KeyPressedEvent(KeyCode key, int repeat_count)
			: KeyEvent(key), m_repeat_count(repeat_count) {}

		inline int get_repeat_count() const { return m_repeat_count; }

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "KeyPressedEvent: " << " (" << m_repeat_count << " repeats)";
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(key_pressed)
	};


	class  KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode key)
			: KeyEvent(key) {}

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "KeyReleasedEvent: " << m_key_code;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(key_released);
	};


	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode key)
			: KeyEvent(key) {}

		std::string to_string() const override
		{
			std::stringstream s_stream;
			s_stream << "KeyTypedEvent: " << m_key_code;
			return s_stream.str();
		}

		EVENT_CLASS_TYPE(key_typed)
	};
	
}
