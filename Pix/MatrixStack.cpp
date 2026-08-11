#include "MatrixStack.h"

MatrixStack* MatrixStack::Get()
{
    static MatrixStack s_instance;
    return &s_instance;
}

void MatrixStack::OnNewFrame()
{
    m_combinedTransform = Matrix4::Identity();
    m_matrices.clear();

}

void MatrixStack::PushTranslation(const Vector3& d)
{
    Matrix4 translationMatrix = Matrix4::Translation(d);
    m_combinedTransform = translationMatrix * m_combinedTransform;
    m_matrices.push_back(translationMatrix);
}

void MatrixStack::PushRotationX(float radians)
{
    Matrix4 rotationMatrix = Matrix4::RotationX(radians);
    m_combinedTransform = rotationMatrix * m_combinedTransform;
    m_matrices.push_back(rotationMatrix);
}

void MatrixStack::PushRotationY(float radians)
{
    Matrix4 rotationMatrix = Matrix4::RotationY(radians);
    m_combinedTransform = rotationMatrix * m_combinedTransform;
    m_matrices.push_back(rotationMatrix);
}

void MatrixStack::PushRotationZ(float radians)
{
    Matrix4 rotationMatrix = Matrix4::RotationZ(radians);
    m_combinedTransform = rotationMatrix * m_combinedTransform;
    m_matrices.push_back(rotationMatrix);
}

void MatrixStack::PushScaling(const Vector3& s)
{
    Matrix4 scaleMatrix = Matrix4::Scale(s);
    m_combinedTransform = scaleMatrix * m_combinedTransform;
    m_matrices.push_back(scaleMatrix);
}

void MatrixStack::PopMatrix()
{
    if (!m_matrices.empty())
    {
        Matrix4 matrix = m_matrices.back();
        m_matrices.pop_back();
        m_combinedTransform = MathHelper::Inverse(matrix) * m_combinedTransform;
    }
}

const Matrix4& MatrixStack::GetTransform() const
{
    return m_combinedTransform;
}
