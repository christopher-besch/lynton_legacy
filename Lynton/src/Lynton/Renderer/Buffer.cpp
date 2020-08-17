// functions to create VertexBuffer and IndexBuffer instances for the currently used rendering api
#include "lypch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Lynton
{
    Ref<VertexBuffer> VertexBuffer::create(uint32_t size)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
                return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLVertexBuffer>(size);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
                return nullptr;
        }
    }

    Ref<VertexBuffer> VertexBuffer::create(uint32_t size, float* vertices)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLVertexBuffer>(size, vertices);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
    }

    Ref<IndexBuffer> IndexBuffer::create(uint32_t count, uint32_t* indices)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
                return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLIndexBuffer>(count, indices);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
                return nullptr;
        }
    }

}
