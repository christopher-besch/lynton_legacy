#include "lypch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Lynton
{

	VertexArray* VertexArray::create()
	{
        switch (Renderer::get_api())
        {
        case RendererAPI::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::open_gl:
            return new OpenGLVertexArray();
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
	}

}
