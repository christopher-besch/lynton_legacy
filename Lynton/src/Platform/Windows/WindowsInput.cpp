#include "lypch.h"
#include "WindowsInput.h"

#include "Lynton/Application.h"
#include <GLFW/glfw3.h>

namespace Lynton
{

    Input* Input::s_instance = new WindowsInput();

    bool WindowsInput::is_key_pressed_impl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());

        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::is_mouse_button_pressed_impl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());

        int state = glfwGetMouseButton(window, button);
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
