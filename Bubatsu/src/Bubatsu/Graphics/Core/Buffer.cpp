#include "bbzpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Impl/OpenGL/OpenGLBuffer.h"


namespace Bubatsu
{
    SRef<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None: BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return NewSRef<OpenGLVertexBuffer>(size);
        }

        BBZ_CORE_ASSERT(true, "VertexBuffer::Unknown RenderApi!");
        return nullptr;
    }

    SRef<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None: BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return NewSRef<OpenGLVertexBuffer>(vertices, size);
        }

        BBZ_CORE_ASSERT(true, "VertexBuffer::Unknown RenderApi!");
        return nullptr;
    }

    SRef<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None:BBZ_CORE_ASSERT(true, "IndexBuffer::RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return NewSRef<OpenGLIndexBuffer>(indices, count);
        }

        BBZ_CORE_ASSERT(true, "IndexBuffer::Unknown RenderApi!");
        return nullptr;
    }
}