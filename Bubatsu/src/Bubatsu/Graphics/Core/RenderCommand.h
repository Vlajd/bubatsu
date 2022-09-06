#pragma once

#include "Bubatsu/Graphics/Core/RenderApi.h"
#include "Bubatsu/Graphics/Core/VertexArray.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    class RenderCommand
    {
    public:
        inline static void Init()
        {
            s_RenderApi->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_RenderApi->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const FVec4& color)
        {
            s_RenderApi->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_RenderApi->Clear();
        }

        inline static void DrawIndexed(const SRef<VertexArray>& vertexArray)
        {
            s_RenderApi->DrawIndexed(vertexArray);
        }

        inline static void DrawIndexed(const SRef<VertexArray>& vertexArray, uint32_t indexCount)
        {
            s_RenderApi->DrawIndexed(vertexArray, indexCount);
        }

    private:
        static SRef<RenderApi> s_RenderApi;
    };
}