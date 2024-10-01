#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "VBO.h"
#include "Texture.h"

class TextureManager{
private:
	std::map<std::string, std::shared_ptr<Texture>> m_texturesMap;
	std::string m_directoryPath;
public:
	TextureManager(const std::string& directoryPath);
	~TextureManager();
	void LoadTexturesFromDirectory(const std::string& directoryPath);
	std::vector<TextureStruct> GetAllTexturesStruct();
	TextureStruct GetTextureStructFromPath(const std::string& path);
};

#endif