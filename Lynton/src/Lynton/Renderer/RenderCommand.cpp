#include "lypch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lynton
{

	Scope<RendererAPI> RenderCommand::s_renderer_api = create_scope<OpenGLRendererAPI>();

}
