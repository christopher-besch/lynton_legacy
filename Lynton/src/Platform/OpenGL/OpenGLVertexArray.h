#pragma once

#include "Lynton/Renderer/VertexArray.h"

namespace Lynton
{

	class OpenGLVertexArray: public VertexArray
	{
	private:
		uint32_t m_renderer_id;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffer;
		std::shared_ptr<IndexBuffer> m_index_buffer;
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
		virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;

		inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffer() const { return m_vertex_buffer; };
		inline virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const { return m_index_buffer; };

		static VertexArray* create();
	};

}
