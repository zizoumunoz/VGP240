#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "LightManager.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return {
			hw, 0.0f, 0.0f, 0.0f,
			0.0f, -hh, 0.0f, 0.0,
			0.0f, 0.0f, 1.0f, 0.0f,
			hw, hh, 0.0f, 1.0f
		};
	}

	Vector3 CreateFaceNormal(const std::vector<Vertex>& triangle)
	{
		// take b-a cross c-a
		const Vector3& a = triangle[0].m_pos;
		const Vector3& b = triangle[1].m_pos;
		const Vector3& c = triangle[2].m_pos;
		Vector3 norm = MathHelper::Normalize(MathHelper::Cross((b - a), (c - a)));
		return norm;
	}

	bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangle)
	{
		if (mode == CullMode::None)
		{
			return false;
		}
		Vector3 faceNormal = CreateFaceNormal(triangle);
		if (mode == CullMode::Back)
		{
			return faceNormal.z > 0.0f;
		}
		else {
			return faceNormal.z < 0.0f;
		}
	}
}

PrimitivesManager::PrimitivesManager()
{
}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	m_vertexBuffer.clear();
	m_topology = topology;
	m_applyTransform = applyTransform;
	m_drawBegin = true;
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
	if (m_drawBegin)
	{
		m_vertexBuffer.push_back(v);
	}
}

void PrimitivesManager::EndDraw()
{
	if (!m_drawBegin)
	{
		return;
	}

	// apply transformation pipeline
	// matLocal -> matWrold -> matView -> matProj -> matScreen
	Matrix4 matWorld = MatrixStack::Get()->GetTransform();
	// view matrix from the camera
	Matrix4 matView = Camera::Get()->GetViewMatrix();
	// projection matrix from the camera
	Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
	// Screen space matrix from the screen
	Matrix4 matScreen = GetScreenTransform();
	// full transformation pipeline (commented out for notes)
	// Matrix4 matFinal = matWorld * matView * matProj * matScreen;
	// transformation pipeline only to NDC space
	Matrix4 matNDCSpace = matWorld * matView * matProj;

	ShadeMode shadeMode = Rasterizer::Get()->GetShadeMode();



	switch (m_topology)
	{
	case Topology::Point:
	{
		for (uint32_t i = 0; i < m_vertexBuffer.size(); ++i)
		{
			if (!Clipper::Get()->ClipPoint(m_vertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(m_vertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Line:
	{
		for (uint32_t i = 1; i < m_vertexBuffer.size(); i += 2)
		{
			if (!Clipper::Get()->ClipLine(m_vertexBuffer[i - 1], m_vertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(m_vertexBuffer[i - 1], m_vertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Triangle:
	{
		for (uint32_t i = 2; i < m_vertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = {
				m_vertexBuffer[i - 2],
				m_vertexBuffer[i - 1],
				m_vertexBuffer[i]
			};
			if (m_applyTransform)
			{
				// add normals to the vertcies (reminder at this point we are in local space)
				Vector3 faceNorm = CreateFaceNormal(triangle);
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].norm = faceNorm;
				}

				// mat world to transform into world space
				// lighting is done in world space
				// WORLD SPACE ======
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					// tranasforming all positions to world space
					triangle[t].m_pos = MathHelper::TransformCoord(triangle[t].m_pos, matWorld);
					triangle[t].worldPos = triangle[t].m_pos;
					triangle[t].norm = MathHelper::TransformNormal(triangle[t].norm, matWorld);
				}

				if (shadeMode == ShadeMode::Flat)
				{
					triangle[0].m_color *= LightManager::Get()->ComputeLightColor(triangle[0].m_pos, triangle[0].norm);
					triangle[1].m_color = triangle[0].m_color;
					triangle[2].m_color = triangle[0].m_color;
				}
				else if (shadeMode == ShadeMode::Gouraud)
				{
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						// apply light color to the vertices
						triangle[t].m_color *= LightManager::Get()->ComputeLightColor(triangle[t].m_pos, triangle[t].norm);
					}
				}


				// transform to NDC space, then check facing to see if you can draw, then draw
				// use 3 points of triangle to make normal direction
				// check the normal if it should be culled, proceed or cancel
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					// transforming all positions to NDC space
					triangle[t].m_pos = MathHelper::TransformCoord(triangle[t].m_pos, matNDCSpace);
				}

				// triangle in NDC space, if cull mode says to cull, continue, otherwise reender
				if (CullTriangle(m_cullMode, triangle))
				{
					continue;
				}
				for (size_t t = 0; t < triangle.size(); t++)
				{
					// if already in NDC space, transform again just with the remaining matrices (matScreen)
					triangle[t].m_pos = MathHelper::TransformCoord(triangle[t].m_pos, matScreen);
					// after converting to screen space, make sure x and y are whole numbers
					MathHelper::FlattenVectorScreenCoord(triangle[t].m_pos);
				}
			}
			// transformation pipeline (matFinal, transforms from 

			// screen space
			if (!Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);

				}
			}
		}
	}
	break;
	default:
		break;
	}
}

void PrimitivesManager::OnNewFrame()
{
	m_cullMode = CullMode::None;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	m_cullMode = mode;
}

