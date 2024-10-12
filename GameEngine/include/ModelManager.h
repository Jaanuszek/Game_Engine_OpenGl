#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <string>
#include <map>
#include <filesystem>

#include "Model.h"

class ModelManager {
private:
	std::map<std::string, std::shared_ptr<Model>> m_mapModels;
	std::vector<Model> m_vectorModels;
	std::string m_DirectoryPath;
public:
	ModelManager(const std::string& directoryPath);
	~ModelManager();
	void LoadModelsFromDirectory(const std::string& directoryPath);
	static void SetActiveCustomModel(int currentCustomModel, const std::vector<Model>& allModelsVec, Model& selectedModel);
	std::map<std::string, std::shared_ptr<Model>> GetModelsMap() { return m_mapModels; }
	std::vector<Model> GetAllModelsVector() { return m_vectorModels; }
	std::shared_ptr<Model> GetModelFromPath(const std::string& path);
};

#endif