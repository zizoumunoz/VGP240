#include "CmdEndDraw.h"
#include "PrimitivesManager.h"

const char* CmdEndDraw::GetName()
{
	return "EndDraw";
}

const char* CmdEndDraw::GetDescription()
{
	return
		"EndDraw()\n"
		"- Sends the vertices to rasterizer to render";
}

bool CmdEndDraw::Execute(const std::vector<std::string>& params)
{
	PrimitivesManager::Get()->EndDraw();
	return true;
}
