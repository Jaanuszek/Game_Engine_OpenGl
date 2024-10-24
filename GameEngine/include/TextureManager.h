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
	std::vector<TextureStruct>& m_vecLoadedTextures;
	std::vector<TextureStruct> m_vecAllTextures;
public:
	TextureManager(const std::string& directoryPath, std::vector<TextureStruct>& TextureContainer);
	~TextureManager();
	void LoadTexturesFromDirectory(const std::string& directoryPath);
	void SetActiveTexture(int currentTextureImGui);
	std::vector<TextureStruct> GetAllTexturesStruct() { return m_vecAllTextures; }
	TextureStruct GetTextureStructFromPath(const std::string& path);
};

#endif