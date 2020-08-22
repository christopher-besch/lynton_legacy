#pragma once

#include <glm/glm.hpp>

#include "Lynton/Renderer/Texture.h"
#include "Lynton/Renderer/SubTexture2D.h"
#include "Lynton/Renderer/OrthographicCamera.h"

namespace Lynton
{
    class Renderer2D
	{
    private:
		static void flush_and_reset();
    public:
		static void init();
		static void shutdown();

		static void begin_scene(const OrthographicCamera& camera);
		static void end_scene();
		static void flush();

		// primitives
		static void draw_quad(const glm::vec3& position, const glm::vec2 size, const glm::vec4& color);
		static void draw_quad(const glm::vec3& position, const glm::vec2 size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_quad(const glm::vec3& position, const glm::vec2 size, const Ref<SubTexture2D>& sub_texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const glm::vec4& color);
		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const Ref<SubTexture2D>& sub_texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

		struct Statistics
		{
			uint32_t draw_calls = 0;
			uint32_t quad_count = 0;

			uint32_t get_total_vertex_count() const { return quad_count * 4; }
			uint32_t get_total_index_count() const { return quad_count * 6; }
		};
		static void reset_stats();
		static Statistics get_stats();
	};

}
