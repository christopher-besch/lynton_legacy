#include "Lynton.h"
#include <Lynton/Core/EntryPoint.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Lynton::Layer
{
private:
	Lynton::ShaderLibrary m_shader_library;

	Lynton::Ref<Lynton::Shader> m_triangle_shader;
	Lynton::Ref<Lynton::VertexArray> m_triangle_vao;
	glm::vec3 m_triangle_position = { 0.0f, 0.0f, 0.0f };
	float m_triangle_rotation = 0.0f;
	float m_triangle_scale = 1.0f;
	bool m_move_triangle = false;

	Lynton::Ref<Lynton::Shader> m_square_shader;
	Lynton::Ref<Lynton::VertexArray> m_square_vao;
	glm::vec3 m_square_position = { 0.0f, 0.0f, 0.0f };
	float m_square_rotation = 0.0f;
	float m_square_scale = 1.0f;
	bool m_move_square = false;

    Lynton::OrthographicCameraController m_camera_controller;
	// in (1/2 screen)/second
	float m_move_speed = 2.0f;
	// in degrees/second
	float m_turn_speed = 30.0f;
	// in scale units/second
	float m_scale_speed = 0.1f;

	Lynton::Ref<Lynton::Shader> m_flat_color_shader;

	glm::vec3 m_square_color = { 0.2f, 0.3f, 0.8f };

	Lynton::Ref<Lynton::Texture2D> m_texture, m_cherno_logo_texture;

public:
	ExampleLayer()
		: Layer("Example"), m_camera_controller(1280.0f / 720.0f, true)
	{

	    //////////////
		// triangle //
		//////////////
		
		m_triangle_vao = Lynton::VertexArray::create();
		// should get unbound here <- otherwise everything bound after here gets associated with the vao

		// vertex buffer
		float triangle_vertices[(3 + 4) * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.7f, 0.2f, 0.3f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.6f, 0.1f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.1f, 0.0f, 0.9f
		};
		Lynton::Ref<Lynton::VertexBuffer> vertex_buffer;
		vertex_buffer = Lynton::VertexBuffer::create(sizeof(triangle_vertices), triangle_vertices);
		// vertex buffer layout
        Lynton::BufferLayout layout = {
			{Lynton::ShaderDataType::float3, "a_position" },
			{Lynton::ShaderDataType::float4, "a_color" }
		};
		vertex_buffer->set_layout(layout);
		m_triangle_vao->add_vertex_buffer(vertex_buffer);

		// index buffer
		uint32_t triangle_indices[1 * 3] = {
			0, 1, 2
		};
		Lynton::Ref<Lynton::IndexBuffer> index_buffer;
		index_buffer = Lynton::IndexBuffer::create(sizeof(triangle_indices) / sizeof(uint32_t), triangle_indices);
		m_triangle_vao->set_index_buffer(index_buffer);

		// shader
		const std::string triangle_vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;
		    layout(location = 1) in vec4 a_color;

		    uniform mat4 u_view_projection;
		    uniform mat4 u_transform;

		    out vec3 v_position;
		    out vec4 v_color;

		    void main()
		    {
		        v_position = a_position;
                v_color = a_color;
		        gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
		    }

	    )";
		const std::string triangle_fragment_src = R"(
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
		m_triangle_shader = Lynton::Shader::create("Triangle", triangle_vertex_src, triangle_fragment_src);

		////////////
		// square //
		////////////

		// ToDo: temporary
		m_square_vao = Lynton::VertexArray::create();

		float square_vertices[4 * ( 3 + 2 )] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Lynton::Ref<Lynton::VertexBuffer> square_vb;
		square_vb = Lynton::VertexBuffer::create(sizeof(square_vertices), square_vertices);

		square_vb->set_layout({
			{Lynton::ShaderDataType::float3, "a_position" },
			{Lynton::ShaderDataType::float2, "a_tex_coord" }
			});
		m_square_vao->add_vertex_buffer(square_vb);

		uint32_t square_indices[2 * 3] = {
			0, 1, 2,
			2, 3, 0
		};
		Lynton::Ref<Lynton::IndexBuffer> square_ib;
		square_ib = Lynton::IndexBuffer::create(sizeof(square_indices) / sizeof(uint32_t), square_indices);
		m_square_vao->set_index_buffer(square_ib);

		const std::string square_vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;

	        uniform mat4 u_view_projection;
		    uniform mat4 u_transform;

		    out vec3 v_position;

		    void main()
		    {
		        v_position = a_position;
		        gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
		    }

	    )";
		const std::string square_fragment_src = R"(
            #version 330 core

		    layout(location = 0) out vec4 color;

		    in vec3 v_position;

		    void main()
		    {
		        color = vec4(0.2f, 0.7f, 0.65f, 1.0f);
		    }

	    )";
		m_square_shader = Lynton::Shader::create("Square", square_vertex_src, square_fragment_src);

		const std::string flat_color_vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;

	        uniform mat4 u_view_projection;
		    uniform mat4 u_transform;

		    out vec3 v_position;

		    void main()
		    {
		        v_position = a_position;
		        gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
		    }

	    )";
		const std::string flat_color_fragment_src = R"(
            #version 330 core

		    layout(location = 0) out vec4 color;

		    uniform vec3 u_color;

		    in vec3 v_position;

		    void main()
		    {
		        color = vec4(u_color, 1.0f);
		    }

	    )";
		m_flat_color_shader = Lynton::Shader::create("FlatColor", flat_color_vertex_src, flat_color_fragment_src);

		const std::string texture_vertex_src = R"(
            #version 330 core

		    layout(location = 0) in vec3 a_position;
		    layout(location = 1) in vec2 a_tex_coord;

	        uniform mat4 u_view_projection;
		    uniform mat4 u_transform;

		    out vec2 v_tex_coord;

		    void main()
		    {
		        v_tex_coord = a_tex_coord;
		        gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
		    }

	    )";
		const std::string texture_fragment_src = R"(
            #version 330 core

		    layout(location = 0) out vec4 color;

		    in vec2 v_tex_coord;

		    // texture slot
		    uniform sampler2D u_texture;

		    void main()
		    {
		        color = texture(u_texture, v_tex_coord);
		    }

	    )";
		auto texture_shader = m_shader_library.load("assets/shaders/Texture.glsl");
		m_texture = Lynton::Texture2D::create("assets/textures/Checkerboard.png");

		m_cherno_logo_texture = Lynton::Texture2D::create("assets/textures/ChernoLogo.png");

		texture_shader->bind();
		texture_shader->set_int("u_texture", 0);
	}

	void on_update(Lynton::TimeStep time_step) override
	{
		// update
		m_camera_controller.on_update(time_step);

		m_triangle_position.y += Lynton::Input::is_key_pressed(LY_KEY_W)       * m_move_triangle * m_move_speed * time_step;
		m_triangle_position.x -= Lynton::Input::is_key_pressed(LY_KEY_A)       * m_move_triangle * m_move_speed * time_step;
		m_triangle_position.y -= Lynton::Input::is_key_pressed(LY_KEY_S)       * m_move_triangle * m_move_speed * time_step;
		m_triangle_position.x += Lynton::Input::is_key_pressed(LY_KEY_D)       * m_move_triangle * m_move_speed * time_step;
		m_triangle_rotation += Lynton::Input::is_key_pressed(LY_KEY_Q)         * m_move_triangle * m_turn_speed * time_step;
		m_triangle_rotation -= Lynton::Input::is_key_pressed(LY_KEY_E)         * m_move_triangle * m_turn_speed * time_step;
		m_triangle_scale -= Lynton::Input::is_key_pressed(LY_KEY_LEFT_SHIFT)   * m_move_triangle * m_scale_speed * time_step;
		m_triangle_scale += Lynton::Input::is_key_pressed(LY_KEY_LEFT_CONTROL) * m_move_triangle * m_scale_speed * time_step;

		m_square_position.y += Lynton::Input::is_key_pressed(LY_KEY_W)       * m_move_square * m_move_speed * time_step;
		m_square_position.x -= Lynton::Input::is_key_pressed(LY_KEY_A)       * m_move_square * m_move_speed * time_step;
		m_square_position.y -= Lynton::Input::is_key_pressed(LY_KEY_S)       * m_move_square * m_move_speed * time_step;
		m_square_position.x += Lynton::Input::is_key_pressed(LY_KEY_D)       * m_move_square * m_move_speed * time_step;
		m_square_rotation += Lynton::Input::is_key_pressed(LY_KEY_Q)         * m_move_square * m_turn_speed * time_step;
		m_square_rotation -= Lynton::Input::is_key_pressed(LY_KEY_E)         * m_move_square * m_turn_speed * time_step;
		m_square_scale -= Lynton::Input::is_key_pressed(LY_KEY_LEFT_SHIFT)   * m_move_square * m_scale_speed * time_step;
		m_square_scale += Lynton::Input::is_key_pressed(LY_KEY_LEFT_CONTROL) * m_move_square * m_scale_speed * time_step;

		glm::mat4 triangle_transform = glm::translate(glm::mat4(1.0f), m_triangle_position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(m_triangle_scale)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_triangle_rotation), glm::vec3(0, 0, 1));


		glm::mat4 square_transform = glm::translate(glm::mat4(1.0f), m_square_position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(m_square_scale)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_square_rotation), glm::vec3(0, 0, 1));

		// render
	    Lynton::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        Lynton::RenderCommand::clear();

        Lynton::Renderer::begin_scene(m_camera_controller.get_camera());

		auto texture_shader = m_shader_library.get("Texture");

		m_texture->bind();
	    Lynton::Renderer::submit(texture_shader, m_square_vao, square_transform);
		m_cherno_logo_texture->bind();
		Lynton::Renderer::submit(texture_shader, m_square_vao, square_transform);
        Lynton::Renderer::submit(m_triangle_shader, m_triangle_vao, triangle_transform);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));

		m_flat_color_shader->bind();
		m_flat_color_shader->set_vec3("u_color", m_square_color);

	    for (int y = 0; y < 20; y++)
		{
		    for (int x = 0; x < 20; x++)
		    {
				glm::vec3 pos(x * 0.06f, y * 0.06f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Lynton::Renderer::submit(m_flat_color_shader, m_square_vao, transform);
		    }
		}

        Lynton::Renderer::end_scene();
	}

	void on_imgui_render() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Application average %.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        Lynton::Application& app = Lynton::Application::get();

		const std::string window_size = "width: " + std::to_string(app.get_window().get_width()) +
			" height:  " + std::to_string(app.get_window().get_height());
		ImGui::Text(window_size.c_str());

		bool vsync = app.get_window().is_vsync();
		ImGui::Checkbox("VSync", &vsync);
		app.get_window().set_vsync(vsync);

		ImGui::Text("");

		ImGui::Text("Movement:");
		ImGui::Checkbox("Triangle", &m_move_triangle);
		ImGui::Checkbox("Square", &m_move_square);
		ImGui::SliderFloat("Movement Speed", &m_move_speed, 0.0f, 10.0f);
		ImGui::Text("(units/second)");
		ImGui::SliderFloat("Turning Speed", &m_turn_speed, 0.0f, 720.0f);
		ImGui::Text("(degrees/second)");
		ImGui::SliderFloat("Scaling Speed", &m_scale_speed, 0.0f, 6.0f);
		ImGui::Text("(scale units/second)");

		bool reset = false;
		ImGui::Checkbox("Reset Positions, Rotation and Scale", &reset );
		if (reset)
		{
			m_triangle_position = { 0.0f, 0.0f, 0.0f };
			m_triangle_rotation = 0.0f;
			m_triangle_scale = 1.0f;

			m_square_position = { 0.0f, 0.0f, 0.0f };
			m_square_rotation = 0.0f;
			m_square_scale = 1.0f;
		}

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_square_color));

		ImGui::End();
	}

	void on_event(Lynton::Event& event) override
	{
        m_camera_controller.on_event(event);

	    Lynton::EventDispatcher dispatcher(event);
		dispatcher.dispatch<Lynton::KeyPressedEvent>(LY_BIND_EVENT_FUNCTION(ExampleLayer::on_key_pressed_event));
	}

	bool on_key_pressed_event(Lynton::KeyPressedEvent event)
	{
	    switch (event.get_key_code())
	    {
		case LY_KEY_2:
			m_move_triangle = !m_move_triangle;
			return true;
		case LY_KEY_3:
			m_move_square = !m_move_square;
			return true;
		default:
			return false;
	    }
	}
};


class Sandbox : public Lynton::Application
{
public:
	Sandbox()
	{
		// push_layer(new ExampleLayer());
		push_layer(new Sandbox2D());
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
