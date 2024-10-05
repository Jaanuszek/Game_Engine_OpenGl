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
	std::map<std::string, std::shared_ptr<Model>> GetModelsMap();
	std::vector<Model> GetAllModelsVector();
	std::shared_ptr<Model> GetModelFromPath(const std::string& path);
};

#endif