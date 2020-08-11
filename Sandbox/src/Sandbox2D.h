#pragma once

#include "Lynton.h"

class Sandbox2D : public Lynton::Layer
{
private:
	Lynton::OrthographicCameraController m_camera_controller;

	// ToDo: temporary
	Lynton::Ref<Lynton::Shader> m_flat_color_shader;
	Lynton::Ref<Lynton::VertexArray> m_vertex_array;

	glm::vec4 m_square_color = { 0.5f, 0.7f, 1.0f, 1.0f };



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

	// in (1/2 screen)/second
	float m_move_speed = 2.0f;
	// in degrees/second
	float m_turn_speed = 30.0f;
	// in scale units/second
	float m_scale_speed = 0.1f;

	Lynton::Ref<Lynton::Texture2D> m_texture, m_cherno_logo_texture;
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void on_attach() override;
	virtual void on_detach() override;
	virtual void on_update(Lynton::TimeStep time_step) override;
	virtual void on_event(Lynton::Event& event) override;
	virtual void on_imgui_render() override;
};
