#include "lypch.h"
#include "WindowsInput.h"

#include "Lynton/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Lynton
{

    bool WindowsInput::is_key_pressed_impl(KeyCode key)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());

        int state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::is_mouse_button_pressed_impl(MouseCode button)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());

        int state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    float WindowsInput::get_mouse_x_impl()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        return (float)x_pos;
    }

    float WindowsInput::get_mouse_y_impl()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        return (float)y_pos;
    }

    std::pair<float, float> WindowsInput::get_mouse_position_impl()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        return { x_pos, y_pos };

        // as of C++ 17 this is possible:
        // auto [x, y] = get_mouse_position_impl();
    }

}
