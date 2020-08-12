#include "lypch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Lynton
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> flat_color_shader;
	};

	static Renderer2DStorage* s_data;

    void Renderer2D::init()
    {
		s_data = new Renderer2DStorage();

		s_data->quad_vertex_array = VertexArray::create();

		float square_vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		Ref<VertexBuffer> vertex_buffer;
		vertex_buffer.reset(VertexBuffer::create(sizeof(square_vertices), square_vertices));

		vertex_buffer->set_layout({
			{ ShaderDataType::float3, "a_position" }
		});
		s_data->quad_vertex_array->add_vertex_buffer(vertex_buffer);

		uint32_t indices[2 * 3] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> index_buffer;
		index_buffer.reset(IndexBuffer::create(sizeof(indices) / sizeof(uint32_t), indices));
		s_data->quad_vertex_array->set_index_buffer(index_buffer);

		s_data->flat_color_shader = Shader::create("assets/shaders/FlatColor.glsl");
    }

    void Renderer2D::shutdown()
    {
		delete s_data;
    }

    void Renderer2D::begin_scene(const OrthographicCamera& camera)
    {
		// ToDo: temporary
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->upload_uniform_mat4("u_view_projection", camera.get_view_projection_matrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->upload_uniform_mat4("u_transform", glm::mat4(1.0f));
    }

    void Renderer2D::end_scene()
    {
    }

    void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2 size, const glm::vec4& color)
    {
		draw_quad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2 size, const glm::vec4& color)
    {
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->upload_uniform_vec4("u_color", color);

		s_data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data->quad_vertex_array);
    }

}
