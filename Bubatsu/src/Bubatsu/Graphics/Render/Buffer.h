#pragma once

#include "Bubatsu/Core/Core.h"


namespace Bubatsu {

    enum class DataType
    {
        None = 0, Float, FVec2, FVec3, FVec4, FMat2, FMat3, FMat4, Int, IVec2, IVec3, IVec4, IMat2, IMat3, IMat4, Bool
    };

    static uint32_t DataTypeSize(DataType type) {

        switch (type)
        {
        case DataType::Float:	return  4;
        case DataType::FVec2:	return  8;
        case DataType::FVec3:	return 12;
        case DataType::FVec4:	return 16;
        case DataType::FMat2:	return 16;
        case DataType::FMat3:	return 36;
        case DataType::FMat4:	return 64;
        case DataType::Int:	    return  4;
        case DataType::IVec2:	return  8;
        case DataType::IVec3:	return 12;
        case DataType::IVec4:	return 16;
        case DataType::IMat2:	return 16;
        case DataType::IMat3:	return 36;
        case DataType::IMat4:	return 64;
        case DataType::Bool:	return  1;
        }

        BBZ_CORE_ASSERT(true, "DataTypeSize::Unknown DataType!");
        return 0;
    }

    struct BufferElement
    {
        String Name;
        DataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement(DataType type, const String& name, bool normalized = false)
            : Name(name), Type(type), Size(DataTypeSize(type)), Offset(0), Normalized(normalized) {}

        uint32_t GetComponentCount() const {

            switch (Type)
            {
            case DataType::Float:	return  1;
            case DataType::FVec2:	return  2;
            case DataType::FVec3:	return  3;
            case DataType::FVec4:	return  4;
            case DataType::FMat2:	return  4;
            case DataType::FMat3:	return  9;
            case DataType::FMat4:	return 16;
            case DataType::Int:  	return  1;
            case DataType::IVec2:	return  2;
            case DataType::IVec3:	return  3;
            case DataType::IVec4:	return  4;
            case DataType::IMat2:	return  4;
            case DataType::IMat3:	return  9;
            case DataType::IMat4:	return 16;
            case DataType::Bool:	return  1;
            }

            BBZ_CORE_ASSERT(true, "GetComponentCount::Unknown DataType!");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& element)
            : m_Elements(element) {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_Stride; }
        inline const Vector<BufferElement>& GetElements() const { return m_Elements; }

        Vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        Vector<BufferElement>::iterator end() { return m_Elements.end(); }
        Vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        Vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        Vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;

        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t size);
    };
}