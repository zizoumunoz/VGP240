#pragma once

#include "Command.h"
class CmdSetColor : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;

	bool Execute(const std::vector<std::string>& params) override;


};

