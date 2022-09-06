#include "bbzpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>


namespace Bubatsu
{
    static GLenum ShaderTypeFromString(const String& type)
    {
        BBZ_PROFILE_FUNCTION();

        if (type == "vertex")
        {
            return GL_VERTEX_SHADER;
        }
        if (type == "fragment" || type == "pixel")
        {
            return GL_FRAGMENT_SHADER;
        }

        BBZ_CORE_ASSERT(false, "Unknown Shader Type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const String& filepath)
    {
        BBZ_PROFILE_FUNCTION();

        String source = ReadFile(filepath);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);

        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind(".");
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const String& name, const String& vertexSrc, const String& fragmentSrc)
        : m_Name(name)
    {
        BBZ_PROFILE_FUNCTION();
        
        std::unordered_map<GLenum, String> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        BBZ_PROFILE_FUNCTION();

        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        BBZ_PROFILE_FUNCTION();

        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        BBZ_PROFILE_FUNCTION();

        glUseProgram(NULL);
    }

    void OpenGLShader::SetInt(const String& name, int value)
    {
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetIntArray(const String& name, int* values, uint32_t count)
    {
        UploadUniformIntArray(name, values, count);
    }

    void OpenGLShader::SetFloat(const String& name, float value)
    {
        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFVec3(const String& name, FVec3 value)
    {
        UploadUniformFVec3(name, value);
    }

    void OpenGLShader::SetFVec4(const String& name, FVec4 value)
    {
        UploadUniformFVec4(name, value);
    }

    void OpenGLShader::SetFMat4(const String& name, FMat4 value)
    {
        UploadUniformFMat4(name, value);
    }

    void OpenGLShader::UploadUniformInt(const String& name, int value)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformIntArray(const String& name, int* values, uint32_t count)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, count, values);
    }

    void OpenGLShader::UploadUniformIVec2(const String& name, const IVec2& values)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2i(location, values.x, values.y);
    }

    void OpenGLShader::UploadUniformIVec3(const String& name, const IVec3& values)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3i(location, values.x, values.y, values.z);
    }

    void OpenGLShader::UploadUniformIVec4(const std::string& name, const IVec4& values)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4i(location, values.x, values.y, values.z, values.w);
    }

    void OpenGLShader::UploadUniformFloat(const String& name, float value)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFVec2(const String& name, const FVec2& values)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, values.x, values.y);
    }

    void OpenGLShader::UploadUniformFVec3(const String& name, const FVec3& values)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, values.x, values.y, values.z);
    }

    void OpenGLShader::UploadUniformFVec4(const std::string& name, const FVec4& values)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, values.x, values.y, values.z, values.w);
    }

    void OpenGLShader::UploadUniformFMat2(const String& name, const FMat2& matrix)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix2fv(location, 1, GL_FALSE, RawValuePtr(matrix));
    }

    void OpenGLShader::UploadUniformFMat3(const String& name, const FMat3& matrix)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, RawValuePtr(matrix));
    }

    void OpenGLShader::UploadUniformFMat4(const String& name, const FMat4& matrix)
    {
        BBZ_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, RawValuePtr(matrix));
    }

    String OpenGLShader::ReadFile(const String& filepath)
    {
        BBZ_PROFILE_FUNCTION();

        String result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            BBZ_CORE_ERROR("Could Not Open File '{}'", filepath);
            BBZ_CORE_ASSERT(true, "");
        }

        return result;
    }

    std::unordered_map<GLenum, String> OpenGLShader::PreProcess(const String& source)
    {
        BBZ_PROFILE_FUNCTION();

        std::unordered_map<GLenum, String> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != String::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            BBZ_CORE_ASSERT(eol == std::string::npos, "Shader Syntax Error");
            size_t begin = pos + typeTokenLength + 1;
            String type = source.substr(begin, eol - begin);
            BBZ_CORE_ASSERT(!ShaderTypeFromString(type), "Invalid Shader Type Specification!");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, String>& shaderSources)
    {
        BBZ_PROFILE_FUNCTION();

        GLuint program = glCreateProgram();
        BBZ_CORE_ASSERT(shaderSources.size() > 2, "Only 2 Shaders Supported");
        std::array<GLenum, 2 /*Shader Count*/> glShaderIDs;
        int glShaderIDIndex = 0;
        m_RendererID = glCreateProgram();

        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const String& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                BBZ_CORE_ERROR("{0}", infoLog.data());
                BBZ_CORE_ASSERT(true, "Shader Compilation Failure!");
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }


        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            Vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            for (auto id : glShaderIDs)
            {
                glDeleteShader(id);
            }

            BBZ_CORE_ERROR("{0}", infoLog.data());
            BBZ_CORE_ASSERT(true, "Shader Linking Failure!");
            return;
        }

        for (auto id : glShaderIDs)
        {
            glDetachShader(program, id);
        }

        m_RendererID = program;
    }
}

