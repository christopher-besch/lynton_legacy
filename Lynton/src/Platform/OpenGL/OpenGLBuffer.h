#pragma once

#include "Lynton/Renderer/Buffer.h"

namespace Lynton
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
    private:
        uint32_t m_renderer_id;
        BufferLayout m_layout;
    public:
        OpenGLVertexBuffer(uint32_t size, float* vertices);
        virtual ~OpenGLVertexBuffer();

        virtual void bind() const override;
        virtual void unbind() const override;

        inline virtual void set_layout(const BufferLayout& layout) override { m_layout = layout; };
        inline virtual const BufferLayout& get_layout() const override { return m_layout; };
    };


    class OpenGLIndexBuffer : public IndexBuffer
    {
    private:
        uint32_t m_renderer_id;
        uint32_t m_count;
    public:
        OpenGLIndexBuffer(uint32_t count, uint32_t* indices);
        virtual ~OpenGLIndexBuffer();

        inline virtual uint32_t get_count() const override { return m_count; }

        virtual void bind() const override;
        virtual void unbind() const override;
    };
    
}
