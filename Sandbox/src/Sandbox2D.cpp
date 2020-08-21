#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_camera_controller(1280.0f / 720.0f, true)
{
}

// ToDo: inline wrong blabla

void Sandbox2D::on_attach()
{
	LY_PROFILE_FUNCTION();

	m_checker_board_texture = Lynton::Texture2D::create("assets/textures/Checkerboard.png");

	m_particle_props.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_particle_props.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_particle_props.SizeBegin = 0.5f, m_particle_props.SizeVariation = 0.3f, m_particle_props.SizeEnd = 0.0f;
	m_particle_props.LifeTime = 5.0f;
	m_particle_props.Velocity = { 0.0f, 0.0f };
	m_particle_props.VelocityVariation = { 3.0f, 1.0f };
	m_particle_props.Position = { 0.0f, 0.0f };
}

void Sandbox2D::on_detach()
{
	LY_PROFILE_FUNCTION();

	
}

void Sandbox2D::on_update(Lynton::TimeStep time_step)
{
	LY_PROFILE_FUNCTION();

	// update
	m_camera_controller.on_update(time_step);

	// render
	Lynton::Renderer2D::reset_stats();
    {
		LY_PROFILE_SCOPE("Render Prep");
        Lynton::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 0.0f });
	    Lynton::RenderCommand::clear();
    }

    {
		LY_PROFILE_SCOPE("Render Draw");

		static float rotation = 0.0f;
		rotation += time_step * 50.0f;

        Lynton::Renderer2D::begin_scene(m_camera_controller.get_camera());
        Lynton::Renderer2D::draw_rotated_quad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Lynton::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Lynton::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Lynton::Renderer2D::draw_quad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_checker_board_texture, 10.0f);
		Lynton::Renderer2D::draw_rotated_quad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_checker_board_texture, 20.0f);
        Lynton::Renderer2D::end_scene();

		Lynton::Renderer2D::begin_scene((m_camera_controller.get_camera()));
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for ( float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f,  0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Lynton::Renderer2D::draw_quad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Lynton::Renderer2D::end_scene();

    }

	{
		LY_PROFILE_SCOPE("Particle System");


		if (Lynton::Input::is_mouse_button_pressed(LY_MOUSE_BUTTON_LEFT))
		{
			auto [x, y] = Lynton::Input::get_mouse_position();
			auto width = Lynton::Application::get().get_window().get_width();
			auto height = Lynton::Application::get().get_window().get_height();

			auto bounds = m_camera_controller.get_bounds();
			auto pos = m_camera_controller.get_camera().get_position();
			x = (x / width) * bounds.get_width() - bounds.get_width() * 0.5f;
			y = bounds.get_height() * 0.5f - (y / height) * bounds.get_height();
			m_particle_props.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 50; i++)
				m_particle_system.Emit(m_particle_props);
		}

		m_particle_system.OnUpdate(time_step);
		m_particle_system.OnRender(m_camera_controller.get_camera());
	}
	
}

void Sandbox2D::on_event(Lynton::Event& event)
{
	m_camera_controller.on_event(event);

}

void Sandbox2D::on_imgui_render()
{
	LY_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Lynton::Renderer2D::get_stats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.draw_calls);
	ImGui::Text("Quads: %d", stats.quad_count);
	ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
	ImGui::Text("Indices: %d", stats.get_total_index_count());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));

	ImGui::End();
}
