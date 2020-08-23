#pragma once

#include "Lynton/Renderer/FrameBuffer.h"

namespace Lynton
{

	class OpenGLFrameBuffer : public FrameBuffer
	{
	private:
		uint32_t m_renderer_id;
		uint32_t m_color_attachment, m_depth_attachment;
		FrameBufferSpecification m_specification;
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void invalidate();

		virtual void bind() override;
		virtual void unbind() override;

		virtual uint32_t get_color_attachment_renderer_id() const override { return m_color_attachment; }
		virtual const FrameBufferSpecification& get_specification() const override { return m_specification; }
	};

}
