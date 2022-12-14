#pragma once

#include "Bubatsu/Graphics/Core/RenderApi.h"


namespace Bubatsu
{
    class BUBATSU_API OpenGLRenderApi : public RenderApi
    {
    public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual void SetClearColor(const FVec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const SRef<VertexArray>& vertexArray) override;
        virtual void DrawIndexed(const SRef<VertexArray>& vertexArray, uint32_t indexCount) override;
    };
}

