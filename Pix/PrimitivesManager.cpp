#include "PrimitivesManager.h"
#include "Rasterizer.h"

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
	_mVertexBuffer.clear();
	_mTopology = topology;
	_mDrawBegin = true;
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
	if (_mDrawBegin)
	{
		_mVertexBuffer.push_back(v);
	}
}

void PrimitivesManager::EndDraw()
{
	if (!_mDrawBegin)
	{
		return;
	}
	switch (_mTopology)
	{
	case Topology::Point:
	{
		for (uint32_t i = 0; i < _mVertexBuffer.size(); ++i)
		{
			Rasterizer::Get()->DrawPoint(_mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Line:
	{
		for (uint32_t i = 1; i < _mVertexBuffer.size(); i += 2)
		{
			Rasterizer::Get()->DrawLine(_mVertexBuffer[i - 1], _mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Triangle:
	{
		for (uint32_t i = 2; i < _mVertexBuffer.size(); i += 3)
		{
			Rasterizer::Get()->DrawLine(_mVertexBuffer[i - 2], _mVertexBuffer[i]);
		}
	}
	break;
	default:
		break;
	}
}

