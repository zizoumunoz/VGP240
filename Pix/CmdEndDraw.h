#pragma once

#include "Command.h"

class CmdEndDraw : public Command
{
public:
	const char* GetName()
	{
		return "EndDraw";
	}

	const char* GetDescription()
	{
		return
			"EndDraw()\n"
			"- Sends the vertices to rasterizer to render";
	}
	bool Execute(const std::vector<std::string>& params) override;
	
};