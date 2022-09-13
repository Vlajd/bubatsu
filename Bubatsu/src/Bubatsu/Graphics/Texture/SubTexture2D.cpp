#include "bbzpch.h"
#include "SubTexture2D.h"


namespace Bubatsu
{
    SubTexture2D::SubTexture2D(SRef<Texture2D> texture, FVec2 min, FVec2 max)
        : m_Texture(texture)
    {
        m_TexCoords[0] = FVec2(min.x, min.y);
        m_TexCoords[1] = FVec2(max.x, min.y);
        m_TexCoords[2] = FVec2(max.x, max.y);
        m_TexCoords[3] = FVec2(min.x, max.y);
    }

    SRef<SubTexture2D> SubTexture2D::CreateFromCoords(SRef<Texture2D> texture, FVec2 coords, FVec2 cellSize, FVec2 spriteSize)
    {
        FVec2 min = FVec2((coords.x * cellSize.x) / texture->GetWidth(), (coords.y * cellSize.y) / texture->GetHeight());
        FVec2 max = FVec2(((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight());
        return NewSRef<SubTexture2D>(texture, min, max);
    }
}