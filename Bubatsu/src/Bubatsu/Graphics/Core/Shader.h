#pragma once

#include "Bubatsu/Core/Core.h"
#include "Bubatsu/Core/Math.h"


namespace Bubatsu
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const String& GetName() const = 0;
        virtual void SetInt(const String& name, int value) = 0;
        virtual void SetIntArray(const String& name, int* values, uint32_t count) = 0;
        virtual void SetFloat(const String& name, float value) = 0;
        virtual void SetFVec3(const String& name, FVec3 value) = 0;
        virtual void SetFVec4(const String& name, FVec4 value) = 0;
        virtual void SetFMat4(const String& name, FMat4 value) = 0;

        static SRef<Shader> Create(const String& filepath);
        static SRef<Shader> Create(const String& name, const String& vertexSrc, const String& fragmentSrc);
    };

    class ShaderLibrary
    {
    public:
        void Add(const SRef<Shader>& shader);
        void Add(const String& name, const SRef<Shader>& shader);
        SRef<Shader> Load(const String& filepath);
        SRef<Shader> Load(const String& name, const String& filepath);

        SRef<Shader> Get(const String& name);

        bool Exists(const String& name) const;
    private:
        std::unordered_map<String, SRef<Shader>> m_Shaders;
    };
}