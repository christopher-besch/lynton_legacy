#include "lypch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Lynton
{

    static GLenum shader_data_type_to_gl_enum(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::float1: return GL_FLOAT;
        case ShaderDataType::float2: return GL_FLOAT;
        case ShaderDataType::float3: return GL_FLOAT;
        case ShaderDataType::float4: return GL_FLOAT;
        case ShaderDataType::mat3:   return GL_FLOAT;
        case ShaderDataType::mat4:   return GL_FLOAT;
        case ShaderDataType::int1:   return GL_INT;
        case ShaderDataType::int2:   return GL_INT;
        case ShaderDataType::int3:   return GL_INT;
        case ShaderDataType::int4:   return GL_INT;
        case ShaderDataType::bool1:  return GL_BOOL;
        default:
            LY_CORE_ASSERT(false, "Unknwon ShaderDataType!")
                return 0;
        }
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_renderer_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_renderer_id);
    }



    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(m_renderer_id);
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer)
    {
        glBindVertexArray(m_renderer_id);
        vertex_buffer->bind();

        LY_CORE_ASSERT(vertex_buffer->get_layout().get_elements().size(), "Vertex Buffer has no layout!")

        const auto& layout = vertex_buffer->get_layout();
        uint32_t index = 0;
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.get_component_count(),
                shader_data_type_to_gl_enum(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                vertex_buffer->get_layout().get_stride(),
                (const void*)element.offset);
            index++;
        }

        m_vertex_buffer.push_back(vertex_buffer);
    }

    void OpenGLVertexArray::set_index_buffer(const Ref<IndexBuffer>& index_buffer)
    {
        glBindVertexArray(m_renderer_id);
        index_buffer->bind();

        m_index_buffer = index_buffer;
    }
}
