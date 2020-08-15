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
        LY_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_window_handle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        LY_CORE_ASSERT(status, "Could not initialize Glad!")

        LY_CORE_INFO("OpenGL Info:");
        LY_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
        LY_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
        LY_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));

        #ifdef LY_ENABLE_ASSERTS
            int versionMajor;
            int versionMinor;
            glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
            glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

            LY_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Lynton requires at least OpenGL version 4.5!");
        #endif
    }

    void OpenGLContext::swap_buffers()
    {
        LY_PROFILE_FUNCTION();

        glfwSwapBuffers(m_window_handle);
    }
}
