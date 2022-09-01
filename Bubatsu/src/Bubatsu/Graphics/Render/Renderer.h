#pragma once

#include "Bubatsu/Graphics/Render/Shader.h"
#include "Bubatsu/Graphics/Render/RenderCommand.h"
#include "Bubatsu/Graphics/Camera/OrthographicCamera.h"


namespace Bubatsu
{
    class Renderer
    {
    public:
        static void Init();

        static void OnWindowResized(uint32_t width, uint32_t height);

        static void BeginScene(OrthographicCamera& camera); // [TODO] Get other Params
        static void EndScene();

        // Implemented by correspondin API
        static void Submit(const SPtr<Shader>& shader, const SPtr<VertexArray>& vertexArray, const FMat4& transform = FMat4(1.0f));

        inline static RenderApi::Api GetApi()
        {
            return RenderApi::GetApi();
        }

    private:
        struct SceneData
        {
            FMat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
}