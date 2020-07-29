#include "lypch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Lynton
{

	VertexBuffer* VertexBuffer::create(uint32_t size, float* vertices)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::open_gl:
            return new OpenGLVertexBuffer(size, vertices);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
    }

    IndexBuffer* IndexBuffer::create(uint32_t count, uint32_t* indices)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
                return nullptr;
        case RendererAPI::open_gl:
            return new OpenGLIndexBuffer(count, indices);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
                return nullptr;
        }
    }

}
