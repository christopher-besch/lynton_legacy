#include "lypch.h"
#include "Renderer.h"

#include "Lynton/Renderer/Renderer2D.h"

namespace Lynton
{
    Scope<Renderer::SceneData> Renderer::s_scene_data = create_scope<Renderer::SceneData>();

    void Renderer::init()
    {
        LY_PROFILE_FUNCTION();

        RenderCommand::init();
        Renderer2D::init();
    }

    void Renderer::shutdown()
    {
        Renderer2D::shutdown();
    }

    void Renderer::on_window_resize(uint32_t width, uint32_t height)
    {
        RenderCommand::set_viewport(0, 0, width, height);
    }

    void Renderer::begin_scene(OrthographicCamera& camera)
    {
        s_scene_data->view_projection_matrix = camera.get_view_projection_matrix();
    }

    void Renderer::end_scene()
    {
    }

    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform)
    {
        shader->bind();
        shader->set_mat4("u_view_projection", s_scene_data->view_projection_matrix);
        shader->set_mat4("u_transform", transform);

        vertex_array->bind();
        RenderCommand::draw_indexed(vertex_array);
    }
}
