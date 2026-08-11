#include "CmdBeginDraw.h"
#include "PrimitivesManager.h"

const char* CmdBeginDraw::GetName()
{
	return "BeginDraw";
}

const char* CmdBeginDraw::GetDescription()
{
	return
	{
		"BeginDraw(topology, <applyTransform>)\n"
		"\n"
		"- Starts storing vertices\n"
		"- topology (point, line, triangle)\n"
		"- (optional) apply transform to apply 3d pipeline transformation to vertices"
	};

}

bool CmdBeginDraw::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	Topology topology = Topology::Point;
	if (params[0] == "point") 
	{
		topology = Topology::Point;
	}
	else if (params[0] == "line")
	{
		topology = Topology::Line;
	}
	else if (params[0] == "triangle")
	{
		topology = Topology::Triangle;
	}
	else
	{
		return false;
	}

	bool applyTransform = params.size() > 1 && params[1] == "true";
	PrimitivesManager::Get()->BeginDraw(topology, applyTransform);
	return true;
}
