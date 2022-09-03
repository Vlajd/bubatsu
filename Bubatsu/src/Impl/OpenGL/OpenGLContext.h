#pragma once

#include "Bubatsu/Graphics/Core/Context.h"


// FORWARD
struct GLFWwindow;

namespace Bubatsu
{
    class BUBATSU_API OpenGLContext : public Context
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}

