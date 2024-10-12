#include "TextureManager.h"

TextureManager::TextureManager(const std::string& directoryPath) : m_directoryPath(directoryPath)
{
	LoadTexturesFromDirectory(directoryPath);
}

TextureManager::~TextureManager()
{
}

void TextureManager::LoadTexturesFromDirectory(const std::string& directoryPath) {
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
		if (entry.exists() && entry.is_regular_file() && entry.path().extension() == ".png") {
			std::string texturePath = entry.path().string();
			std::cout << "[TextureManager::LoadTexturesFromDirectory] Loading texture: " << texturePath << std::endl;
			if (m_texturesMap.find(texturePath) == m_texturesMap.end()) {
				// for now it will be only diffuse, because I do not use any other texture type
				m_texturesMap[texturePath] = std::make_shared<Texture>(texturePath, "diffuse");
			}
		}
		else {
			std::cout << "[TextureManager::LoadTexturesFromDirectory] " << entry.path().string() << " is not a valid texture file" << std::endl;
			throw std::runtime_error("[TextureManager::LoadTexturesFromDirectory] " + entry.path().string() + " is not a valid texture file");
		}
	}
}
void TextureManager::SetActiveTexture(int currentTextureImGui, const std::vector<TextureStruct>& allTextures,
	std::vector<TextureStruct>& vecSelectedTexture, TextureStruct& structSelectedTexture) {
	if (currentTextureImGui >= 0 && currentTextureImGui < allTextures.size()) {
		structSelectedTexture = allTextures.at(currentTextureImGui);
	}
	vecSelectedTexture.clear();
	vecSelectedTexture.push_back(structSelectedTexture);
}
std::vector<TextureStruct> TextureManager::GetAllTexturesStruct() {
	std::vector<TextureStruct> texturesStruct;
	for (auto& texture : m_texturesMap) {
		texturesStruct.push_back(texture.second->GetTextureStruct());
	}
	return texturesStruct;
}

TextureStruct TextureManager::GetTextureStructFromPath(const std::string& path) {
	try {
		if (m_texturesMap.find(path) != m_texturesMap.end()) {
			return m_texturesMap[path]->GetTextureStruct();
		}
		throw std::runtime_error("[TextureManager::GetTextureStructFromPath] Texture with path: " + path + " does not exist");
	}
	catch (const std::runtime_error& e) {
		std::cerr << "[TextureManager::GetTextureStructFromPath] "<< e.what() << std::endl;
		return TextureStruct();
	}
}