#pragma once

#include "Command.h"

class CmdSetLightAmbient : public Command
{
public:
    const char* GetName() override
    {
        return "SetLightAmbient";
    }
    const char* GetDescription() override
    {
        return
            "SetLightAmbient(r, g, b)\n"
            "\n"
            "- sets the ambient color of the light";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightSpecular : public Command
{
public:
    const char* GetName() override
    {
        return "SetLightSpecular";
    }
    const char* GetDescription() override
    {
        return
            "SetLightSpecular(r, g, b)\n"
            "\n"
            "- sets the Specular color of the light";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightDiffuse : public Command
{
public:
    const char* GetName() override
    {
        return "SetLightDiffuse";
    }
    const char* GetDescription() override
    {
        return
            "SetLightDiffuse(r, g, b)\n"
            "\n"
            "- sets the Diffuse color of the light";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddDirectionalLight : public Command