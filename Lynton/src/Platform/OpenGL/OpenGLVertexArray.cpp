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
        LY_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &m_renderer_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        LY_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_renderer_id);
    }

    void OpenGLVertexArray::bind() const
    {
        LY_PROFILE_FUNCTION();

        glBindVertexArray(m_renderer_id);
    }

    void OpenGLVertexArray::unbind() const
    {
        LY_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer)
    {
        LY_PROFILE_FUNCTION();

        glBindVertexArray(m_renderer_id);
        vertex_buffer->bind();

        LY_CORE_ASSERT(vertex_buffer->get_layout().get_elements().size(), "Vertex Buffer has no layout!")

        const auto& layout = vertex_buffer->get_layout();
        for (const auto& element : layout)
        {
            switch (element.type)
            {
            case ShaderDataType::float1:
            case ShaderDataType::float2:
            case ShaderDataType::float3:
            case ShaderDataType::float4:
            case ShaderDataType::int1:
            case ShaderDataType::int2:
            case ShaderDataType::int3:
            case ShaderDataType::int4:
            case ShaderDataType::bool1:
            {
                glEnableVertexAttribArray(m_vertex_buffer_index);
                glVertexAttribPointer(m_vertex_buffer_index,
                    element.get_component_count(),
                    shader_data_type_to_gl_enum(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    layout.get_stride(),
                    (const void*)element.offset);
                m_vertex_buffer_index++;
                break;
            }
            case ShaderDataType::mat3:
            case ShaderDataType::mat4:
            {
                uint8_t count = element.get_component_count();
                for (uint8_t i = 0; i < count; i++)
                {
                    glEnableVertexAttribArray(m_vertex_buffer_index);
                    glVertexAttribPointer(m_vertex_buffer_index,
                        count,
                        shader_data_type_to_gl_enum(element.type),
                        element.normalized ? GL_TRUE : GL_FALSE,
                        layout.get_stride(),
                        (const void*)(sizeof(float) * count * i));
                    glVertexAttribDivisor(m_vertex_buffer_index, 1);
                    m_vertex_buffer_index++;
                }
                break;
            }
            default:
                LY_CORE_ASSERT(false, "Unknown ShaderDataType!");
            }
        }

        m_vertex_buffer.push_back(vertex_buffer);
    }

    void OpenGLVertexArray::set_index_buffer(const Ref<IndexBuffer>& index_buffer)
    {
        LY_PROFILE_FUNCTION();

        glBindVertexArray(m_renderer_id);
        index_buffer->bind();

        m_index_buffer = index_buffer;
    }
}
