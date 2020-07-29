#pragma once

#include "Lynton/Renderer/Buffer.h"

namespace Lynton
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
    private:
        uint32_t m_renderer_id;
    public:
        OpenGLVertexBuffer(uint32_t size, float* vertices);
        virtual ~OpenGLVertexBuffer();

        virtual void bind() const override;
        virtual void unbind() const override;
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
