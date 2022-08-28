#pragma once

#include "Bubatsu/Core/Core.h"
#include "Bubatsu/Core/Math.h"


namespace Bubatsu
{
	class BUBATSU_API OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const FVec3& GetPosition() const { return m_Position; }
		void SetPosition(const FVec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const FMat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const FMat4& GetViewMatrix() const { return m_ViewMatrix; }
		const FMat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

		FMat4 m_ProjectionMatrix;
		FMat4 m_ViewMatrix;
		FMat4 m_ViewProjectionMatrix;

		FVec3 m_Position = FVec3(0.0f);
		float m_Rotation = 0.0f;
	};
}