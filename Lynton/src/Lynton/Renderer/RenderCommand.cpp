#include "lypch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lynton
{

	RendererAPI* RenderCommand::s_renderer_api = new OpenGLRendererAPI;

}
