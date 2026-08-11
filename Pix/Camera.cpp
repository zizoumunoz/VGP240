#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

Camera* Camera::Get()
{
	static Camera s_instance;
	return &s_instance;
}

void Camera::OnNewFrame()
{
	m_position = { 0.0f, 0.0f, 0.0f };
	m_direction = { 0.0f, 0.0f, 1.0f };
	m_nearPlane = 0.01f;
	m_farPlane = 100.0f;
	m_FOV = 1.57f;
}

void Camera::SetPosition(const Vector3& pos)
{
	m_position = pos;
}

void Camera::SetDirection(const Vector3& dir)
{
	m_direction = MathHelper::Normalize(dir);
}

void Camera::SetNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	m_farPlane = farPlane;
}

void Camera::SetFov(float fov)
{
	m_FOV = fov;
}

Matrix4 Camera::GetViewMatrix() const
{
	// need to return inverse camera world matrix
	const Vector3 l = m_direction;
	const Vector3 r = MathHelper::Normalize(MathHelper::Cross({ 0.0f, 1.0f, 0.0f }, l));
	const Vector3 u = MathHelper::Normalize(MathHelper::Cross(l, r));
	const float a = -MathHelper::Dot(r, m_position);
	const float b = -MathHelper::Dot(u, m_position);
	const float c = -MathHelper::Dot(l, m_position);
	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		  a,   b,   c, 1.0f
	};
}

Matrix4 Camera::GetProjectionMatrix() const
{
	const float a = gResolutionX / gResolutionY;
	const float d = 1.0f / tanf(m_FOV * 0.5f);
	const float w = d / a;
	const float zn = m_nearPlane;
	const float zf = m_farPlane;
	const float q = zf / (zf - zn);
	return{
		w, 0.0f, 0.0f, 0.0f,
		0.0f, d, 0.0f, 0.0f,
		0.0f, 0.0f, q, 1.0f,
		0.0f, 0.0f, -zn * q, 0.0f
	};
}

const Vector3& Camera::GetPosition() const
{
	return m_position;
}

const Vector3& Camera::GetDirection() const
{
	return m_direction;
}