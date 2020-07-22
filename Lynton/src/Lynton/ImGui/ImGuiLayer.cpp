#include "lypch.h"
#include "ImGuiLayer.h"
#include "Lynton/Application.h"

#include "glad/glad.h"

#include "imgui.h"

// ToDo: temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace Lynton
{

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer") {}

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::on_attach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // temporary: should use Lynton key codes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::on_dettach()
    {
    }

    void ImGuiLayer::on_update()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::get();
        io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());

        auto time = (float)glfwGetTime();
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::on_event(Event& event)
    {
        // dispatch events
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_mouse_button_pressed_event));
        dispatcher.dispatch<MouseButtonReleasedEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_mouse_button_released_event));
        dispatcher.dispatch<MouseMovedEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_mouse_moved_event));
        dispatcher.dispatch<MouseScrolledEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_mouse_scrolled_event));

        dispatcher.dispatch<KeyPressedEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_key_pressed));
        dispatcher.dispatch<KeyReleasedEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_released_pressed));
        dispatcher.dispatch<KeyTypedEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_key_typed_event));

        dispatcher.dispatch<WindowResizedEvent>(LY_BIND_EVENT_FUNCTION(ImGuiLayer::on_window_resized_event));
    }

    bool ImGuiLayer::on_mouse_button_pressed_event(MouseButtonPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.get_mouse_button()] = true;

        // ToDo: hardcoded -> every event enters every other layer to, even when already handled
        return false;

    }

    bool ImGuiLayer::on_mouse_button_released_event(MouseButtonReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.get_mouse_button()] = false;

        // ToDo: hardcoded -> every event enters every other layer to, even when already handled
        return false;
    }

    bool ImGuiLayer::on_mouse_moved_event(MouseMovedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.get_x(), event.get_y());

        // ToDo: hardcoded -> every event enters every other layer to, even when already handled
        return false;
    }

    bool ImGuiLayer::on_mouse_scrolled_event(MouseScrolledEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += event.get_x();
        io.MouseWheel += event.get_y();

        // ToDo: hardcoded -> every event enters every other layer to, even when already handled
        return false;
    }

    bool ImGuiLayer::on_key_pressed(KeyPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.get_key_code()] = true;

        // set modifiers too
        io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::on_released_pressed(KeyReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.get_key_code()] = false;

        // set modifiers too
        io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::on_key_typed_event(KeyTypedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        int key_code = event.get_key_code();
        if (key_code > 0 && key_code < 0x10000)
            io.AddInputCharacter((unsigned int)key_code);

        return false;
    }

    bool ImGuiLayer::on_window_resized_event(WindowResizedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(event.get_width(), event.get_height());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        // ToDo: temporary
        glViewport(0, 0, event.get_width(), event.get_height());

        return false;
    }

}
