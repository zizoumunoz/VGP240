#include "VariableCache.h"

#include <ImGui/Inc/imgui.h>
#include <algorithm>

struct Variable
{
	virtual ~Variable() = default;
	virtual void ShowUI() = 0;
	std::string name;
};

struct FloatVar : public Variable
{
	// Inherited via Variable
	void ShowUI() override
	{
		ImGui::DragFloat(name.c_str(), &value, speed, min, max);
	}

	float value = 0.0f;
	float speed = 1.0f;
	float min = 0.0f;
	float max = 1.0f;
};

struct IntVar : public Variable
{
	void ShowUI() override
	{
		ImGui::DragInt(name.c_str(), &value, speed, min, max);
	}
	int value = 0;
	float speed = 1.0f;
	int min = 0;
	int max = 1;
};

struct BoolVar : public Variable
{
	void ShowUI() override
	{
		ImGui::Checkbox(name.c_str(), &value);
	}
	bool value = true;
};

VariableCache* VariableCache::Get()
{
	static VariableCache sInstance;
	return &sInstance;
}

void VariableCache::Clear()
{
	m_variables.clear();
}

bool VariableCache::IsVarName(const std::string& name) const
{
	return !name.empty() && name[0] == '$';
}

void VariableCache::AddFloat(const std::string& name, float value, float speed, float min, float max)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(m_variables.begin(), m_variables.end(), [name](auto& var)
		{
			return var->name == name;
		});
	if (iter == m_variables.end())
	{
		auto floatVar = std::make_unique<FloatVar>();
		floatVar->name = name;
		floatVar->value = value;
		floatVar->speed = speed;
		floatVar->min = min;
		floatVar->max = max;
		m_variables.emplace_back(std::move(floatVar));
	}
}

float VariableCache::GetFloat(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(m_variables.begin(), m_variables.end(), [param](auto& var)
			{
				return var->name == param;
			});
		if (iter != m_variables.end())
		{
			return static_cast<FloatVar*>((*iter).get())->value;
		}
	}

	return stof(param);
}

void VariableCache::AddInt(const std::string& name, int value, float speed, int min, int max)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(m_variables.begin(), m_variables.end(), [name](auto& var)
		{
			return var->name == name;
		});
	if (iter == m_variables.end())
	{
		auto intVar = std::make_unique<IntVar>();
		intVar->name = name;
		intVar->value = value;
		intVar->speed = speed;
		intVar->min = min;
		intVar->max = max;
		m_variables.emplace_back(std::move(intVar));
	}
}

int VariableCache::GetInt(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(m_variables.begin(), m_variables.end(), [param](auto& var)
			{
				return var->name == param;
			});
		if (iter != m_variables.end())
		{
			return static_cast<IntVar*>((*iter).get())->value;
		}
	}

	return stoi(param);
}

void VariableCache::AddBool(const std::string& name, bool value)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(m_variables.begin(), m_variables.end(), [name](auto& var)
		{
			return var->name == name;
		});
	if (iter == m_variables.end())
	{
		auto boolVar = std::make_unique<BoolVar>();
		boolVar->name = name;
		boolVar->value = value;
		m_variables.emplace_back(std::move(boolVar));
	}
}

bool VariableCache::GetBool(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(m_variables.begin(), m_variables.end(), [param](auto& var)
			{
				return var->name == param;
			});
		if (iter != m_variables.end())
		{
			return static_cast<BoolVar*>((*iter).get())->value;
		}
	}

	return param == "true";
}

void VariableCache::ShowEditor()
{
	if (m_variables.empty())
		return;

	ImGui::Begin("Variables", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	for (auto& var : m_variables)
		var->ShowUI();
	ImGui::End();
}
