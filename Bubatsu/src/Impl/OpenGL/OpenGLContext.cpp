#include "bbzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Bubatsu
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        BBZ_CORE_ASSERT(!windowHandle, "Window Handle Is Null!")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        BBZ_CORE_ASSERT(!status, "Failed To Inizialize Glad!");

        BBZ_CORE_INFO("OpenGL:");
        BBZ_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
        BBZ_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
        BBZ_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}