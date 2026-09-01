#include "MaterialManager.h"

MaterialManager* MaterialManager::Get()
{
    static MaterialManager s_instance;
    return &s_instance;
}

void MaterialManager::OnNewFrame()
{
    m_emissive = X::Colors::Black;
    m_ambient = X::Colors::White;
    m_diffuse = X::Colors::White;
    m_specular = X::Colors::White;
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
void MaterialManager::SetMaterialDiffuse(const X::Color& color)
{
    m_diffuse = color;
}
void MaterialManager::SetMaterialSpecular(const X::Color& color)
{
    m_specular = color;
}
void MaterialManager::SetMaterialShininess(float color)
{
    m_shininess = color;
}

const X::Color& MaterialManager::GetMaterialEmissive() const
{
    return m_emissive;
}
const X::Color& MaterialManager::GetMaterialAmbient() const
{
    return m_ambient;
}
const X::Color& MaterialManager::GetMaterialDiffuse() const
{
    return m_diffuse;
}
const X::Color& MaterialManager::GetMaterialSpecular() const
{
    return m_specular;
}
const float MaterialManager::GetMaterialShininess() const
{
    return m_shininess;
}
