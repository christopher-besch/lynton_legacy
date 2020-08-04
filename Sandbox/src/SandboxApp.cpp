#include "Lynton.h"

#include "imgui/imgui.h"

class ExampleLayer : public Lynton::Layer
{
private:
	std::shared_ptr<Lynton::Shader> m_shader;
	std::shared_ptr<Lynton::VertexArray> m_vertex_array;

	std::shared_ptr<Lynton::Shader> m_shader2;
	std::shared_ptr<Lynton::VertexArray> m_square_vao;

	static Lynton::Application* s_instance;

    Lynton::OrthographicCamera m_camera;
	float m_camera_move_speed = 0.01f;
	float m_camera_turn_speed = 2.0f;
public:
	ExampleLayer()
		: Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_vertex_array.reset(Lynton::VertexArray::create());
		// should get unbound here <- otherwise everything bound after here gets associated with the vao

		// vertex buffer
		float vertices[(3 + 4) * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.7f, 0.2f, 0.3f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.6f, 0.1f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.1f, 0.0f, 0.9f
		};
		std::shared_ptr<Lynton::VertexBuffer> vertex_buffer;
		vertex_buffer.reset(Lynton::VertexBuffer::create(sizeof(vertices), vertices));
		// vertex buffer layout
        Lynton::BufferLayout layout = {
			{Lynton::ShaderDataType::float3, "a_position" },
			{Lynton::ShaderDataType::float4, "a_color" }
		};
		vertex_buffer->set_layout(layout);
		m_vertex_array->add_vertex_buffer(vertex_buffer);

		// index buffer
		uint32_t indices[1 * 3] = {
			0, 1, 2
		};
		std::shared_ptr<Lynton::IndexBuffer> index_buffer;
		index_buffer.reset(Lynton::IndexBuffer::create(sizeof(indices) / sizeof(uint32_t), indices));
		m_vertex_array->set_index_buffer(index_buffer);

		// ToDo: temporary

		m_square_vao.reset(Lynton::VertexArray::create());

		float vertices2[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<Lynton::VertexBuffer> square_vb;
		square_vb.reset(Lynton::VertexBuffer::create(sizeof(vertices2), vertices2));

		square_vb->set_layout({
			{Lynton::ShaderDataType::float3, "a_position" }
			});
		m_square_vao->add_vertex_buffer(square_vb);

		uint32_t indices2[2 * 3] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<Lynton::IndexBuffer> square_ib;
		square_ib.reset(Lynton::IndexBuffer::create(sizeof(indices2) / sizeof(uint32_t), indices2));
		m_square_vao->set_index_buffer(square_ib);

		// shader
		std::string vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;
		    layout(location = 1) in vec4 a_color;

		    uniform mat4 u_view_projection;

		    out vec3 v_position;
		    out vec4 v_color;

		    void main()
		    {
		        v_position = a_position;
                v_color = a_color;
		        gl_Position = u_view_projection * vec4(a_position, 1.0);
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
		m_shader.reset(new Lynton::Shader(vertex_src, fragment_src));

		vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;

	        uniform mat4 u_view_projection;

		    out vec3 v_position;

		    void main()
		    {
		        v_position = a_position;
		        gl_Position = u_view_projection * vec4(a_position, 1.0);
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
		m_shader2.reset(new Lynton::Shader(vertex_src, fragment_src));
	}

	void on_update() override
	{
		glm::vec3 position = m_camera.get_position();
		position.y += Lynton::Input::is_key_pressed(LY_KEY_W) * m_camera_move_speed;
		position.x -= Lynton::Input::is_key_pressed(LY_KEY_A) * m_camera_move_speed;
		position.y -= Lynton::Input::is_key_pressed(LY_KEY_S) * m_camera_move_speed;
		position.x += Lynton::Input::is_key_pressed(LY_KEY_D) * m_camera_move_speed;
		m_camera.set_position(position);

		float rotation = m_camera.get_rotation();
		rotation += Lynton::Input::is_key_pressed(LY_KEY_Q) * m_camera_turn_speed;
		rotation -= Lynton::Input::is_key_pressed(LY_KEY_E) * m_camera_turn_speed;
		m_camera.set_rotation(rotation);

		Lynton::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        Lynton::RenderCommand::clear();

        Lynton::Renderer::begin_scene(m_camera);

        Lynton::Renderer::submit(m_shader2, m_square_vao);
        Lynton::Renderer::submit(m_shader, m_vertex_array);

        Lynton::Renderer::end_scene();
	}

	void on_imgui_render() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Application average %.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        Lynton::Application& app = Lynton::Application::get();

		ImGui::Text("Window Parameters");
		const std::string window_size = "width: " + std::to_string(app.get_window().get_width()) +
			" height:  " + std::to_string(app.get_window().get_height());
		ImGui::Text(window_size.c_str());

		bool vsync = app.get_window().is_vsync();
		ImGui::Checkbox("VSync", &vsync);
		app.get_window().set_vsync(vsync);

		ImGui::Text("Camera");
		ImGui::SliderFloat("Movement Speed", &m_camera_move_speed, 0.0f, 0.2f);
		ImGui::SliderFloat("Turning Speed", &m_camera_turn_speed, 0.0f, 5.0f);
		ImGui::End();
	}

	void on_event(Lynton::Event& event) override
	{
		// Lynton::EventDispatcher dispatcher(event);
		// dispatcher.dispatch<Lynton::KeyPressedEvent>(LY_BIND_EVENT_FUNCTION(ExampleLayer::on_key_pressed_event));
	}
};


class Sandbox : public Lynton::Application
{
public:
	Sandbox()
	{
		push_layer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

Lynton::Application* Lynton::create_application()
{
	return new Sandbox();
}

/*
 * $(TEMP)vc$(PlatformToolsetVersion).pdb has to be added in every projects property page under C/C++ -> Output Files -> Program Database File Name
 */
