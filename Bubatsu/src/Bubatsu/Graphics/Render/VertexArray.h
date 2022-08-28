#pragma once

#include "Buffer.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const SPtr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const SPtr<IndexBuffer>& indexBuffer) = 0;

		virtual const Vector<SPtr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const SPtr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}
