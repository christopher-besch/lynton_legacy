#include "lypch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Lynton
{
    Renderer::SceneData* Renderer::s_scene_data = new Renderer::SceneData;

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
        std::dynamic_pointer_cast<OpenGLShader>(shader)->upload_uniform_mat4("u_view_projection", s_scene_data->view_projection_matrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->upload_uniform_mat4("u_transform", transform);

        vertex_array->bind();
        RenderCommand::draw_indexed(vertex_array);
    }
}
