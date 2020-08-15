#include "lypch.h"
#include "WindowsWindow.h"

#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Events/MouseEvent.h"
#include "Lynton/Events/KeyEvent.h"
#include "Lynton/Core/Core.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Lynton
{
	static uint8_t s_glfw_window_count = 0;

	static void glfw_error_callback(int error, const char* description)
	{
		LY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}
	
	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		LY_PROFILE_FUNCTION();

		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		LY_PROFILE_FUNCTION();

		shutdown();
	}

	void WindowsWindow::init(const WindowProperties& props)
	{
		LY_PROFILE_FUNCTION();

		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		LY_CORE_INFO("Creating window \"{0}\" ({1}, {2})", props.title, props.width, props.height);

		if (s_glfw_window_count == 0)
		{
			LY_PROFILE_SCOPE("glfwInit");

			LY_CORE_INFO("Initiated GLFW");
			int success = glfwInit();
			LY_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(glfw_error_callback);
		}

	    {
			LY_PROFILE_SCOPE("glfwCreateWindow");

	        m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		    ++s_glfw_window_count;
	    }

		m_context = create_scope<OpenGLContext>(m_window);
		// includes make context current stuff
		m_context->init();

		glfwSetWindowUserPointer(m_window, &m_data);
		set_vsync(true);

		// set glfw callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
			    // 1. get m_data from the used WindowsWindow
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

			    // 2. create sensible event
				WindowResizedEvent event(width, height);
			    // 3. call callback with that event
				data.event_callback(event);
			});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.event_callback(event);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scan_code, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch(action)
				{
					case GLFW_PRESS:
					{
					    KeyPressedEvent event(key, 0);
					    data.event_callback(event);
					    break;
					}
					case GLFW_RELEASE:
					{
					    KeyReleasedEvent event(key);
					    data.event_callback(event);
					    break;
					}
					case GLFW_REPEAT:
					{
					    //                         <- should actually be variable but glfw doesn't support that
					    KeyPressedEvent event(key, 1);
					    data.event_callback(event);
					    break;
					}
					default:
					{
					    LY_CORE_ASSERT(false, "glfwSetKeyCallback() produced unsupported key action")
					    break;
					}
				}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int character)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(character);
				data.event_callback(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
					{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.event_callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.event_callback(event);
						break;
					}
					default:
					{
						LY_CORE_ASSERT(false, "glfwSetMouseButtonCallback() produced unsupported button action")
						break;
					}
				}
			});
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double offset_x, double offset_y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)offset_x, (float)offset_y);
				data.event_callback(event);
			});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double position_x, double position_y)
		{
	        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)position_x, (float)position_y);
			data.event_callback(event);
		});
	}

	void WindowsWindow::shutdown()
	{
		LY_PROFILE_FUNCTION();

		glfwDestroyWindow(m_window);
		s_glfw_window_count -= 1;
		if (s_glfw_window_count == 0)
		{
			LY_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void WindowsWindow::on_update()
	{
		LY_PROFILE_FUNCTION();

		glfwPollEvents();
		m_context->swap_buffers();
	}

	void WindowsWindow::set_vsync(bool enabled)
	{
		LY_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vsync = enabled;
	}
	
}
