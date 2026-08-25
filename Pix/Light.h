#pragma once

#include "MathHelper.h"
#include <XColors.h>

class Light
{
public:
	virtual ~Light() = default;
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) = 0;
<<<<<<< Updated upstream
	void SetAmbient(const X::Color& color) { m_ambient = color; }
	void SetDiffuse(const X::Color& color) { m_diffuse = color; }
	void SetSpecular(const X::Color& color) { m_specular = color; }

protected:
=======
	void SetAmbient(const X::Color& color);
private:
>>>>>>> Stashed changes
	X::Color m_ambient = X::Colors::White;
	X::Color m_diffuse = X::Colors::White;
	X::Color m_specular = X::Colors::White;
};