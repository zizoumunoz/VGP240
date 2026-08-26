#pragma once

#include "Command.h"

class CmdVertex : public Command
{
public:
	const char* GetName()
	{
		return "Vertex";
	}
	const char* GetDescription()
	{
		return
			"Vertex(x, y)\n"			// only 2d pos
			"Vertex(x, y, z)\n"			// only 3d pos
			"Vertex(x, y, r, g, b)\n"	// a 2d pos with color
			"\n"
			"- Adds vertex to the primitives manager before render";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

