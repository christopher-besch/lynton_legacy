#include "lypch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Lynton
{

    // create VertexArray instances for the currently used rendering api
	Ref<VertexArray> VertexArray::create()
	{
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::API::open_gl:
            return std::make_shared<OpenGLVertexArray>();
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
	}

}
