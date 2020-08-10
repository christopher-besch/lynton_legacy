#include "lypch.h"
#include "OrthographicCameraController.h"

#include "Lynton/Input.h"
#include "Lynton/KeyCodes.h"

namespace Lynton
{

    OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool rotation)
        : m_aspect_ration(aspect_ratio), m_rotation(rotation), m_camera(-m_aspect_ration * m_zoom_level, m_aspect_ration* m_zoom_level, -m_zoom_level, m_zoom_level)
    {

    }

    void OrthographicCameraController::on_update(TimeStep time_step)
    {
        m_camera_position.y += Input::is_key_pressed(LY_KEY_W) * m_camera_move_speed * time_step;
        m_camera_position.x -= Input::is_key_pressed(LY_KEY_A) * m_camera_move_speed * time_step;
        m_camera_position.y -= Input::is_key_pressed(LY_KEY_S) * m_camera_move_speed * time_step;
        m_camera_position.x += Input::is_key_pressed(LY_KEY_D) * m_camera_move_speed * time_step;
        m_camera.set_position(m_camera_position);

        if (m_rotation)
        {
            m_camera_rotation += Input::is_key_pressed(LY_KEY_Q) * m_camera_turn_speed * time_step;
            m_camera_rotation -= Input::is_key_pressed(LY_KEY_E) * m_camera_turn_speed * time_step;
            m_camera.set_rotation(m_camera_rotation);
        }
    }

    void OrthographicCameraController::on_event(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>(LY_BIND_EVENT_FUNCTION(OrthographicCameraController::on_mouse_scrolled));
        dispatcher.dispatch<WindowResizedEvent>(LY_BIND_EVENT_FUNCTION(OrthographicCameraController::on_window_resized));
    }

    bool OrthographicCameraController::on_mouse_scrolled(MouseScrolledEvent& event)
    {
        m_zoom_level -= event.get_y() * 0.25f;
        m_zoom_level = std::max(m_zoom_level, 0.25f);
        m_camera.set_projection(-m_aspect_ration * m_zoom_level, m_aspect_ration * m_zoom_level, -m_zoom_level, m_zoom_level);
        return false;
    }

    bool OrthographicCameraController::on_window_resized(WindowResizedEvent& event)
    {
        m_aspect_ration = static_cast<float>(event.get_width()) / static_cast<float>(event.get_height());
        m_camera.set_projection(-m_aspect_ration * m_zoom_level, m_aspect_ration * m_zoom_level, -m_zoom_level, m_zoom_level);
        return false;
    }

}
