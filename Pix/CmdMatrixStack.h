#pragma once

#include "Command.h"

class CmdPushTranslation : public Command
{
public:
	const char* GetName()
	{
		return "PushTranslation";
	}
	const char* GetDescription()
	{
		return "PushTranslation(x, y, z)\n"
			"\n"
			"- pushes a translation matrix to the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationX : public Command
{
public:

	const char* GetName()
	{
		return "PushRotationX";
	}
	const char* GetDescription()
	{
		return "PushRotationX(degrees)\n"
			"\n"
			"- pushes a rotation around the x axis matrix to the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationY : public Command
{
public:

	const char* GetName()
	{
		return "PushRotationY";
	}
	const char* GetDescription()
	{
		return "PushRotationY(degrees)\n"
			"\n"
			"- pushes a rotation around the y axis matrix to the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationZ : public Command
{
public:

	const char* GetName()
	{
		return "PushRotationZ";
	}
	const char* GetDescription()
	{
		return "PushRotationZ(degrees)\n"
			"\n"
			"- pushes a rotation around the z axis matrix to the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushScaling : public Command
{
public:
	const char* GetName()
	{
		return "PushScaling";
	}
	const char* GetDescription()
	{
		return "PushScaling(x, y, z)\n"
			"\n"
			"- pushes a scale matrix to the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;

};

class CmdPopMatrix : public Command
{
public:
	const char* GetName()
	{
		return "PopMatrix";
	}

	const char* GetDescription()
	{
		return "PopMatrix()\n"
			"\n"
			"- pops the last matrix on the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
