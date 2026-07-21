#pragma once
#include "Command.h"
class CmdSetClipping :
	public Command
{
public:
	// Inherited via Command
	const char* GetName() override;

	const char* GetDescription() override;

	bool Execute(const std::vector<std::string>& params) override;

};
