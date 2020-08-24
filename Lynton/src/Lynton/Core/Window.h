#pragma once

#include "lypch.h"

#include "Lynton/Core/Core.h"
#include "Lynton/Events/Event.h"

namespace Lynton
{
	struct WindowProperties
	{
		std::string title;
		uint32_t height;
		uint32_t width;

		WindowProperties(const std::string& title = "Lynton Engine", uint32_t width = 1280, uint32_t height = 720)
			: title(title), width(width), height(height) {}
	};


	// platform independent abstraction (interface) of a desktop system based window
	class Window
	{
	public:
		// function pointer of a void returning, Event& taking function
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void on_update() = 0;

		virtual uint32_t get_width() const = 0;
		virtual uint32_t get_height() const = 0;

		virtual void set_event_callback(const EventCallback& callback) = 0;
		
		virtual void set_vsync(bool enable) = 0;
		virtual bool is_vsync() const = 0;

		virtual void* get_native_window() const = 0;

		static Scope<Window> create(const WindowProperties& props = WindowProperties());
	};
}
