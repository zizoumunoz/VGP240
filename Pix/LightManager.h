#pragma once

#include <XEngine.h>
#include "Vector3.h"
#include "Light.h"

class LightManager
{
public:
	static LightManager* Get();

	void OnNewFrame();

	void SetLightAmbient(const X::Color& color);
	void SetLightDiffuse(const X::Color& color);
	void SetLightSpecular(const X::Color& color);

	// directional light
	// point light
	// spot light

	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal);
	void AddDirectionalLight(const Vector3& direction);

private:
	std::vector<std::unique_ptr<Light>> m_lights;
	X::Color m_ambient = X::Colors::White;
	X::Color m_diffuse = X::Colors::White;
	X::Color m_specular = X::Colors::White;
};