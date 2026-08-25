#pragma once

#include <XEngine.h>
#include "Light.h"

class LightManager
{
public:
	static LightManager* Get();

	void OnNewFrame();

	void SetLightAmbient(const X::Color& color);
	void SetLightDiffuse(const X::Color& color);
	void SetLightSpecular(const X::Color& color);

<<<<<<< Updated upstream
	// directional light
	void AddDirectionalLight(const Vector3& direction);
	// point light
	void AddPointLight(const Vector3& position, float kConstant, float kLinear, float kQuadratic);

	// spot light

=======
>>>>>>> Stashed changes
	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal);

private:
	std::vector<std::unique_ptr<Light>> m_lights;
	X::Color m_ambient = X::Colors::White;
	X::Color m_diffuse = X::Colors::White;
	X::Color m_specular = X::Colors::White;
};