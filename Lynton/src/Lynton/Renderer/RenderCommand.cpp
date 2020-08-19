#include "lypch.h"
#include "RenderCommand.h"

namespace Lynton
{

	Scope<RendererAPI> RenderCommand::s_renderer_api = RendererAPI::create();

}
