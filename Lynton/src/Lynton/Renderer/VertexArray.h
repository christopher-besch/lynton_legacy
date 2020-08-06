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

		virtual void add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer) = 0;
		virtual void set_index_buffer(const Ref<IndexBuffer>& index_buffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& get_vertex_buffer() const = 0;
		virtual const Ref<IndexBuffer>& get_index_buffer() const = 0;

		static VertexArray* create();
	};

}
