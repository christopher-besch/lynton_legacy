#pragma once

#include "Core.h"
#include "Lynton/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

#include "Lynton/ImGui/ImGuiLayer.h"
#include "Lynton/Core/TimeStep.h"

namespace Lynton
{

	// singleton
	class  Application
	{
	private:
		static Application* s_instance;

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imgui_layer;
		bool m_running = true;
		LayerStack m_layer_stack;

		float m_last_frame_time;
	public:
		Application();
		virtual ~Application();

		void run();

		void on_event(Event& event);

		void push_layer(Layer* layer);
		void push_overlay(Layer* layer);

		inline Window& get_window() { return *m_window; }

		inline static Application& get() { return *s_instance; }
		inline bool& get_running() { return m_running; }
	private:
		bool on_window_close(WindowCloseEvent& event);
	};

	// to be defined in client
	Application* create_application();
	
}
