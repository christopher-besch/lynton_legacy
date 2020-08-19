#pragma once

namespace Lynton
{

	// interface for a rendering context
	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swap_buffers() = 0;

		static Scope<GraphicsContext> create(void* window);
	};

}
