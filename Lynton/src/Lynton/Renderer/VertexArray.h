#pragma once

#include "Lynton/Renderer/Buffer.h"
#include <memory>

namespace Lynton
{

	// interface for abstracting Vertex Arrays from different rendering apis
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
		virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const = 0;

		static VertexArray* create();
	};

}
