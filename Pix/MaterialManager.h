#pragma once

#include <XColors.h>

class MaterialManager
{
public:
	static MaterialManager* Get();

	void OnNewFrame();

	void SetMaterialEmissive(const X::Color& color);
	void SetMaterialAmbient(const X::Color& color);
	void SetMaterialDiffuse(const X::Color& color);
	void SetMaterialSpecular(const X::Color& color);
	void SetMaterialShininess(float color);

	const X::Color& GetMaterialEmissive() const;
	const X::Color& GetMaterialAmbient() const;
	const X::Color& GetMaterialDiffuse() const;
	const X::Color& GetMaterialSpecular() const;
	const float GetMaterialShininess() const;

private:
	X::Color m_emissive = X::Colors::Black;
	X::Color m_ambient = X::Colors::White;
	X::Color m_diffuse = X::Colors::White;
	X::Color m_specular = X::Colors::White;
	float m_shininess = 10.0f;

};