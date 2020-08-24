#pragma once

#include "Lynton.h"

#include "ParticleSystem.h"

namespace Lynton
{

    class EditorLayer : public Layer
    {
    private:
	    OrthographicCameraController m_camera_controller;

	    Ref<Texture2D> m_checker_board_texture, m_sprite_sheet;
	    Ref<SubTexture2D> m_stairs_texture, m_barrel_texture, m_tree_texture;

	    Ref<FrameBuffer> m_frame_buffer;

	    glm::vec4 m_square_color = { 0.5f, 0.7f, 1.0f, 1.0f };

	    ParticleSystem m_particle_system;
	    ParticleProps m_particle_props;

	    std::unordered_map<char, Ref<SubTexture2D>> m_texture_map;
    public:
		EditorLayer();
	    virtual ~EditorLayer() = default;

	    virtual void on_attach() override;
	    virtual void on_detach() override;
	    virtual void on_update(TimeStep time_step) override;
	    virtual void on_event(Event& event) override;
	    virtual void on_imgui_render() override;
    };
    
}
