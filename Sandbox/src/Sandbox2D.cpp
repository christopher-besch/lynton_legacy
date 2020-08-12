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
	m_vertex_array = Lynton::VertexArray::create();

	float square_vertices[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	Lynton::Ref<Lynton::VertexBuffer> vertex_buffer;
	vertex_buffer.reset(Lynton::VertexBuffer::create(sizeof(square_vertices), square_vertices));

	vertex_buffer->set_layout({
		{ Lynton::ShaderDataType::float3, "a_position" }
		});
	m_vertex_array->add_vertex_buffer(vertex_buffer);

	uint32_t indices[2 * 3] = {
		0, 1, 2,
		2, 3, 0
	};
	Lynton::Ref<Lynton::IndexBuffer> index_buffer;
	index_buffer.reset(Lynton::IndexBuffer::create(sizeof(indices) / sizeof(uint32_t), indices));
	m_vertex_array->set_index_buffer(index_buffer);

	m_flat_color_shader = Lynton::Shader::create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::on_detach()
{
}

void Sandbox2D::on_update(Lynton::TimeStep time_step)
{
	// update
	m_camera_controller.on_update(time_step);

	// render
	Lynton::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 0.0f });
	Lynton::RenderCommand::clear();

	Lynton::Renderer2D::begin_scene(m_camera_controller.get_camera());

	Lynton::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Lynton::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });

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
	ImGui::End();
}
