#pragma once

#include "Lynton.h"

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
	ExampleLayer();
	void on_update(Lynton::TimeStep time_step) override;

	void on_imgui_render() override;
	void on_event(Lynton::Event& event) override;

	bool on_key_pressed_event(Lynton::KeyPressedEvent event);
};
