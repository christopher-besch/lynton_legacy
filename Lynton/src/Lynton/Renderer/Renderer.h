#pragma once

namespace Lynton
{

	enum class RendererAPI
	{
		none = 0,
		open_gl = 1
	};

	class Renderer
	{
	private:
		static RendererAPI s_renderer_api;
	public:
		inline static RendererAPI get_api() { return s_renderer_api; }
	};

}
