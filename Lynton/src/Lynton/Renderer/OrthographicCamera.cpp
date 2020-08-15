#include "lypch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Lynton
{
    void OrthographicCamera::recalculate_view_matrix()
    {
        LY_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0,0,1));

        m_view_matrix = glm::inverse(transform);
        // row mayor
        m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_view_matrix(1.0f)
    {
        LY_PROFILE_FUNCTION();

        m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    }

    void OrthographicCamera::set_projection(float left, float right, float bottom, float top)
    {
        LY_PROFILE_FUNCTION();

        m_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    }
}
