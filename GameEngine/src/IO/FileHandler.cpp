#include "FileHandler.h"

std::vector<std::string> FileHandler::getFilesNamesFromDirectory(const std::string& pathToModels)
{
	std::vector<std::string> stringFilesNames;
	for (const auto& entry : std::filesystem::directory_iterator(pathToModels)) {
		std::string fileName = entry.path().filename().string();
		fileName = fileName.substr(0, fileName.find_last_of('.'));
		stringFilesNames.push_back(fileName);
	}
	return stringFilesNames;
}