#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

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

	bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangle);
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
		if (mode == CullMode::Front)
		{
			return faceNormal.z < 0.0f;
		}
		return false;
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

bool PrimitivesManager::BeginDraw(Topology topology)
{
	m_VertexBuffer.clear();
	m_Topology = topology;
	m_DrawBegin = true;
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
	if (m_DrawBegin)
	{
		m_VertexBuffer.push_back(v);
	}
}

void PrimitivesManager::EndDraw()
{
	if (!m_DrawBegin)
	{
		return;
	}

	// 



	switch (m_Topology)
	{
	case Topology::Point:
	{
		for (uint32_t i = 0; i < m_VertexBuffer.size(); ++i)
		{
			if (!Clipper::Get()->ClipPoint(m_VertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(m_VertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Line:
	{
		for (uint32_t i = 1; i < m_VertexBuffer.size(); i += 2)
		{
			if (!Clipper::Get()->ClipLine(m_VertexBuffer[i - 1], m_VertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(m_VertexBuffer[i - 1], m_VertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Triangle:
	{
		for (uint32_t i = 2; i < m_VertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = {
				m_VertexBuffer[i - 2],
				m_VertexBuffer[i - 1],
				m_VertexBuffer[i]
			};
			if (m_applyTransform)
			{
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
			}
			// transformation pipeline (matFinal, transforms from 
			for (size_t t = 0; t < triangle.size(); t++)
			{
				// if already in NDC space, transform again just with the remaining matrices (matScreen)
				triangle[t].m_pos = MathHelper::TransformCoord(triangle[t].m_pos, matScreen);
				// after converting to screen space, make sure x and y are whole numbers
				MathHelper::FlattenVectorScreenCoord(triangle[t].m_pos);
			}

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

