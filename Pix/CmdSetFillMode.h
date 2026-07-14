#pragma once

#include "Command.h"

class CmdSetFillMode : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;
	bool Execute(const std::vector<std::string>& params);
};