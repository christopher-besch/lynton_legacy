#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_camera_controller(1280.0f / 720.0f, true)
{
}

void Sandbox2D::on_attach()
{
	m_checker_board_texture = Lynton::Texture2D::create("assets/textures/Checkerboard.png");
}

void Sandbox2D::on_detach()
{
}

void Sandbox2D::on_update(Lynton::TimeStep time_step)
{
	LY_PROFILE_FUNCTION();

	// update
	{
		LY_PROFILE_SCOPE("Render Update");
	    m_camera_controller.on_update(time_step);
    }

	// render
    {
		LY_PROFILE_SCOPE("Render Prep");
        Lynton::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 0.0f });
	    Lynton::RenderCommand::clear();
    }

    {
		LY_PROFILE_SCOPE("Render Draw");
        Lynton::Renderer2D::begin_scene(m_camera_controller.get_camera());

	    Lynton::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_square_color);
	    Lynton::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	    Lynton::Renderer2D::draw_quad({ 0.2f, 0.5f, -0.1 }, { 10.0f, 10.0f }, m_checker_board_texture);

	    Lynton::Renderer2D::end_scene();
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
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));

	ImGui::End();
}
