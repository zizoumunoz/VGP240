#include "CmdVertex.h"
#include "PrimitivesManager.h"
#include "VariableCache.h"

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 2)
	{
		return false;
	}

	Vertex v;
	v.m_pos = Vector3(0, 0, 0);
	v.m_color = X::Color(1, 1, 1, 1);
	v.m_pos.x = VariableCache::Get()->GetFloat(params[0]);
	v.m_pos.y = VariableCache::Get()->GetFloat(params[1]);

	if (params.size() == 2)
	{

	}
	else if (params.size() == 3)
	{
		v.m_pos.z = VariableCache::Get()->GetFloat(params[2]);
	}
	else if (params.size() == 5) {
		v.m_color.r = VariableCache::Get()->GetFloat(params[2]);
		v.m_color.g = VariableCache::Get()->GetFloat(params[3]);
		v.m_color.b = VariableCache::Get()->GetFloat(params[4]);
	}
	else if (params.size() == 6) {
		v.m_pos.z = VariableCache::Get()->GetFloat(params[2]);
		v.m_color.r = VariableCache::Get()->GetFloat(params[3]);
		v.m_color.g = VariableCache::Get()->GetFloat(params[4]);
		v.m_color.b = VariableCache::Get()->GetFloat(params[5]);
	}
	else {
		return false;
	}

	PrimitivesManager::Get()->AddVertex(v);
	return true;
}
