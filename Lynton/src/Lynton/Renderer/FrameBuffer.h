#pragma once

#include "Lynton/Core/Core.h"

namespace Lynton
{

    struct FrameBufferSpecification
    {
		uint32_t width, height;
		uint32_t samples = 1;

		bool swap_chain_target = false;
    };

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual uint32_t get_color_attachment_renderer_id() const = 0;
		virtual const FrameBufferSpecification& get_specification() const = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpecification& spec);

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};

}