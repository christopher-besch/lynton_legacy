#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Lynton/Core/TimeStep.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Events/MouseEvent.h"

namespace Lynton
{

	class OrthographicCameraController
	{
	private:
		float m_aspect_ration;
		bool m_rotation;
		float m_zoom_level = 1.0f;

		glm::vec3 m_camera_position = { 0.0f, 0.0f, 0.0f };
		float m_camera_rotation = 0.0f;
		float m_camera_move_speed = 0.2f;
		float m_camera_turn_speed = 180.0f;

		OrthographicCamera m_camera;
	public:
		OrthographicCameraController(float aspect_ratio, bool rotation = false);

		void on_update(TimeStep time_step);
		void on_Event(Event& event);

		inline OrthographicCamera get_camera() { return m_camera; }
		inline const OrthographicCamera get_camera() const { return m_camera; }

		inline void set_zoom_level(float level) { m_zoom_level = level; }
		inline float get_zoom_level() { return m_zoom_level; }
	private:
		bool on_mouse_scrolled(MouseScrolledEvent& event);
		bool on_window_resized(WindowResizedEvent& event);
	};

}
