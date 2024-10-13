#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include <filesystem>

class FileHandler {
public:
	static std::vector<std::string> getFilesNamesFromDirectory(const std::string& pathToModels);
};

#endif