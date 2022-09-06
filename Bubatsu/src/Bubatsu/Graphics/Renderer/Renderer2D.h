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
        static void Flush();

        // Solid Color, no rotation
        static void DrawQuad(FVec2 position, FVec2 size, FVec4 color);
        static void DrawQuad(FVec3 position, FVec2 size, FVec4 color);

        // Solid Color, rotation
        static void DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color);
        static void DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color);

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
        struct QuadVertex
        {
            FVec3 Position;
            FVec4 Color;
            FVec2 TexCoord;
            float TexIndex;
            float Tiling;
        };
        
        struct Renderer2DData
        {
            static const uint32_t MAXQUADS = 8192;
            static const uint32_t MAXVERTICES = MAXQUADS * 4;
            static const uint32_t MAXINDICES = MAXQUADS * 6;
            static const uint32_t MAXTEXTURESLOTS = 32; // TODO: Render Capabilities
            SRef<Shader> Shader;
            SRef<Texture2D> EmptyTexture;
            SRef<VertexArray> QuadVertexArray;
            SRef<VertexBuffer> QuadVertexBuffer;
            uint32_t QuadIndexCount = 0;
            QuadVertex* QuadVertexBufferBase = nullptr;
            QuadVertex* QuadVertexBufferPtr = nullptr;
            Array<SRef<Texture2D>, MAXTEXTURESLOTS> TextureSlots;
            uint32_t TextureSlotIndex = 1; // 0 is EmptyTexture
            FVec4 QuadVertexPositions[4];
        };

        static Renderer2DData s_Data;
    };
}

