#pragma once

#include "MathHelper.h"

class Camera
{
public:
	static Camera* Get();

	void OnNewFrame();

	// external info
	void SetPosition(const Vector3& pos);
	void SetDirection(const Vector3& dir);

	// internal info
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetFov(float fov);

	Matrix4 GetViewMatrix() const;
	Matrix4 GetProjectionMatrix() const;

	const Vector3& GetPosition() const;
	const Vector3& GetDirection() const;

private:
	Vector3 m_position;
	Vector3 m_direction;
	float m_nearPlane;
	float m_farPlane;
	float m_FOV;
};
