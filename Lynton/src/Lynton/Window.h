#pragma once

#include "lypch.h"

#include "Lynton/Core.h"
#include "Lynton/Events/Event.h"

namespace Lynton
{
	struct WindowProperties
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "Lynton Engine", unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height) {}
	};


	// platform independent abstraction (interface) of a desktop system based window
	class LYNTON_API Window
	{
	public:
		// function pointer of a void returning, Event& taking function
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void on_update() = 0;

		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		virtual void set_event_callback(const EventCallback& callback) = 0;
		
		virtual void set_vsync(bool enable) = 0;
		virtual bool is_vsync() const = 0;

		static Window* create(const WindowProperties& props = WindowProperties());
	};
}
