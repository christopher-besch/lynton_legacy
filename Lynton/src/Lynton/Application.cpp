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

	static GLenum shader_data_type_to_gl_enum(ShaderDataType type)
	{
        switch (type)
		{
		case ShaderDataType::float1: return GL_FLOAT;
		case ShaderDataType::float2: return GL_FLOAT;
		case ShaderDataType::float3: return GL_FLOAT;
		case ShaderDataType::float4: return GL_FLOAT;
		case ShaderDataType::mat3:   return GL_FLOAT;
		case ShaderDataType::mat4:   return GL_FLOAT;
		case ShaderDataType::int1:   return GL_INT;
		case ShaderDataType::int2:   return GL_INT;
		case ShaderDataType::int3:   return GL_INT;
		case ShaderDataType::int4:   return GL_INT;
		case ShaderDataType::bool1:  return GL_BOOL;
		default:
			LY_CORE_ASSERT(false, "Unknwon ShaderDataType!")
			return 0;
		}
	}

	Application::Application()
	{
		LY_CORE_ASSERT(!s_instance, "Application already exists!")
		s_instance = this;

		// create window handler
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(LY_BIND_EVENT_FUNCTION(Application::on_event));

		// ImGui layer
		m_imgui_layer = new ImGuiLayer();
		push_overlay(m_imgui_layer);

		glGenVertexArrays(1, &m_vertex_Array);
		glBindVertexArray(m_vertex_Array);

		float vertices[(3 + 4) * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.7f, 0.2f, 0.3f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.6f, 0.1f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.1f, 0.0f, 0.9f
		};

		m_vertex_buffer.reset(VertexBuffer::create(sizeof(vertices), vertices));

		{
			BufferLayout layout = {
				{ ShaderDataType::float3, "a_position" },
				{ ShaderDataType::float4, "a_color" }
			};
			m_vertex_buffer->set_layout(layout);
		}

		const auto& layout = m_vertex_buffer->get_layout();
	    uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.get_component_count(),
				shader_data_type_to_gl_enum(element.type),
				element.normalized ? GL_TRUE: GL_FALSE,
				m_vertex_buffer->get_layout().get_stride(),
				(const void*)element.offset);
			index++;
		}

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

		// TRIANGLES!!!
		uint32_t indices[1 * 3] = {
			0, 1, 2
		};
		m_index_buffer.reset(IndexBuffer::create(sizeof(indices) / sizeof(uint32_t), indices));

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

			m_shader->bind();
			glBindVertexArray(m_vertex_Array);
			glDrawElements(GL_TRIANGLES, m_index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);

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

	    // LY_CORE_TRACE("{0}", event);

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
