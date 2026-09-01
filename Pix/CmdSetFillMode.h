#pragma once

#include "Command.h"

class CmdSetFillMode : public Command
{
public:
    const char* GetName()
    {
        return "SetFillMode";
    }

    const char* GetDescription()
    {
        return
            "SetFillMode(fillMode)\n"
            "\n"
            "- Sets triangle fill mode (wireframe, solid)";
    }
	bool Execute(const std::vector<std::string>& params);
};