#include "CmdSetColor.h"
#include "Rasterizer.h"

const char* CmdSetColor::GetName()
{
	return "SetColor";
}

const char* CmdSetColor::GetDescription()
{
	return
		"SetColor(r, g, b)\n"
		"\n"
		"- Sets the color of the next pixel using red, green, and blue\n"
		"- Values are from 0.0 to 1.0";
}

bool CmdSetColor::Execute(const std::vector<std::string>& params)
{
	// need 3 values, r, g, b
	if (params.size() < 3)
	{
		return false; 
	}
	float r = std::stof(params[0]);
	float g = std::stof(params[1]);
	float b = std::stof(params[2]);

	Rasterizer::Get()->SetColor({ r, g, b, 1.0f });
	return true;

}
