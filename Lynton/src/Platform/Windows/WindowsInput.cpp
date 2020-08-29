#include "lypch.h"
#include "Lynton/Core/Input.h"

#include "Lynton/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Lynton
{

    bool Input::is_key_pressed(KeyCode key)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());

        int state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::is_mouse_button_pressed(MouseCode button)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());

        int state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::get_mouse_position()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        return { (float)x_pos, (float)y_pos };
    }

    float Input::get_mouse_x()
    {
        auto [x, y] = get_mouse_position();
        return x;
    }

    float Input::get_mouse_y()
    {
        auto [x, y] = get_mouse_position();
        return y;
    }

}
