#pragma once

#include "Bubatsu/Graphics/Core/Buffer.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const SRef<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const SRef<IndexBuffer>& indexBuffer) = 0;

        virtual const Vector<SRef<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const SRef<IndexBuffer>& GetIndexBuffer() const = 0;

        static SRef<VertexArray> Create();
    };
}
