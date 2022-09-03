#include "bbzpch.h"
#include "Texture.h"

#include "Bubatsu/Graphics/Core/Renderer.h"
#include "Impl/OpenGL/OpenGLTexture.h"


namespace Bubatsu
{
    SRef<Texture2D> Texture2D::Create(const String& path) 
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None: BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return NewSRef<OpenGLTexture2D>(path);
        }

        BBZ_CORE_ASSERT(true, "VertexArray::Unknown RenderApi!");
        return nullptr;
    }
}