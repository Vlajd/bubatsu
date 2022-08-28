#include "bbzpch.h"
#include "OrthographicCamera.h"

namespace Bubatsu
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(Ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		FMat4 transform = Translate(glm::mat4(1.0f), m_Position) * Rotate(glm::mat4(1.0f), Radians(m_Rotation), FVec3(0, 0, 1));

		m_ViewMatrix = Inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}