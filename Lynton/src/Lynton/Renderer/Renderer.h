#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

#include "OrthographicCamera.h"

namespace Lynton
{
    class OrthographicCamera;

    // create and render scenes using abstracted rendering api calls
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 view_projection_matrix;
		};

		static SceneData* s_scene_data;
	public:
		static void init();
		static void on_window_resize(uint32_t width, uint32_t height);

		static void begin_scene(OrthographicCamera& camera);

		static void end_scene();
		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API get_api() { return RendererAPI::get_api(); }
	};

}
