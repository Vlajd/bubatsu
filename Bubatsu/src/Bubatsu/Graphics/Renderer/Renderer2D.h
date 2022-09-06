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

        // Solid Color
        static void DrawQuad(FMat4 transform, FVec4 color); // prefered

        // Solid Color, no rotation
        static void DrawQuad(FVec2 position, FVec2 size, FVec4 color);
        static void DrawQuad(FVec3 position, FVec2 size, FVec4 color);

        // Solid Color, rotation
        static void DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color);

        // Texture
        static void DrawQuad(FMat4 transform, const SRef<Texture2D>& texture);
        static void DrawQuad(FMat4 transform, const SRef<Texture2D>& texture, FVec4 tint);
        static void DrawQuad(FMat4 transform, const SRef<Texture2D>& texture, float tiling);
        static void DrawQuad(FMat4 transform, const SRef<Texture2D>& texture, float tiling, FVec4 tint); // prefered

        // Texture, no rotation
        static void DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture);
        static void DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint);
        static void DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture, float tiling);
        static void DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint);
        static void DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture);
        static void DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint);
        static void DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture, float tiling);
        static void DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint);

        // Texture, rotation
        static void DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture);
        static void DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint);
        static void DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling);
        static void DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint);

    private:
        struct Renderer2DData {
            SRef<Shader> Shader;
            SRef<Texture2D> EmptyTexture;
            SRef<VertexArray> QuadVA;
        };
        
        static URef<Renderer2DData> s_Data;
    };
}

