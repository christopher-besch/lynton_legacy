#include "lypch.h"

#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Lynton
{
    OpenGLContext::OpenGLContext(GLFWwindow* window_handle)
        : m_window_handle(window_handle)
    {
        LY_CORE_ASSERT(window_handle, "Window Handle is null")
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(m_window_handle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        LY_CORE_ASSERT(status, "Could not initialize Glad!")

        LY_CORE_INFO("OpenGL Info:");
        LY_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
        LY_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
        LY_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::swap_buffers()
    {
        glfwSwapBuffers(m_window_handle);
    }
}
