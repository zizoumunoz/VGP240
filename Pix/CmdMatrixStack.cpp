#include "CmdMatrixStack.h"
#include "VariableCache.h"
#include "MatrixStack.h"

const char* CmdPushTranslation::GetName()
{
	return "PushTranslation";
}

const char* CmdPushTranslation::GetDescription()
{
	return "PushTranslation(x, y, z)\n"
		"\n"
		"- pushes a translation matrix to the matrix stack";
}

bool CmdPushTranslation::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	MatrixStack::Get()->PushTranslation({ x, y, z });
	return true;
}

const char* CmdPushRotationX::GetName()
{
	return "PushRotationX";
}

const char* CmdPushRotationX::GetDescription()
{
	return "PushRotationX(degrees)\n"
		"\n"
		"- pushes a rotation around the x axis matrix to the matrix stack";
}

bool CmdPushRotationX::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	float degrees = VariableCache::Get()->GetFloat(params[0]);
	MatrixStack::Get()->PushRotationX(degrees * MathHelper::DegToRad);
	return true;
}

const char* CmdPushRotationY::GetName()
{
	return "PushRotationY";
}

const char* CmdPushRotationY::GetDescription()
{
	return "PushRotationY(degrees)\n"
		"\n"
		"- pushes a rotation around the y axis matrix to the matrix stack";
}

bool CmdPushRotationY::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	float degrees = VariableCache::Get()->GetFloat(params[0]);
	MatrixStack::Get()->PushRotationY(degrees * MathHelper::DegToRad);
	return true;
}

const char* CmdPushRotationZ::GetName()
{
	return "PushRotationY";
}

const char* CmdPushRotationZ::GetDescription()
{
	return "PushRotationZ(degrees)\n"
		"\n"
		"- pushes a rotation around the z axis matrix to the matrix stack";
}

bool CmdPushRotationZ::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	float degrees = VariableCache::Get()->GetFloat(params[0]);
	MatrixStack::Get()->PushRotationZ(degrees * MathHelper::DegToRad);
	return true;
}

const char* CmdPushScaling::GetName()
{
	return "PushScaling";
}

const char* CmdPushScaling::GetDescription()
{
	return "PushScaling(x, y, z)\n"
		"\n"
		"- pushes a scale matrix to the matrix stack";
}

bool CmdPushScaling::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	MatrixStack::Get()->PushScaling({ x, y, z });
	return true;
}

const char* CmdPopMatrix::GetName()
{
	return "PopMatrix";
}

const char* CmdPopMatrix::GetDescription()
{
	return "PopMatrix()\n"
		"\n"
		"- pops the last matrix on the matrix stack";
}

bool CmdPopMatrix::Execute(const std::vector<std::string>& params)
{
	MatrixStack::Get()->PopMatrix();
	return true;
}
