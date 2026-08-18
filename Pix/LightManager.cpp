#include "LightManager.h"
#include "MaterialManager.h"
#include "LightTypes.h"

LightManager* LightManager::Get()
{
	static LightManager s_instance;
	return &s_instance;
}

void LightManager::OnNewFrame()
{
	m_lights.clear();
	m_ambient = X::Colors::White;
	m_diffuse = X::Colors::White;
	m_specular = X::Colors::White;
}

void LightManager::SetLightAmbient(const X::Color& color)
{
	m_ambient = color;
}

void LightManager::SetLightDiffuse(const X::Color& color)
{
	m_diffuse = color;
}

void LightManager::SetLightSpecular(const X::Color& color)
{
	m_specular = color;
}

// dir light

void LightManager::AddDirectionalLight(const Vector3& direction)
{
	auto light = std::make_unique<DirectionalLight>();
	light->SetAmbient(m_ambient);
	light->SetDiffuse(m_diffuse);
	light->SetSpecular(m_specular);

}

// point light
// spot light

X::Color LightManager::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	if (m_lights.empty())
	{
		return X::Colors::White;
	}
	// C = Ce + E(Ca + Cd + Cs) of all the lights
	X::Color color = MaterialManager::
}
