#include "bbzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>


namespace Bubatsu
{
    static GLenum ShaderDataTypeToOpenGLBaseType(DataType type)
    {
        switch (type) {
        case DataType::Float:	return GL_FLOAT;
        case DataType::FVec2:	return GL_FLOAT;
        case DataType::FVec3:	return GL_FLOAT;
        case DataType::FVec4:	return GL_FLOAT;
        case DataType::FMat2:	return GL_FLOAT;
        case DataType::FMat3:	return GL_FLOAT;
        case DataType::FMat4:	return GL_FLOAT;
        case DataType::Int:		return GL_INT;
        case DataType::IVec2:	return GL_INT;
        case DataType::IVec3:	return GL_INT;
        case DataType::IVec4:	return GL_INT;
        case DataType::IMat2:	return GL_INT;
        case DataType::IMat3:	return GL_INT;
        case DataType::IMat4:	return GL_INT;
        case DataType::Bool:	return GL_BOOL;
        }

        BBZ_CORE_ASSERT(true, "DataTypeToOpenGLBaseType::Unknown DataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(NULL);
    }

    void OpenGLVertexArray::AddVertexBuffer(const SPtr<VertexBuffer>& vertexBuffer)
    {
        BBZ_CORE_ASSERT(!vertexBuffer->GetLayout().GetElements().size(), "OpenGLVertexArray::AddVertexBuffer::Vertex Buffer Has No Layout")

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();// glVertexAttribPointer
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);

            glVertexAttribPointer(
                index,											// glVertexAttribPointer
                element.GetComponentCount(),					// glVertexAttribPointer
                ShaderDataTypeToOpenGLBaseType(element.Type),	// glVertexAttribPointer
                element.Normalized ? GL_TRUE : GL_FALSE,		// glVertexAttribPointer
                layout.GetStride(),								// glVertexAttribPointer
                (const void*)element.Offset						// glVertexAttribPointer
            );													// glVertexAttribPointer

            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const SPtr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}

