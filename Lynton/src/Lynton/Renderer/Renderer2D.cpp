#include "lypch.h"
#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderCommand.h"

namespace Lynton
{

	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 tex_coord;
		// ToDo: texid
	};

	struct Renderer2DData
	{
		const uint32_t max_quads = 10000;
		const uint32_t max_vertices = max_quads * 4;
		const uint32_t max_indices = max_quads * 6;

		Ref<VertexArray> quad_vertex_array;
		Ref<VertexBuffer> quad_vertex_buffer;
		Ref<Shader> texture_shader;
		Ref<Texture> white_texture;

		uint32_t quad_index_count = 0;
		QuadVertex* quad_vertex_buffer_base = nullptr;
		QuadVertex* quad_vertex_buffer_ptr = nullptr;
	};

	static Renderer2DData s_data;

    void Renderer2D::init()
    {
		LY_PROFILE_FUNCTION();

		s_data.quad_vertex_array = VertexArray::create();
		
		s_data.quad_vertex_buffer = VertexBuffer::create(s_data.max_vertices * sizeof(QuadVertex));

		s_data.quad_vertex_buffer->set_layout({
			{ ShaderDataType::float3, "a_position" },
			{ ShaderDataType::float4, "a_color" },
			{ ShaderDataType::float2, "a_tex_coord" }
		});
		s_data.quad_vertex_array->add_vertex_buffer(s_data.quad_vertex_buffer);

		s_data.quad_vertex_buffer_base = new QuadVertex[s_data.max_vertices];

		uint32_t offset = 0;
		uint32_t* quad_indices = new uint32_t[s_data.max_indices];
		for (uint32_t i = 0; i < s_data.max_indices; i += 6)
		{
			// first triangle
			quad_indices[i + 0] = offset + 0;
			quad_indices[i + 1] = offset + 1;
			quad_indices[i + 2] = offset + 2;
			// second triangle
			quad_indices[i + 3] = offset + 2;
			quad_indices[i + 4] = offset + 3;
			quad_indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quad_index_buffer = IndexBuffer::create(s_data.max_indices, quad_indices);
		s_data.quad_vertex_array->set_index_buffer(quad_index_buffer);
		delete[] quad_indices;

		s_data.white_texture = Texture2D::create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_data.white_texture->set_data(&white_texture_data, sizeof(white_texture_data));

		s_data.texture_shader = Shader::create("assets/shaders/Texture.glsl");
		s_data.texture_shader->bind();
		s_data.texture_shader->set_int("u_texture", 0);
    }

    void Renderer2D::shutdown()
    {
		LY_PROFILE_FUNCTION();
    }

    void Renderer2D::begin_scene(const OrthographicCamera& camera)
    {
		LY_PROFILE_FUNCTION();

		s_data.texture_shader->bind();
		s_data.texture_shader->set_mat4("u_view_projection", camera.get_view_projection_matrix());

		s_data.quad_index_count = 0;
		s_data.quad_vertex_buffer_ptr = s_data.quad_vertex_buffer_base;
    }

    void Renderer2D::end_scene()
    {
		LY_PROFILE_FUNCTION();

		uint32_t data_size = (uint8_t)s_data.quad_vertex_buffer_ptr - (uint8_t)s_data.quad_vertex_buffer_base;
		s_data.quad_vertex_buffer->set_data(s_data.quad_vertex_buffer_base, data_size);

		flush();
    }

	void Renderer2D::flush()
	{
		LY_PROFILE_FUNCTION();

		RenderCommand::draw_indexed(s_data.quad_vertex_array, s_data.quad_index_count);
	}

    void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2 size, const glm::vec4& color)
    {
		draw_quad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2 size, const glm::vec4& color)
    {
		LY_PROFILE_FUNCTION();

		s_data.quad_vertex_buffer_base->position = position;
		s_data.quad_vertex_buffer_base->color = color;
		s_data.quad_vertex_buffer_base->tex_coord = { 0.0f, 0.0f };
		s_data.quad_vertex_buffer_ptr++;

		s_data.quad_vertex_buffer_base->position = { position.x + size.x, position.y, position.z };
		s_data.quad_vertex_buffer_base->color = color;
		s_data.quad_vertex_buffer_base->tex_coord = { 1.0f, 0.0f };
		s_data.quad_vertex_buffer_ptr++;

		s_data.quad_vertex_buffer_base->position = { position.x + size.x, position.y + size.y, position.z };
		s_data.quad_vertex_buffer_base->color = color;
		s_data.quad_vertex_buffer_base->tex_coord = { 1.0f, 1.0f };
		s_data.quad_vertex_buffer_ptr++;

		s_data.quad_vertex_buffer_base->position = { position.x, position.y + size.y, position.z };
		s_data.quad_vertex_buffer_base->color = color;
		s_data.quad_vertex_buffer_base->tex_coord = { 0.0f, 1.0f };
		s_data.quad_vertex_buffer_ptr++;

		s_data.quad_index_count += 6;
    }

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2 size, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, texture, tiling_factor, tint_color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2 size, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		LY_PROFILE_FUNCTION();

		s_data.texture_shader->set_vec4("u_color", tint_color);
		s_data.texture_shader->set_float("u_tiling_factor", tiling_factor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.texture_shader->set_mat4("u_transform", transform);

		texture->bind();

		s_data.quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data.quad_vertex_array);
	}

    void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2 size, float rotation, const glm::vec4& color)
    {
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const glm::vec4& color)
    {
		LY_PROFILE_FUNCTION();

		s_data.texture_shader->set_vec4("u_color", color);
		s_data.texture_shader->set_float("u_tiling_factor", 1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		    * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.texture_shader->set_mat4("u_transform", transform);

		s_data.white_texture->bind();

		s_data.quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data.quad_vertex_array);
    }

    void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2 size, float rotation, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, texture, tiling_factor, tint_color);
    }

    void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const Ref<Texture>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
		LY_PROFILE_FUNCTION();

		s_data.texture_shader->set_vec4("u_color", tint_color);
		s_data.texture_shader->set_float("u_tiling_factor", tiling_factor);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.texture_shader->set_mat4("u_transform", transform);

		texture->bind();

		s_data.quad_vertex_array->bind();
		RenderCommand::draw_indexed(s_data.quad_vertex_array);
    }
}
