#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Bubatsu
{
    using FVec2 = glm::vec2;
    using FVec3 = glm::vec3;
    using FVec4 = glm::vec4;
    using FMat2 = glm::mat2x2;
    using FMat3 = glm::mat3x3;
    using FMat4 = glm::mat4x4;

    using IVec2 = glm::ivec2;
    using IVec3 = glm::ivec3;
    using IVec4 = glm::ivec4;
    using IMat2 = glm::imat2x2;
    using IMat3 = glm::imat3x3;
    using IMat4 = glm::imat4x4;

    inline FMat4 Ortho(float left, float right, float bottom, float top, float front = -1.0f, float back = 1.0f)
    {
        return glm::ortho(left, right, bottom, top, front, back);
    };

    inline FMat4 Translate(FMat4 m, FVec3 p)
    {
        return glm::translate(m, p);
    };

    inline FMat4 Rotate(FMat4 m, float a, FVec3 v)
    {
        return glm::rotate(m, a, v);
    };

    template<typename T>
    inline T Radians(T r)
    {
        return glm::radians(r);
    };

    inline FMat4 Inverse(FMat4 m)
    {
        return glm::inverse(m);
    };

    inline FMat4 Scale(FMat4 m, FVec3 v)
    {
        return glm::scale(m, v);
    };

    #define RawValuePtr(v) glm::value_ptr(v)
}

