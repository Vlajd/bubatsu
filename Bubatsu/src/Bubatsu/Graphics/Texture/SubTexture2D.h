#pragma once

#include "Bubatsu/Graphics/Core/Texture.h"
#include "Bubatsu/Core/Math.h"


namespace Bubatsu
{
    class SubTexture2D
    {
    public:
        SubTexture2D(SRef<Texture2D> texture, FVec2 min, FVec2 max);

        const SRef<Texture2D> GetTexture() const { return m_Texture; }
        const FVec2* GetTexCoords() const { return m_TexCoords; }

        static SRef<SubTexture2D> CreateFromCoords(SRef<Texture2D> texture, FVec2 coords, FVec2 cellSize, FVec2 spriteSize = FVec2(1.0f));

    private:
        SRef<Texture2D> m_Texture;
        FVec2 m_TexCoords[4];
    };
}

