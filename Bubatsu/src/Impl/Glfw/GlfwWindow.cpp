#include "bbzpch.h"
#include "GlfwWindow.h"

#include "Bubatsu/Event/ApplicationEvent.h"
#include "Bubatsu/Event/KeyboardEvent.h"
#include "Bubatsu/Event/MouseButtonEvent.h"
#include "Bubatsu/Event/MouseEvent.h"
#include "Bubatsu/Event/WindowEvent.h"
#include "Impl/OpenGL/OpenGLContext.h"


namespace Bubatsu
{
    unsigned short GlfwWindow::s_WindowCount;

    static void GLFWErrorCallback(int error, const char* description)
    {
        BBZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    URef<Window> Window::Create(const WindowProperties& properties)
    {
        return NewURef<GlfwWindow>(properties);
    }

    GlfwWindow::GlfwWindow(const WindowProperties& properties)
    {
        BBZ_PROFILE_FUNCTION();

        Init(properties);
    }

    GlfwWindow::~GlfwWindow()
    {
        BBZ_PROFILE_FUNCTION();

        ShutDown();
    }

    void GlfwWindow::Init(const WindowProperties& properties)
    {
        BBZ_PROFILE_FUNCTION();

        m_Data.Title = properties.Title;
        m_Data.Width = properties.Width;
        m_Data.Height = properties.Height;
        s_WindowCount = 0;

        BBZ_CORE_INFO("Creating window ({0}) ({1}, {2})", properties.Title, properties.Width, properties.Height);

        if (s_WindowCount == 0)
        {
            BBZ_PROFILE_SCOPE("GlfwWindow::Init(const WindowProperties&) > glfwInit");

            int success = glfwInit();
            BBZ_CORE_ASSERT(!success, "Could Not Initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            BBZ_PROFILE_SCOPE("GlfwWindow::Init(const WindowProperties&) > glfwCreateWindow");

            m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
            s_WindowCount++;
        }

        m_Context = NewURef<OpenGLContext>(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;

            WindowResizedEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowClosedEvent event(event);
            data.EventCallback(event);
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyboardTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyboardPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyboardReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyboardPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);

        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    void GlfwWindow::ShutDown()
    {
        BBZ_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Window);
    }

    void GlfwWindow::OnUpdate()
    {
        BBZ_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void GlfwWindow::SetVSync(bool enabled)
    {
        BBZ_PROFILE_FUNCTION();

        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }

    bool GlfwWindow::GetVSyncEnabled() const
    {
        return m_Data.VSync;
    }
}

