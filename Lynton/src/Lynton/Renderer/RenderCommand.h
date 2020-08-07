#pragma once

#include "RendererAPI.h"

namespace Lynton
{

	// collection of functions to do specific single things regarding graphics rendering using an object inherited from RendererAPI
	// singleton
    class RenderCommand
	{
	private:
	    static RendererAPI* s_renderer_api;
	public:
		inline static void set_clear_color(const glm::vec4& color)
		{
			s_renderer_api->set_clear_color(color);
		}
		inline static void clear()
		{
			s_renderer_api->clear();
		}

		inline static void draw_indexed(const Ref<VertexArray>& vertex_array)
		{
			s_renderer_api->draw_indexed(vertex_array);
		}

	};

}
