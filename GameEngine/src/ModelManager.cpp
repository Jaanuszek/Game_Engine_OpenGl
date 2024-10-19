#include "ModelManager.h"

ModelManager::ModelManager(const std::string& directoryPath, std::shared_ptr<Model>& selectedModel) \
	: m_DirectoryPath(directoryPath), m_selectedModel(selectedModel){
	LoadModelsFromDirectory(directoryPath);
	m_selectedModel = std::make_shared<Model>(m_vectorModels.front());
}
ModelManager::~ModelManager() {

}
void ModelManager::LoadModelsFromDirectory(const std::string& directoryPath) {
	// Going through all directories
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
		if (entry.exists() && entry.is_directory()) {
			// Going into a directory
			std::string stringDirectoryPath = entry.path().string();
			std::cout << "[ModelManager::LoadModelsFromDirectory] Loading models from directory: " << stringDirectoryPath << std::endl;
			for(const auto& entryInDirectory : std::filesystem::directory_iterator(entry.path())){
				if (entryInDirectory.exists() && entryInDirectory.is_regular_file() && entryInDirectory.path().extension() == ".obj") {
					std::string stringModelObjectPath = entryInDirectory.path().string();
					std::replace(stringModelObjectPath.begin(), stringModelObjectPath.end(), 92, 47);
					std::cout << "[ModelManager::LoadModelsFromDirectory] Loading model: " << stringModelObjectPath << std::endl;
					if (m_mapModels.find(stringModelObjectPath) == m_mapModels.end()) {
						m_mapModels[stringModelObjectPath] = std::make_shared<Model>(stringModelObjectPath.c_str());
						m_vectorModels.push_back(*m_mapModels[stringModelObjectPath]);
					}
				}
			}
		}
		else if (!entry.exists()){
			throw std::runtime_error("[ModelManager::LoadModelsFromDirectory] " + entry.path().string() + " is not a valid directory");
		}
		else {
			std::cout << "[ModelManager::LoadModelsFromDirectory] " << entry.path().string() << " is not a valid directory" << std::endl;
		}
	}
}
void ModelManager::SetActiveCustomModel(int currentCustomModel, const std::vector<Model>& allModelsVec, Model& selectedModel) {
	if (currentCustomModel >= 0 && currentCustomModel < allModelsVec.size()) {
		selectedModel = allModelsVec.at(currentCustomModel);
	}
}
void ModelManager::SetActiveCustomModel(int currentCustomModel) {
	if (currentCustomModel >= 0 && currentCustomModel < m_vectorModels.size()) {
		*m_selectedModel = m_vectorModels.at(currentCustomModel);
	}
}
std::shared_ptr<Model> ModelManager::GetModelFromPath(const std::string& path) {
	try {
		if (m_mapModels.find(path) != m_mapModels.end()) {
			return m_mapModels[path];
		}
		else {
			std::cout << "[ModelManager::GetModelFromPath] Model with path: " << path << " does not exist" << std::endl;
			return nullptr;
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << "[ModelManager::GetModelFromPath] " << e.what() << std::endl;
		return nullptr;
	}
}