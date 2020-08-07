// events are blocking -> they get dealt with immediately and block anything else

#pragma once

#include "lypch.h"

#include "Lynton/Core.h"

namespace Lynton
{

	// every event type belongs to at least one category
    enum class EventType
	{
		none = 0,

		window_close,
		window_resize,
		window_focus,
		window_lost_focus,
		window_moved,
		
		app_tick,
		app_update,
		app_render,
		
		key_pressed,
		key_released,
		key_typed,
		
		mouse_button_pressed,
		mouse_button_released,
		mouse_moved,
		mouse_scrolled
	};

	enum EventCategory
	{
		none = 0,
		event_category_application  = BIT(0),
		event_category_input        = BIT(1),
		event_category_keyboard     = BIT(2),
		event_category_mouse        = BIT(3),
		event_category_mouse_button = BIT(4)
	};

// select the type <- a couple of methods definitions to retrieve the type
#define EVENT_CLASS_TYPE(type) static EventType get_static_type() { return EventType::##type; }\
							   virtual EventType get_event_type() const override { return get_static_type(); }\
							   virtual const char* get_name() const override { return #type; }
// select the category <- a couple of methods definitions to retrieve the category
#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

	
	// interface for events
	class  Event
	{
		friend class EventDispatcher;
	public:
		// when true this event doesn't need to be cared for anymore
		bool m_handled = false;
	public:
		virtual EventType get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string to_string() const { return get_name(); }

		inline bool is_in_category(EventCategory category) { return get_category_flags() & category; }
	};


	// used in on_event in each layer:
	// EventDispatcher dispatcher(event);
	//                                      <- lambda or function pointer, which gets executed when event is KeyPressedEvent
	// dispatcher.dispatch<KeyPressedEvent>([](ExampleLayer::on_key_pressed_event event) {});
	class EventDispatcher
	{
	private:
		template<typename T>
		using event_function = std::function<bool(T&)>;
		Event& m_event;
	public:
		EventDispatcher(Event& event)
			: m_event(event) {}

		template<typename T>
		bool dispatch(event_function<T> func)
		{
			if (m_event.get_event_type() == T::get_static_type())
			{
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.to_string();
	}
	
}
