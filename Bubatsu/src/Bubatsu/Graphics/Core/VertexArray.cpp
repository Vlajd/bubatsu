#include "bbzpch.h"
#include "VertexArray.h"

#include "Bubatsu/Graphics/Core/Renderer.h"

#include "Impl/OpenGL/OpenGLVertexArray.h"


namespace Bubatsu
{
    SRef<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None: BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return NewSRef<OpenGLVertexArray>();
        }

        BBZ_CORE_ASSERT(true, "VertexArray::Unknown RendererAPI!");
        return nullptr;
    }
}

