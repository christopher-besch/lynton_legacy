#pragma once

#include <glm/glm.hpp>

#include "OrthographicCameraController.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Lynton/Renderer/OrthographicCamera.h"

namespace Lynton
{
    class Renderer2D
	{
    public:
		static void init();
		static void shutdown();

		static void begin_scene(const OrthographicCamera& camera);
		static void end_scene();

		// primitives
		static void draw_quad(const glm::vec2& position, const glm::vec2 size, const glm::vec4& color);
		static void draw_quad(const glm::vec3& position, const glm::vec2 size, const glm::vec4& color);
		static void draw_quad(const glm::vec2& position, const glm::vec2 size, const Ref<Texture>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_quad(const glm::vec3& position, const glm::vec2 size, const Ref<Texture>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

		static void draw_rotated_quad(const glm::vec2& position, const glm::vec2 size, float rotation, const glm::vec4& color);
		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const glm::vec4& color);
		static void draw_rotated_quad(const glm::vec2& position, const glm::vec2 size, float rotation, const Ref<Texture>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2 size, float rotation, const Ref<Texture>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
	};

}
