#include "lypch.h"
#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderCommand.h"

namespace Lynton
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> flat_color_shader;
		Ref<Shader> texture_shader;
	};

	static Renderer2DStorage* s_data;

    void Renderer2D::init()
    {
		s_data = new Renderer2DStorage();

		s_data->quad_vertex_array = VertexArray::create();

		float square_vertices[4 * ( 3 + 2 )] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> vertex_buffer;
		vertex_buffer.reset(VertexBuffer::create(sizeof(square_vertices), square_vertices));

		vertex_buffer->set_layout({
			{ ShaderDataType::float3, "a_position" },
			{ ShaderDataType::float2, "a_tex_coord" }
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
		s_data->texture_shader = Shader::create("assets/shaders/Texture.glsl");
		s_data->texture_shader->bind();
		s_data->texture_shader->set_int("u_texture", 0);
    }

    void Renderer2D::shutdown()
    {
		delete s_data;
    }

    void Renderer2D::begin_scene(const OrthographicCamera& camera)
    {
		// ToDo: temporary
		s_data->flat_color_shader->bind();
		s_data->flat_color_shader->set_mat4("u_view_projection", camera.get_view_projection_matrix());

		s_data->texture_shader->bind();
		s_data->texture_shader->set_mat4("u_view_projection", camera.get_view_projection_matrix());
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
		s_data->flat_color_shader->bind();
		s_data->flat_color_shader->set_vec4("u_color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->flat_color_shader->set_mat4("u_transform", transform);

		s_data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data->quad_vertex_array);
    }

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2 size, const Ref<Texture>& texture)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2 size, const Ref<Texture>& texture)
	{
		s_data->texture_shader->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->texture_shader->set_mat4("u_transform", transform);

		texture->bind();

		s_data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data->quad_vertex_array);
	}

}
