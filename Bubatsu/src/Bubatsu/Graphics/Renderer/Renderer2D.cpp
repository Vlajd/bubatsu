#include "bbzpch.h"
#include "Renderer2D.h"

#include "Bubatsu/Graphics/Core/RenderCommand.h"


namespace Bubatsu
{
    Renderer2D::Renderer2DData Renderer2D::s_Data;

    void Renderer2D::Init()
    {
        BBZ_PROFILE_FUNCTION();

        // data struct init
        s_Data.QuadVertexArray = VertexArray::Create();

        // vertex buffer
        s_Data.QuadVertexBuffer = VertexBuffer::Create(Renderer2DData::MAXVERTICES * sizeof(QuadVertex));
        s_Data.QuadVertexBuffer->SetLayout({
            { DataType::FVec3, "a_Position" },
            { DataType::FVec4, "a_Color" },
            { DataType::FVec2, "a_TexCoord" },
            { DataType::Float, "a_Texture" },
            { DataType::Float, "a_Tiling" },
        });
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
        s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MAXVERTICES];

        // index buffer
        uint32_t* quadIndices = new uint32_t[Renderer2DData::MAXINDICES];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < s_Data.MAXINDICES; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        SRef<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, Renderer2DData::MAXINDICES);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;

        // empty texture
        s_Data.EmptyTexture = Texture2D::Create(1, 1);
        uint32_t emptyTextureData = 0xffffffff;
        s_Data.EmptyTexture->SetData(&emptyTextureData, sizeof(uint32_t));

        int32_t samplers[Renderer2DData::MAXTEXTURESLOTS];
        for (uint32_t i = 0; i < Renderer2DData::MAXTEXTURESLOTS; i++)
        {
            samplers[i] = i;
        }


        s_Data.Shader = Shader::Create("Assets/Shaders/Texture.glsl");
        s_Data.Shader->Bind();
        s_Data.Shader->SetIntArray("u_Textures", samplers, Renderer2DData::MAXTEXTURESLOTS);


        s_Data.TextureSlots[0] = s_Data.EmptyTexture;

        s_Data.QuadVertexPositions[0] = FVec4(-0.5f, -0.5f, 0.0f, 1.0f);
        s_Data.QuadVertexPositions[1] = FVec4( 0.5f, -0.5f, 0.0f, 1.0f);
        s_Data.QuadVertexPositions[2] = FVec4( 0.5f,  0.5f, 0.0f, 1.0f);
        s_Data.QuadVertexPositions[3] = FVec4(-0.5f,  0.5f, 0.0f, 1.0f);
    }

    void Renderer2D::Shutdown()
    {
        BBZ_PROFILE_FUNCTION();

        delete[] s_Data.QuadVertexBufferBase;
    }

    // ========================================================
    // Inside RunLoop
    // ========================================================
    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        BBZ_PROFILE_FUNCTION();

        s_Data.Shader->Bind();
        s_Data.Shader->SetFMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1; // 0 is EmptyTexture

        ResetStatistics();
    }

    void Renderer2D::EndScene()
    {
        BBZ_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        BBZ_PROFILE_FUNCTION();

        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
            s_Data.TextureSlots[i]->Bind(i);
        }
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

        s_Data.Stats.DrawCalls++;
    }

    void Renderer2D::FlushAndReset()
    {
        EndScene();

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
        s_Data.TextureSlotIndex = 1; // 0 is EmptyTexture
    }


    // ========================================================
    // Solid color, no rotation
    // ========================================================
    void Renderer2D::DrawQuad(FVec2 position, FVec2 size, FVec4 color)
    {
        DrawQuad(FVec3(position, 0.0f), size, color);
    }

    void Renderer2D::DrawQuad(FVec3 position, FVec2 size, FVec4 color)
    {
        BBZ_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= Renderer2DData::MAXINDICES)
        {
            FlushAndReset();
        }

        s_Data.QuadVertexBufferPtr->Position = position;
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f; // 0 is EmptyTexture
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = FVec3(position.x + size.x, position.y, position.z);
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = FVec3(position.x + size.x, position.y + size.y, position.z);
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = FVec3(position.x, position.y + size.y, position.z);
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;


        s_Data.QuadIndexCount += 6;
        s_Data.Stats.QuadCount++;
    }


    // ========================================================
    // Solid color, rotation
    // ========================================================
    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, color);
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color)
    {
        BBZ_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= Renderer2DData::MAXINDICES)
        {
            FlushAndReset();
        }

        FMat4 transform = Translate(FMat4(1.0f), position)
                          * Rotate(FMat4(1.0f), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f))
                          * Scale(FMat4(1.0f), FVec3(size, 1.0f));

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f; // 0 is EmptyTexture
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
        s_Data.QuadVertexBufferPtr->Tiling = 1.0f;
        s_Data.QuadVertexBufferPtr++;


        s_Data.QuadIndexCount += 6;
        s_Data.Stats.QuadCount++;
    }


    // ========================================================
    // Texture
    // ========================================================
    void Renderer2D::DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture);
    }

    void Renderer2D::DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture, tint);
    }

    void Renderer2D::DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture, tiling);
    }

    void Renderer2D::DrawQuad(FVec2 position, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), size, texture, tiling, tint);
    }

    void Renderer2D::DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture)
    {
        DrawQuad(position, size, texture, 1.0f, FVec4(1.0f));
    }

    void Renderer2D::DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint)
    {
        DrawQuad(position, size, texture, 1.0f, tint);
    }

    void Renderer2D::DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture, float tiling)
    {
        DrawQuad(position, size, texture, tiling, FVec4(1.0f));
    }

    void Renderer2D::DrawQuad(FVec3 position, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint)
    {
        BBZ_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= Renderer2DData::MAXINDICES)
        {
            FlushAndReset();
        }

        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) // 0 is EmptyTexture
        {
            if (*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        s_Data.QuadVertexBufferPtr->Position = position;
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = FVec3(position.x + size.x, position.y, position.z);
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = FVec3(position.x + size.x, position.y + size.y, position.z);
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = FVec3(position.x, position.y + size.y, position.z);
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;


        s_Data.QuadIndexCount += 6;
        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture);
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture, tint);
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture, tiling);
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture, tiling, tint);
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture)
    {
        DrawQuad(position, rotation, size, texture, 1.0f, FVec4(1.0f));
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, FVec4 tint)
    {
        DrawQuad(position, rotation, size, texture, 1.0f, tint);
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling)
    {
        DrawQuad(position, rotation, size, texture, tiling, FVec4(1.0f));
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture, float tiling, FVec4 tint)
    {
        BBZ_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= Renderer2DData::MAXINDICES)
        {
            FlushAndReset();
        }

        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) // 0 is EmptyTexture
        {
            if (*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        FMat4 transform = Translate(FMat4(1.0f), position)
                          * Rotate(FMat4(1.0f), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f))
                          * Scale(FMat4(1.0f), FVec3(size, 1.0f));


        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(1.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = FVec2(0.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->Tiling = tiling;
        s_Data.QuadVertexBufferPtr++;


        s_Data.QuadIndexCount += 6;
        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::ResetStatistics()
    {
        s_Data.Stats.DrawCalls = 0;
        s_Data.Stats.QuadCount = 0;
    }

    Renderer2D::Statistics Renderer2D::GetStatistics()
    {
        return s_Data.Stats;
    }
}

