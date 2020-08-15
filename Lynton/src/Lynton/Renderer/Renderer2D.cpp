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
		Ref<Shader> texture_shader;
		Ref<Texture> white_texture;
	};

	static Renderer2DStorage* s_data;

    void Renderer2D::init()
    {
		LY_PROFILE_FUNCTION();

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

		s_data->white_texture = Texture2D::create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_data->white_texture->set_data(&white_texture_data, sizeof(white_texture_data));

		s_data->texture_shader = Shader::create("assets/shaders/Texture.glsl");
		s_data->texture_shader->bind();
		s_data->texture_shader->set_int("u_texture", 0);
    }

    void Renderer2D::shutdown()
    {
		LY_PROFILE_FUNCTION();

		delete s_data;
    }

    void Renderer2D::begin_scene(const OrthographicCamera& camera)
    {
		LY_PROFILE_FUNCTION();

		s_data->texture_shader->bind();
		s_data->texture_shader->set_mat4("u_view_projection", camera.get_view_projection_matrix());
    }

    void Renderer2D::end_scene()
    {
		LY_PROFILE_FUNCTION();

    }

    void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2 size, const glm::vec4& color)
    {
		draw_quad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2 size, const glm::vec4& color)
    {
		LY_PROFILE_FUNCTION();

		s_data->texture_shader->set_vec4("u_color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->texture_shader->set_mat4("u_transform", transform);

		s_data->white_texture->bind();

		s_data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data->quad_vertex_array);
    }

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2 size, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, texture, tiling_factor, tint_color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2 size, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		LY_PROFILE_FUNCTION();

		s_data->texture_shader->set_vec4("u_color", tint_color);
		s_data->texture_shader->set_float("u_tiling_factor", tiling_factor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->texture_shader->set_mat4("u_transform", transform);

		texture->bind();

		s_data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data->quad_vertex_array);
	}

    void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2 size, float rotation, const glm::vec4& color)
    {
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const glm::vec4& color)
    {
		LY_PROFILE_FUNCTION();

		s_data->texture_shader->set_vec4("u_color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		    * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->texture_shader->set_mat4("u_transform", transform);

		s_data->white_texture->bind();

		s_data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data->quad_vertex_array);
    }

    void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2 size, float rotation, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, texture, tiling_factor, tint_color);
    }

    void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
		LY_PROFILE_FUNCTION();

		s_data->texture_shader->set_vec4("u_color", tint_color);
		s_data->texture_shader->set_float("u_tiling_factor", tiling_factor);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->texture_shader->set_mat4("u_transform", transform);

		texture->bind();

		s_data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data->quad_vertex_array);
    }
}
