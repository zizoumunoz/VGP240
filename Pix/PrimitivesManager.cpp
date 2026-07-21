#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

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

