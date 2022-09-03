#pragma once

#include "Bubatsu/Graphics/Core/VertexArray.h"
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

        virtual void AddVertexBuffer(const SRef<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const SRef<IndexBuffer>& indexBuffer) override;

        virtual const Vector<SRef<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
        virtual const SRef<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };

    private:
        uint32_t m_RendererID;
        Vector<SRef<VertexBuffer>> m_VertexBuffers;
        SRef<IndexBuffer> m_IndexBuffer;
    };
}

