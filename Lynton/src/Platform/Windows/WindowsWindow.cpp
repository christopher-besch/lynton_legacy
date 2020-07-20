#include "lypch.h"
#include "WindowsWindow.h"

namespace Lynton
{
	static bool s_glfw_initialized = false;

	Window* Window::create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}
	
	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::init(const WindowProperties& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		LY_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_glfw_initialized)
		{
			// ToDo: glwfTerminate on system shutdown
			int success = glfwInit();
			LY_CORE_ASSERT(success, "Could not initialized GLFW!");

			s_glfw_initialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		set_vsync(true);
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::set_vsync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vsync = enabled;
	}
	
}
