#include "LightTypes.h"
#include "MaterialManager.h"
#include "Camera.h"


X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	// Calculate ambient color
	X::Color ambient = m_ambient * mm->GetMaterialAmbient();

	// calculate diffuse color
	Vector3 L = -m_direction;
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = m_diffuse * mm->GetMaterialDiffuse() * dot;

	// calculate specular color
	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.0f);
	X::Color specular = m_specular * mm->GetMaterialSpecular() * fallOff;

	//  final color
	return m_ambient + m_diffuse + m_specular;

}

void DirectionalLight::SetDirection(const Vector3& direction)
{
	m_direction = MathHelper::Normalize(direction);
}
