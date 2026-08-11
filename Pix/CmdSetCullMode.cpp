#include "CmdSetCullMode.h"

const char* CmdSetCullMode::GetName()
{
    return "SetCullMode";
}

const char* CmdSetCullMode::GetDescription()
{
    return nullptr;
}

bool CmdSetCullMode::Execute(const std::vector<std::string>& params)
{
    return false;
}
