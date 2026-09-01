#include "ModelManager.h"

ModelManager* ModelManager::Get()
{
	static ModelManager s_instance;
	return &s_instance;
}

void ModelManager::Clear()
{
	m_models.clear();
}

const Model* ModelManager::GetModel(const std::string& fileName)
{
	auto iter = std::find_if(m_models.begin(), m_models.end(), [fileName](auto& model)	{
		return model->GetFileName() == fileName;
		});

	if (iter != m_models.end())
	{
		return iter->get();
	}
	auto& model = m_models.emplace_back(std::make_unique<Model>());
	model->Load(fileName);
	return model.get();
}
