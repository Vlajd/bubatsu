#include "bbzpch.h"
#include "OpenGLRenderApi.h"

#include <glad/glad.h>


namespace Bubatsu
{
    void OpenGLRenderApi::Init()
    {
        BBZ_PROFILE_FUNCTION();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderApi::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRenderApi::SetClearColor(const FVec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderApi::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderApi::DrawIndexed(const SRef<VertexArray>& vertexArray)
    {
        DrawIndexed(vertexArray, vertexArray->GetIndexBuffer()->GetCount());
    }
    void OpenGLRenderApi::DrawIndexed(const SRef<VertexArray>& vertexArray, uint32_t indexCount)
    {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}