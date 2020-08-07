#include "lypch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lynton
{

    // create Texture2D instances for the currently used rendering api
	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
                return nullptr;
        case RendererAPI::API::open_gl:
            return std::make_shared<OpenGLTexture2D>(path);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
                return nullptr;
        }
	}

}
