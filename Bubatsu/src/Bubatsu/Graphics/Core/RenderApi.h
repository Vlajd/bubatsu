#pragma once

#include "Bubatsu/Graphics/Core/VertexArray.h"
#include "Bubatsu/Core/Core.h"
#include "Bubatsu/Core/Math.h"


namespace Bubatsu
{
    class RenderApi
    {
    public:
        enum class Api
        {
            None = 0, OpenGL = 1
        };

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const FVec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const SRef<VertexArray>& vertexArray) = 0;

        inline static Api GetApi() { return m_Api; }

    private:
        static Api m_Api;
    };
}

