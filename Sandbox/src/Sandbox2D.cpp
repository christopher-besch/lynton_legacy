#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template<typename Fn>
class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time_point;
	const char* m_name;
	bool m_stopped = false;
	Fn m_func;
public:
	Timer(const char* name, Fn&& func)
	    : m_name(name), m_func(func)
	{
		m_start_time_point = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_stopped)
            stop();
	}

	void stop()
	{
		auto end_time_point = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time_point).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

		auto duration = end - start;
		float ms = duration * 0.001;
		m_stopped = true;

		m_func({ m_name, ms });
	}
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profile_result) { m_profile_results.push_back(profile_result);  })

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
	PROFILE_SCOPE("Sandbox2D::on_update");

	// update
	m_camera_controller.on_update(time_step);

	// render
	Lynton::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 0.0f });
	Lynton::RenderCommand::clear();

	Lynton::Renderer2D::begin_scene(m_camera_controller.get_camera());

	Lynton::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_square_color);
	Lynton::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Lynton::Renderer2D::draw_quad({ 0.2f, 0.5f, -0.1 }, { 10.0f, 10.0f }, m_checker_board_texture);

	Lynton::Renderer2D::end_scene();
}

void Sandbox2D::on_event(Lynton::Event& event)
{
	m_camera_controller.on_event(event);

}

void Sandbox2D::on_imgui_render()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));

	for (auto& result : m_profile_results)
	{
		char label[50];
		strcpy(label, "%.3fms  ");
		strcat(label, result.name);
		ImGui::Text(label, result.time);
	}
	m_profile_results.clear();

	ImGui::End();
}
