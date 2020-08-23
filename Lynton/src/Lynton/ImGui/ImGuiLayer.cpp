#include "lypch.h"
#include "ImGuiLayer.h"
#include "Lynton/Core/Application.h"

#include "glad/glad.h"

// ToDo: temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

namespace Lynton
{

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer") {}

    void ImGuiLayer::on_attach()
    {
        LY_PROFILE_FUNCTION();

        // setup dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // enable keyboard controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // enable docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // enable multi-viewport / platform windows
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // setup dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // when viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.get_window().get_native_window());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::on_detach()
    {
        LY_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::on_event(Event& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        event.m_handled |= event.is_in_category(event_category_mouse) & io.WantCaptureMouse;
        event.m_handled |= event.is_in_category(event_category_keyboard) & io.WantCaptureKeyboard;
    }

    void ImGuiLayer::begin()
    {
        LY_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        LY_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::get();
        io.DisplaySize = ImVec2((float)app.get_window().get_width(), (float)app.get_window().get_height());

        // rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::on_imgui_render()
    {
    }


}
