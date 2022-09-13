#pragma once

#include "Bubatsu/Graphics/Camera/OrthographicCamera.h"
#include "Bubatsu/Graphics/Core/VertexArray.h"
#include "Bubatsu/Graphics/Core/Shader.h"
#include "Bubatsu/Graphics/Core/Texture.h"
#include "Bubatsu/Graphics/Texture/SubTexture2D.h"
#include "Bubatsu/Core/Math.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    class Renderer2D
    {
    public:
        struct Statistics
        {
            uint32_t DrawCalls;
            uint32_t QuadCount;

            uint32_t GetVertexCount() { return QuadCount * 4; }
            uint32_t GetIndexCount() { return QuadCount * 6; }
        };

        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();

        // Solid Color, no rotation
        static inline void DrawQuad(FVec2 position, FVec2 size, FVec4 color);
        static inline void DrawQuad(FVec3 position, FVec2 size, FVec4 color);

        // Solid Color, rotation
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color);

        // Solid Color
        static void DrawQuad(FMat4 transform, FVec4 color);

        // Texture, no rotation
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture, FVec4 tint);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture, float tiling);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture, FVec4 tint, float tiling);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, FVec4 tint);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, float tiling);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, FVec4 tint, float tiling);

        // Texture, rotation
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint, float tiling);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint, float tiling);

        // Texture
        static void DrawQuad(FMat4 transform, const SRef<Texture2D> subTexture, float tiling, FVec4 tint);
        static inline void DrawQuad(FMat4 transform, const SRef<Texture2D> subTexture, FVec4 tint, float tiling);

        // SubTexture, no rotation
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling);

        // SubTexture, rotation
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint);
        static inline void DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling);

        // SubTexture
        static void DrawQuad(FMat4 transform, const SRef<SubTexture2D> subTexture, float tiling, FVec4 tint);
        static inline void DrawQuad(FMat4 transform, const SRef<SubTexture2D> subTexture, FVec4 tint, float tiling);

        static void ResetStatistics();
        static Statistics GetStatistics();
    private:
        static void FlushAndReset();

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
            static const uint32_t MAXQUADS = 8184;
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
            Statistics Stats;
        };

        static Renderer2DData s_Data;
    };
}

#include "Renderer2D.inl"

