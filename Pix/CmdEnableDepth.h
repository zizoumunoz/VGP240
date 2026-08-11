#pragma once

#include "Command.h"

class CmdEnableDepth : public Command
{
public:


	// Inherited via Command
	const char* GetName() override
	{
		return "EnableDepth";
	}

	const char* GetDescription() override
	{
		return
			"EnableDepth(enable)\n"
			"\n"
			"- enable/disable depth buffer";
	}

	bool Execute(const std::vector<std::string>& params) override;

};