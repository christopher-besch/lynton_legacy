#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_map_width = 32;
static const char* s_map_tiles =
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWDDDDDDWWWWWWWWWWWWWWWW"
"WWWWWWWWWDDDDDDDDWWWWWWWWWWWWWWW"
"WWWWWWWWDDDDDDDDDDWWWWWWWWWWWWWW"
"WWWWWWWDDDDDDDDDDDDWWWWWWWWWWWWW"
"WWWWWWDDDDDDDDDDDDDDWWWWWWWWWWWW"
"WWWWWDDDDDDDDDDDDDDDDWWWWWWWWWWW"
"WWWWDDDDDDDDDDDDDDDDDDWWWWWWWWWW"
"WWWDDDDDDDDDDDDDDDDDDDDWWWWWWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDWWWWWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDWWWWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDWWWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDWWWWWDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDWWWWWWDDDDDDDDDDWWWW"
"WWDDDDDDDDWWWWWWWWDDDDDDDDDDWWWW"
"WWDDDDDDDDWWWWWWWWDDDDDDDDDDWWWW"
"WWDDDDDDDDWWWWWWWWDDDDDDDDDDWWWW"
"WWDDDDDDDDWWWWWWWWDDDDDDDDDDWWWW"
"WWDDDDDDDDWWWWWWWWDDDDDDDDDDWWWW"
"WWDDDDDDDDWWWWWWDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDWWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDDWWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDDDWWWWWWWWWWWWWWWWWW"
"WWDDDDDDDDDDDDDWWWWWWWWWWWWWWWWW"
"WWWDDDDDDDDDDDDDWWWWWWWWWWWWWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
static const uint32_t s_map_height = strlen(s_map_tiles) / s_map_width;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_camera_controller(1280.0f / 720.0f, true)
{
}

// ToDo: inline wrong blabla

void Sandbox2D::on_attach()
{
	LY_PROFILE_FUNCTION();

	m_checker_board_texture = Lynton::Texture2D::create("assets/textures/Checkerboard.png");
	m_sprite_sheet = Lynton::Texture2D::create("assets/game/textures/RPGpack_sheet_2X.png");

	m_stairs_texture = Lynton::SubTexture2D::create_from_coords(m_sprite_sheet, { 7, 6 }, { 128, 128 });
	m_barrel_texture = Lynton::SubTexture2D::create_from_coords(m_sprite_sheet, { 8, 2 }, { 128, 128 });
	m_tree_texture = Lynton::SubTexture2D::create_from_coords(m_sprite_sheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	m_texture_map['D'] = Lynton::SubTexture2D::create_from_coords(m_sprite_sheet, { 6, 11 }, { 128, 128 });
	m_texture_map['W'] = Lynton::SubTexture2D::create_from_coords(m_sprite_sheet, { 11, 11 }, { 128, 128 });

	m_particle_props.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_particle_props.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_particle_props.SizeBegin = 0.5f, m_particle_props.SizeVariation = 0.3f, m_particle_props.SizeEnd = 0.0f;
	m_particle_props.LifeTime = 5.0f;
	m_particle_props.Velocity = { 0.0f, 0.0f };
	m_particle_props.VelocityVariation = { 3.0f, 1.0f };
	m_particle_props.Position = { 0.0f, 0.0f };

	m_camera_controller.set_zoom_level(5.0f);

	Lynton::FrameBufferSpecification frame_buffer_spec;
	frame_buffer_spec.width = 1280;
	frame_buffer_spec.height = 720;
	m_frame_buffer = Lynton::FrameBuffer::create(frame_buffer_spec);
}

void Sandbox2D::on_detach()
{
	LY_PROFILE_FUNCTION();

	
}

void Sandbox2D::on_update(Lynton::TimeStep time_step)
{
	LY_PROFILE_FUNCTION();

	// update
	m_camera_controller.on_update(time_step);

	// render
	Lynton::Renderer2D::reset_stats();
    {
		LY_PROFILE_SCOPE("Render Prep");
		m_frame_buffer->bind();
        Lynton::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 0.0f });
	    Lynton::RenderCommand::clear();
    }

