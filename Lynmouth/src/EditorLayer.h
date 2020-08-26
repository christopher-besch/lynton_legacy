#pragma once

#include "Lynton.h"

namespace Lynton
{

    class EditorLayer : public Layer
    {
    private:
	    OrthographicCameraController m_camera_controller;

		Ref<Texture2D> m_checker_board_texture;

		glm::vec2 m_viewport_size = { 0, 0 };
	    Ref<FrameBuffer> m_frame_buffer;
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
