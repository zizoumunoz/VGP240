#include "LightTypes.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color DirectionalLight::ComputeLightColor(const Vector3 & position, const Vector3 & normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	X::Color ambient = m_ambient * mm->GetMaterialAmbient();

	Vector3 L = -m_direction;
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = m_diffuse * mm->GetMaterialDiffuse() * dot;

	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.0f);
	X::Color specular = m_specular * mm->GetMaterialSpecular() * fallOff;

	return ambient + diffuse + specular;
}

void DirectionalLight::SetDirection(const Vector3& direction)
{
	m_direction = MathHelper::Normalize(direction);
}

X::Color PointLight::ComputeLightColor(const Vector3& position, const Vector3& normal) {
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	Vector3 L = m_position - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	float attenuation = 1.0f / (m_kConstant + (m_kLinear * distance) + (m_kQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);

	X::Color ambient = m_ambient * mm->GetMaterialAmbient();

	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = m_diffuse * mm->GetMaterialDiffuse() * dot * iL;

	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOf = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.0f);
	X::Color specular = m_specular * mm->GetMaterialSpecular() * fallOf * iL;

	return ambient + diffuse + specular;
}

void PointLight::SetPosition(const Vector3& position)
{
	m_position = position;
}
void PointLight::SetAttenuation(float kConstant, float kLinear, float kQuadratic)
{
	m_kConstant = kConstant;
	m_kLinear = kLinear;
	m_kQuadratic = kQuadratic;
}

X::Color SpotLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	Vector3 L = m_position - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	X::Color ambient = m_ambient * mm->GetMaterialAmbient();

	Vector3 lightDir = -L;
	float dotDir = MathHelper::Dot(lightDir, m_direction);
	if (dotDir < m_cosAngle)
	{
		return ambient;
	}

	float spot = pow(dotDir, m_decay);
	float attenuation = spot / (m_kConstant + (m_kLinear * distance) + (m_kQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);

	X::Color ambient = m_ambient * mm->GetMaterialAmbient();

	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = m_diffuse * mm->GetMaterialDiffuse() * dot * iL;

	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOf = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.0f);
	X::Color specular = m_specular * mm->GetMaterialSpecular() * fallOf * iL;

	return ambient + diffuse + specular;
}

void SpotLight::SetPosition(const Vector3& position)
{
	m_position = position;
}

void SpotLight::SetDirection(const Vector3& direction)
{
	m_direction = MathHelper::Normalize(direction);
}

void SpotLight::SetAttenuation(float kConstant, float kLinear, float kQuadratic)
{
	m_kConstant = kConstant;
	m_kLinear = kLinear;
	m_kQuadratic = kQuadratic;
}

void SpotLight::SetAngle(float angle)
{
	m_cosAngle = cos(angle);
}

void SpotLight::SetDecay(float decay)
{
	m_decay = decay;
}