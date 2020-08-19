// functions to create VertexBuffer and IndexBuffer instances for the currently used rendering api
#include "lypch.h"
#include "GraphicsContext.h"

#include "Lynton/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Lynton
{
    Scope<GraphicsContext> GraphicsContext::create(void* window)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::API::open_gl:
            return create_scope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
    }

}
