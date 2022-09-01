#include "bbzpch.h"
#include "VertexArray.h"

#include "Bubatsu/Graphics/Render/Renderer.h"

#include "Impl/OpenGL/OpenGLVertexArray.h"


namespace Bubatsu
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None: BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return new OpenGLVertexArray();
        }

        BBZ_CORE_ASSERT(true, "VertexArray::Unknown RendererAPI!");
        return nullptr;
    }
}

