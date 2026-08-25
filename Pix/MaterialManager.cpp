#include "MaterialManager.h"

MaterialManager* MaterialManager::Get()
{
<<<<<<< Updated upstream
    static MaterialManager sInstance;
    return &sInstance;
=======
    static MaterialManager s_instance;
    return &s_instance;
>>>>>>> Stashed changes
}

void MaterialManager::OnNewFrame()
{
    m_emissive = X::Colors::Black;
<<<<<<< Updated upstream
    m_ambient = X::Colors::White;
    m_diffuse = X::Colors::White;
    m_specular = X::Colors::White;
=======
    m_emissive = X::Colors::White;
    m_emissive = X::Colors::White;
    m_emissive = X::Colors::White;
>>>>>>> Stashed changes
    m_shininess = 10.0f;
}

void MaterialManager::SetMaterialEmissive(const X::Color& color)
{
    m_emissive = color;
}

void MaterialManager::SetMaterialAmbient(const X::Color& color)
{
    m_ambient = color;
}

<<<<<<< Updated upstream
void MaterialManager::SetMaterialSpecular(const X::Color& color)
{
    m_specular = color;
}

=======
>>>>>>> Stashed changes
void MaterialManager::SetMaterialDiffuse(const X::Color& color)
{
    m_diffuse = color;
}

<<<<<<< Updated upstream
void MaterialManager::SetMaterialShininess(const float color)
=======
void MaterialManager::SetMaterialShininess(const X::Color& color)
>>>>>>> Stashed changes
{
    m_shininess = color;
}

<<<<<<< Updated upstream
=======
void MaterialManager::SetMaterialSpecular(const float color)
{
    m_specular = color;
}

>>>>>>> Stashed changes
const X::Color& MaterialManager::GetMaterialEmissive() const
{
    return m_emissive;
}

const X::Color& MaterialManager::GetMaterialAmbient() const
{
    return m_ambient;
}

<<<<<<< Updated upstream
const X::Color& MaterialManager::GetMaterialSpecular() const
{
    return m_specular;
}

=======
>>>>>>> Stashed changes
const X::Color& MaterialManager::GetMaterialDiffuse() const
{
    return m_diffuse;
}

<<<<<<< Updated upstream
const float MaterialManager::GetMaterialShininess() const
{
    return m_shininess;
}
=======
const X::Color& MaterialManager::GetMaterialSpecular() const
{
    return m_specular;
}

const float MaterialManager::GetMaterialShininess() const
{
    return m_shininess;
}
>>>>>>> Stashed changes
