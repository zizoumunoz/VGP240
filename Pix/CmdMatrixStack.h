#pragma once

#include "Command.h"

class CmdPushTranslation : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushScaling : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;
	bool Execute(const std::vector<std::string>& params) override;

};

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override;
	const char* GetDescription() override;
	bool Execute(const std::vector<std::string>& params) override;
};
