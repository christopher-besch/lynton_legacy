#pragma once

#include "Lynton/Renderer/RendererAPI.h"

namespace Lynton
{

	class OpenGLRendererAPI : public RendererAPI
	{

	public:
		virtual void init() override;

		virtual void set_clear_color(const glm::vec4& color) override;
		virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void clear() override;

		virtual void draw_indexed(const Ref<VertexArray>& vertex_array) override;

	};

}
