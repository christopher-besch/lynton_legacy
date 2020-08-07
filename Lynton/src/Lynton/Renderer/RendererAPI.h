#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Lynton
{

	// interface for abstracting simple graphics rendering calls
	// singleton
	class RendererAPI
	{
	public:
		enum class API
		{
			none = 0,
			open_gl = 1
		};
	private:
		static API s_api;
	public:
		virtual void set_clear_color(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void draw_indexed(const Ref<VertexArray>& vertex_array) = 0;

		inline static API get_api() { return s_api; }
	};

}
