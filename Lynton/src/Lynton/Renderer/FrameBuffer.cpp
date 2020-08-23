#include "lypch.h"
#include "FrameBuffer.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Lynton
{

    Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecification& spec)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLFrameBuffer>(spec);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
    }

}
