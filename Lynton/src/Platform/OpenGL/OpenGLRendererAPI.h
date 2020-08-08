#pragma once

#include "Lynton/Renderer/RendererAPI.h"

namespace Lynton
{

	class OpenGLRendererAPI : public RendererAPI
	{

	public:
		virtual void init() override;

		virtual void set_clear_color(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void draw_indexed(const Ref<VertexArray>& vertex_array) override;

	};

}
