#pragma once

#include <glm/glm.hpp>

namespace Lynton
{

	class OrthographicCamera
	{
	private:
		glm::mat4 m_projection_matrix;
		glm::mat4 m_view_matrix;
		glm::mat4 m_view_projection_matrix;

		glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
		float m_rotation = 0.0f;
	private:
		void recalculate_view_matrix();
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void set_position(const glm::vec3& position)
		{
		    m_position = position;
			recalculate_view_matrix();
		}
	    inline const glm::vec3& get_position() const { return m_position; }

		void set_z_rotation(float rotation)
		{
		    m_rotation = rotation;
			recalculate_view_matrix();
		}
		inline float get_z_rotation() const { return m_rotation; }

		const glm::mat4& get_projection_matrix() const { return m_projection_matrix; }
		const glm::mat4& get_view_matrix() const { return m_view_matrix; }
		const glm::mat4& get_view_projection_matrix() const { return m_view_projection_matrix; }
	};

}
