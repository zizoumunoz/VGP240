#pragma once

#include "Command.h"

class CmdSetViewport : public Command
{
public:
	const char* GetName() override;

	const char* GetDescription() override;

	// Inherited via Command
	bool Execute(const std::vector<std::string>& params) override;
};