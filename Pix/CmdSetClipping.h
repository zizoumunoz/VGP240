#pragma once
#include "Command.h"
class CmdSetClipping :
	public Command
{
public:
	// Inherited via Command
	const char* GetName()
	{
		return "SetClipping";
	}
	const char* GetDescription()
	{
		return
			"SetClipping(enable)\n"
			"\n"
			"- enables/disables clipping outside of viewport";
	}
	bool Execute(const std::vector<std::string>& params) override;
};