#if 0
    {
		LY_PROFILE_SCOPE("Render Draw");

		static float rotation = 0.0f;
		rotation += time_step * 50.0f;

        Lynton::Renderer2D::begin_scene(m_camera_controller.get_camera());
        Lynton::Renderer2D::draw_rotated_quad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Lynton::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Lynton::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Lynton::Renderer2D::draw_quad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_checker_board_texture, 10.0f);
		Lynton::Renderer2D::draw_rotated_quad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_checker_board_texture, 20.0f);
        Lynton::Renderer2D::end_scene();

		Lynton::Renderer2D::begin_scene((m_camera_controller.get_camera()));
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for ( float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f,  0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Lynton::Renderer2D::draw_quad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Lynton::Renderer2D::end_scene();

    }
#endif

	{
		LY_PROFILE_SCOPE("Particle System");


		if (Lynton::Input::is_mouse_button_pressed(LY_MOUSE_BUTTON_LEFT))
		{
			auto [x, y] = Lynton::Input::get_mouse_position();
			auto width = Lynton::Application::get().get_window().get_width();
			auto height = Lynton::Application::get().get_window().get_height();

			auto bounds = m_camera_controller.get_bounds();
			auto pos = m_camera_controller.get_camera().get_position();
			x = (x / width) * bounds.get_width() - bounds.get_width() * 0.5f;
			y = bounds.get_height() * 0.5f - (y / height) * bounds.get_height();
			m_particle_props.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 5; i++)
				m_particle_system.Emit(m_particle_props);
		}

		m_particle_system.OnUpdate(time_step);
		m_particle_system.OnRender(m_camera_controller.get_camera());

		Lynton::Renderer2D::begin_scene(m_camera_controller.get_camera());

		for (uint32_t y = 0; y < s_map_height; y++)
		{
		    for (uint32_t x = 0; x < s_map_width; x++)
		    {
				char tile_type = s_map_tiles[x + y * s_map_width];
				Lynton::Ref<Lynton::SubTexture2D> texture;

				if (m_texture_map.find(tile_type) != m_texture_map.end())
					texture = m_texture_map[tile_type];
				else
					texture = m_barrel_texture;

				Lynton::Renderer2D::draw_quad({ x * 0.1f, (s_map_height - y) * 0.1f, 0.5f }, { 0.1f, 0.1f }, texture);
		    }
		}

		// Lynton::Renderer2D::draw_quad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_stairs_texture);
		// Lynton::Renderer2D::draw_quad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_barrel_texture);
		// Lynton::Renderer2D::draw_quad({ -1.0f, 0.5f, 0.5f }, { 1.0f, 2.0f }, m_tree_texture);
		Lynton::Renderer2D::end_scene();
		m_frame_buffer->unbind();
	}
	
}

void Sandbox2D::on_event(Lynton::Event& event)
{
	m_camera_controller.on_event(event);

}

void Sandbox2D::on_imgui_render()
{
	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Lynton::Application::get().close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Lynton::Renderer2D::get_stats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.draw_calls);
		ImGui::Text("Quads: %d", stats.quad_count);
		ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
		ImGui::Text("Indices: %d", stats.get_total_index_count());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));

		uint32_t textureID = m_frame_buffer->get_color_attachment_renderer_id();
		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::Begin("Settings");

		auto stats = Lynton::Renderer2D::get_stats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.draw_calls);
		ImGui::Text("Quads: %d", stats.quad_count);
		ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
		ImGui::Text("Indices: %d", stats.get_total_index_count());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));

		uint32_t textureID = m_checker_board_texture->get_renderer_id();
		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
		ImGui::End();
	}
}
