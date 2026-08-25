#pragma once
#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName()
	{
		return "BeginDraw";
	}
	const char* GetDescription()
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
	bool Execute(const std::vector<std::string>& params) override;
};

