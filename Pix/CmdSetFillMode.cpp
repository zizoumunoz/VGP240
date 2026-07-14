#include "CmdSetFillMode.h"
#include "Rasterizer.h"

const char* CmdSetFillMode::GetName()
{
    return "SetFillMode";
}

const char* CmdSetFillMode::GetDescription()
{
    return
        "SetFillMode(fillMode)\n"
        "\n"
        "- Sets triangle fill mode (wireframe, solid)";
}

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    FillMode fillMode = FillMode::Wireframe;
    if (params[0] == "wireframe")
    {
        fillMode = FillMode::Wireframe;
    }
    else if (params[0] == "solid")
    {
        fillMode = FillMode::Solid;
    }
    else
    {
        return false;
    }

    Rasterizer::Get()->SetFillMode(fillMode);
    return true;
}
