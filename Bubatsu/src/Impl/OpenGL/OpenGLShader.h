#pragma once

#include "Bubatsu/Graphics/Core/Shader.h"
#include "Bubatsu/Core/Math.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    typedef unsigned int GLenum;

    class BUBATSU_API OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const String& filepath);
        OpenGLShader(const String& name, const String& vertexSrc, const String& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const String& GetName() const override { return m_Name; }
        virtual void SetInt(const String& name, int value) override;
        virtual void SetIntArray(const String& name, int* values, uint32_t count) override;
        virtual void SetFloat(const String& name, float value) override;
        virtual void SetFVec3(const String& name, FVec3 value) override;
        virtual void SetFVec4(const String& name, FVec4 value) override;
        virtual void SetFMat4(const String& name, FMat4 value) override;

        void UploadUniformInt(const String& name, int value);
        void UploadUniformIntArray(const String& name, int* values, uint32_t count);
        void UploadUniformIVec2(const String& name, const IVec2& values);
        void UploadUniformIVec3(const String& name, const IVec3& values);
        void UploadUniformIVec4(const String& name, const IVec4& values);

        void UploadUniformFloat(const String& name, float value);
        void UploadUniformFVec2(const String& name, const FVec2& values);
        void UploadUniformFVec3(const String& name, const FVec3& values);
        void UploadUniformFVec4(const String& name, const FVec4& values);
        void UploadUniformFMat2(const String& name, const FMat2& matrix);
        void UploadUniformFMat3(const String& name, const FMat3& matrix);
        void UploadUniformFMat4(const String& name, const FMat4& matrix);

    private:
        String ReadFile(const String& filepath);
        std::unordered_map<GLenum, String> PreProcess(const String& source);
        void Compile(const std::unordered_map<GLenum, String>& shaderSources);

        uint32_t m_RendererID;
        String m_Name;
    };
}