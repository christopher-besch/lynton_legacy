#pragma once

#include "Lynton/Renderer/OrthographicCamera.h"
#include "Lynton/Core/TimeStep.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Events/MouseEvent.h"

namespace Lynton
{

	struct OrthographicCameraBounds
	{
		float left, right;
		float bottom, top;

		float get_width() { return right - left; }
		float get_height() { return top - bottom; }
	};


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

		OrthographicCameraBounds m_bounds;
		OrthographicCamera m_camera;
	public:
		OrthographicCameraController(float aspect_ratio, bool rotation = false);

		void on_update(TimeStep time_step);
		void on_event(Event& event);

		inline OrthographicCamera get_camera() { return m_camera; }
		inline const OrthographicCamera get_camera() const { return m_camera; }

		inline OrthographicCameraBounds get_bounds() { return m_bounds; }
		inline const OrthographicCameraBounds get_bounds() const { return m_bounds; }

		inline void set_zoom_level(float level)
		{
		    m_zoom_level = level;
			calculate_view();
		}
		inline float get_zoom_level() const { return m_zoom_level; }
	private:
		void calculate_view();

		bool on_mouse_scrolled(MouseScrolledEvent& event);
		bool on_window_resized(WindowResizedEvent& event);
	};

}
