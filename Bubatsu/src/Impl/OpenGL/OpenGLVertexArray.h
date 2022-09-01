#pragma once

#include "Bubatsu/Graphics/Render/VertexArray.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    class BUBATSU_API OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();

        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const SPtr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const SPtr<IndexBuffer>& indexBuffer) override;

        virtual const Vector<SPtr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
        virtual const SPtr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };

    private:
        uint32_t m_RendererID;
        Vector<SPtr<VertexBuffer>> m_VertexBuffers;
        SPtr<IndexBuffer> m_IndexBuffer;
    };
}

