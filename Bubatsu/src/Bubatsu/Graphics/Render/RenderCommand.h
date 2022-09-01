#pragma once

#include "Bubatsu/Graphics/Render/RenderApi.h"
#include "Bubatsu/Graphics/Render/VertexArray.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    class RenderCommand
    {
    public:
        inline static void Init()
        {
            m_RenderApi->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            m_RenderApi->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const FVec4& color)
        {
            m_RenderApi->SetClearColor(color);
        }

        inline static void Clear()
        {
            m_RenderApi->Clear();
        }

        inline static void DrawIndexed(const SPtr<VertexArray>& vertexArray)
        {
            m_RenderApi->DrawIndexed(vertexArray);
        }

    private:
        static RenderApi* m_RenderApi;
    };
}