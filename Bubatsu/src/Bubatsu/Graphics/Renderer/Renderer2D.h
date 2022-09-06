#pragma once

#include "Bubatsu/Graphics/Camera/OrthographicCamera.h"
#include "Bubatsu/Graphics/Core/VertexArray.h"
#include "Bubatsu/Graphics/Core/Shader.h"
#include "Bubatsu/Graphics/Core/Texture.h"
#include "Bubatsu/Core/Math.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color);
        static void DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture);

    private:
        struct Renderer2DData {
            SRef<Shader> Shader;
            SRef<Texture2D> EmptyTexture;
            SRef<VertexArray> QuadVA;
        };
        
        static URef<Renderer2DData> s_Data;
    };
}

