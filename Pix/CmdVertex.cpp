#include "CmdVertex.h"
#include "PrimitivesManager.h"

const char* CmdVertex::GetName()
{
	return "Vertex";
}

const char* CmdVertex::GetDescription()
{
	return
		"Vertex(x, y)\n"			// only 2d pos
		"Vertex(x, y, z)\n"			// only 3d pos
		"Vertex(x, y, r, g, b)\n"	// a 2d pos with color
		"\n"
		"- Adds vertex to the primitives manager before render";
}

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float r = 1.0f, g = 1.0f, b = 1.0f;

	if (params.size() == 2)	// only 2d position
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
	}
	else if (params.size() == 3) // only 3d pos
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
		z = std::stof(params[2]);
	}
	else if (params.size() == 5) // only 2d pos and color
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
		r = std::stof(params[2]);
		g = std::stof(params[3]);
		b = std::stof(params[4]);
	}
	else if (params.size() == 6) // only 3d pos and color
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
		y = std::stof(params[2]);
		r = std::stof(params[3]);
		g = std::stof(params[4]);
		b = std::stof(params[5]);
	}
	else
	{
		return false;
	}

	Vertex v;
	v.m_pos = { x, y ,z };
	v.m_color = { r, g, b, 1.0f };
	PrimitivesManager::Get()->AddVertex(v);
	return true;
}
