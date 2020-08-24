#pragma once

#include "Lynton.h"

#include "ParticleSystem.h"

class Sandbox2D : public Lynton::Layer
{
private:
	Lynton::OrthographicCameraController m_camera_controller;

	Lynton::Ref<Lynton::Texture2D> m_checker_board_texture, m_sprite_sheet;
	Lynton::Ref<Lynton::SubTexture2D> m_stairs_texture, m_barrel_texture, m_tree_texture;

	glm::vec4 m_square_color = { 0.5f, 0.7f, 1.0f, 1.0f };

	ParticleSystem m_particle_system;
	ParticleProps m_particle_props;

	std::unordered_map<char, Lynton::Ref<Lynton::SubTexture2D>> m_texture_map;
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void on_attach() override;
	virtual void on_detach() override;
	virtual void on_update(Lynton::TimeStep time_step) override;
	virtual void on_event(Lynton::Event& event) override;
	virtual void on_imgui_render() override;
};
