#include "bbzpch.h"
#include "OrthographicCamera.h"


namespace Bubatsu
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(Ortho(left, right, bottom, top)), m_ViewMatrix(1.0f)
    {
        BBZ_PROFILE_FUNCTION();

        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        BBZ_PROFILE_FUNCTION();

        m_ProjectionMatrix = Ortho(left, right, bottom, top);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        BBZ_PROFILE_FUNCTION();

        FMat4 transform = Translate(FMat4(1.0f), m_Position) * Rotate(FMat4(1.0f), Radians(m_Rotation), FVec3(0, 0, 1));

        m_ViewMatrix = Inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}

