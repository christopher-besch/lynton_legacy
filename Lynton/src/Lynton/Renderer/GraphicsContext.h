#pragma once

namespace Lynton
{

	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swap_buffers() = 0;
	};

}
