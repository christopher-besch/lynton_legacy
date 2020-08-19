#include "lypch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lynton
{

	RendererAPI::API RendererAPI::s_api = RendererAPI::API::open_gl;

    Scope<RendererAPI> RendererAPI::create()
    {
        switch (s_api)
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
                return nullptr;
        case RendererAPI::API::open_gl:
            return create_scope<OpenGLRendererAPI>();
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
                return nullptr;
        }
    }

}
