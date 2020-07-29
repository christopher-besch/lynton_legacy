#pragma once

#include "Core.h"
#include "Lynton/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

#include "Lynton/ImGui/ImGuiLayer.h"

#include "Lynton/Renderer/Shader.h"
#include "Lynton/Renderer/Buffer.h"

namespace Lynton
{

	class  Application
	{
	private:
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imgui_layer;
		bool m_running = true;
		LayerStack m_layer_stack;

		unsigned int m_vertex_Array;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VertexBuffer> m_vertex_buffer;
		std::unique_ptr<IndexBuffer> m_index_buffer;

		static Application* s_instance;
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
