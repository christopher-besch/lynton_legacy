#include "lypch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lynton
{
    Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
                return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLTexture2D>(width, height);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
                return nullptr;
        }
    }

    // create Texture2D instances for the currently used rendering api
	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
                return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLTexture2D>(path);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
                return nullptr;
        }
	}

}
