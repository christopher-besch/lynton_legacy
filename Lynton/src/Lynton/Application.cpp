#include "lypch.h"

#include "Application.h"
#include "Core.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Log.h"

#include <Glad/glad.h>

#include "Input.h"

namespace Lynton
{

	// make Application a singleton
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		LY_CORE_ASSERT(!s_instance, "Application already exists!")
		s_instance = this;

		// create window handler
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(LY_BIND_EVENT_FUNCTION(Application::on_event));

		// ImGui
		m_imgui_layer = new ImGuiLayer();
		push_overlay(m_imgui_layer);

		m_vertex_array.reset(VertexArray::create());
		// should get unbound here <- otherwise everything bound after here gets associated with the vao

		// vertex buffer
		float vertices[( 3 + 4 ) * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.7f, 0.2f, 0.3f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.6f, 0.1f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.1f, 0.0f, 0.9f
		};
		std::shared_ptr<VertexBuffer> vertex_buffer;
		vertex_buffer.reset(VertexBuffer::create(sizeof(vertices), vertices));
		// vertex buffer layout
		BufferLayout layout = {
			{ ShaderDataType::float3, "a_position" },
			{ ShaderDataType::float4, "a_color" }
		};
		vertex_buffer->set_layout(layout);
		m_vertex_array->add_vertex_buffer(vertex_buffer);

		// index buffer
		uint32_t indices[1 * 3] = {
			0, 1, 2
		};
		std::shared_ptr<IndexBuffer> index_buffer;
		index_buffer.reset(IndexBuffer::create(sizeof(indices) / sizeof(uint32_t), indices));
		m_vertex_array->set_index_buffer(index_buffer);

		// ToDo: temporary

		m_square_vao.reset(VertexArray::create());

		float vertices2[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> square_vb;
		square_vb.reset(VertexBuffer::create(sizeof(vertices2), vertices2));

		square_vb->set_layout({
			{ ShaderDataType::float3, "a_position" }
		});
		m_square_vao->add_vertex_buffer(square_vb);

		uint32_t indices2[2 * 3] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<IndexBuffer> square_ib;
		square_ib .reset(IndexBuffer::create(sizeof(indices2) / sizeof(uint32_t), indices2));
		m_square_vao->set_index_buffer(square_ib);

		// shader
		std::string vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;
		    layout(location = 1) in vec4 a_color;

		    out vec3 v_position;
		    out vec4 v_color;

		    void main()
		    {
		        v_position = a_position;
                v_color = a_color;
		        gl_Position = vec4(a_position, 1.0);
		    }

	    )";
		std::string fragment_src = R"(
            #version 330 core

		    layout(location = 0) out vec4 color;

		    in vec3 v_position;
		    in vec4 v_color;

		    void main()
		    {
		        color = vec4(v_position * 0.5 + 0.5, 1.0);
		        color = v_color;
		    }

	    )";
		m_shader.reset(new Shader(vertex_src, fragment_src));

		// shader
		vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;

		    out vec3 v_position;

		    void main()
		    {
		        v_position = a_position;
		        gl_Position = vec4(a_position, 1.0);
		    }

	    )";
		fragment_src = R"(
            #version 330 core

		    layout(location = 0) out vec4 color;

		    in vec3 v_position;
		    in vec4 v_color;

		    void main()
		    {
		        color = vec4(0.2f, 0.7f, 0.65f, 1.0f);
		    }

	    )";
		m_shader2.reset(new Shader(vertex_src, fragment_src));
	}

	Application::~Application()
	{
	}

	void Application::push_layer(Layer* layer)
    {
		m_layer_stack.push_layer(layer);
		layer->on_attach();
    }

	void Application::push_overlay(Layer* layer)
    {
		m_layer_stack.push_overlay(layer);
		layer->on_attach();
    }

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader2->bind();
			m_square_vao->bind();
			glDrawElements(GL_TRIANGLES, m_square_vao->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);

			m_shader->bind();
			m_vertex_array->bind();
			glDrawElements(GL_TRIANGLES, m_vertex_array->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_layer_stack)
				layer->on_update();

			m_imgui_layer->begin();
			for (Layer* layer : m_layer_stack)
				layer->on_imgui_render();
			m_imgui_layer->end();

			m_window->on_update();
		}
	}

	void Application::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);
		// when the event is a WindowCloseEvent -> call on_window_close
		dispatcher.dispatch<WindowCloseEvent>(LY_BIND_EVENT_FUNCTION(Application::on_window_close));

		// ToDo: put break into loop instead of if?
	    // sending the event through every layer until one handles it -> overlays get events first
		for ( auto iterator = m_layer_stack.end(); iterator != m_layer_stack.begin(); )
		{
			(*--iterator)->on_event(event);
			if (event.m_handled)
				break;
		}
	}

	bool Application::on_window_close(WindowCloseEvent& event)
    {
		m_running = false;
		return true;
    }

}
