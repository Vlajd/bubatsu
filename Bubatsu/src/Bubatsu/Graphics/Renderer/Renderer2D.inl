namespace Bubatsu
{
    // ========================================================
    // Solid Color, no rotation
    // ========================================================
    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, FVec4 color)
    {
        DrawQuad(FVec3(position, 0.0f), size, color);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, FVec4 color)
    {
        DrawQuad(
            Scale(Translate(FMat4(1.0f), position), FVec3(size, 1.0f)),
            color
        );
    }

    // ========================================================
    // Solid Color, rotation
    // ========================================================
    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, color);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color)
    {
         DrawQuad(
            Scale(Rotate(Translate(FMat4(1.0f), position), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f)), FVec3(size, 1.0f)),
            color
        );
    }

    // ========================================================
    // Texture, no rotation
    // ========================================================
    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture, tint);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture, tiling);

    }

    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture, tiling, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture)
    {
        DrawQuad(position, size, texture, 1.0f, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, FVec4 tint)
    {
        DrawQuad(position, size, texture, 1.0f, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, float tiling)
    {
        DrawQuad(position, size, texture, tiling, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint)
    {
        DrawQuad(
            Scale(Translate(FMat4(1.0f), position), FVec3(size, 1.0f)),
            texture, tiling, tint
        );
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<Texture2D> texture, FVec4 tint, float tiling)
    {
        DrawQuad(position, size, texture, tiling, tint);
    }

    // ========================================================
    // Texture, rotation
    // ========================================================
    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture, tint);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture, tiling);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture, tiling, tint);
    }
    
    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture, tiling, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture)
    {
        DrawQuad(position, rotation, size, texture, 1.0f, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint)
    {
        DrawQuad(position, rotation, size, texture, 1.0f, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling)
    {
        DrawQuad(position, rotation, size, texture, tiling, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, float tiling, FVec4 tint)
    {
        DrawQuad(
            Scale(Rotate(Translate(FMat4(1.0f), position), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f)), FVec3(size, 1.0f)),
            texture, tiling, tint
        );
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<Texture2D> texture, FVec4 tint, float tiling)
    {
        DrawQuad(position, rotation, size, texture, tiling, tint);
    }

    // ========================================================
    // Texture
    // ========================================================
    inline void Renderer2D::DrawQuad(FMat4 transform, SRef<Texture2D> texture, FVec4 tint, float tiling)
    {
        DrawQuad(transform, texture, tiling, tint);
    }

    // ========================================================
    // SubTexture, no rotation
    // ========================================================
    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture)
    {
        DrawQuad(FVec3(position, 0.0f), size, subTexture);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), size, subTexture, tint);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), size, subTexture, tiling);

    }

    inline void Renderer2D::DrawQuad(FVec2 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), size, subTexture, tiling, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture)
    {
        DrawQuad(position, size, subTexture, 1.0f, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint)
    {
        DrawQuad(position, size, subTexture, 1.0f, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling)
    {
        DrawQuad(position, size, subTexture, tiling, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint)
    {
        DrawQuad(
            Scale(Translate(FMat4(1.0f), position), FVec3(size, 1.0f)),
            subTexture, tiling, tint
        );
    }

    inline void Renderer2D::DrawQuad(FVec3 position, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling)
    {
        DrawQuad(position, size, subTexture, tiling, tint);
    }

    // ========================================================
    // SubTexture, rotation
    // ========================================================
    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, subTexture);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, subTexture, tint);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, subTexture, tiling);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, subTexture, tiling, tint);
    }

    inline void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, subTexture, tiling, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture)
    {
        DrawQuad(position, rotation, size, subTexture, 1.0f, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint)
    {
        DrawQuad(position, rotation, size, subTexture, 1.0f, tint);
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling)
    {
        DrawQuad(position, rotation, size, subTexture, tiling, FVec4(1.0f));
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, float tiling, FVec4 tint)
    {
        DrawQuad(
            Scale(Rotate(Translate(FMat4(1.0f), position), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f)), FVec3(size, 1.0f)),
            subTexture, tiling, tint
        );
    }

    inline void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling)
    {
        DrawQuad(position, rotation, size, subTexture, tiling, tint);
    }

    // ========================================================
    // SubTexture
    // ========================================================
    inline void Renderer2D::DrawQuad(FMat4 transform, SRef<SubTexture2D> subTexture, FVec4 tint, float tiling)
    {
        DrawQuad(transform, subTexture, tiling, tint);
    }
}
