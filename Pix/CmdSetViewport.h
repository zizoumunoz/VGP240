#pragma once

#include "Command.h"

class CmdSetViewport : public Command
{
public:
	const char* GetName()
	{
		return "SetViewport";
	}
	const char* GetDescription()
	{
		return
			"SetViewport(x, y, width, height, <show>)\n"
			"\n"
			"- create a viewport rect with x, y, width, and height";
	}

	// Inherited via Command
	bool Execute(const std::vector<std::string>& params) override;
};