#include "CmdSetClipping.h"
#include "Clipper.h"

const char* CmdSetClipping::GetName()
{
	return "SetClipping";
}

const char* CmdSetClipping::GetDescription()
{
	return
		"SetClipping(enable)\n"
		"\n"
		"- enables/disables clipping outside of viewport";
}

bool CmdSetClipping::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	bool enable = params[0] == "true";
	Clipper::Get()->SetClipping(enable);
	return true;
}
