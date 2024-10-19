#include "TextureManager.h"

TextureManager::TextureManager(const std::string& directoryPath, std::vector<TextureStruct>& TextureContainer)
	: m_directoryPath(directoryPath), m_vecLoadedTextures(TextureContainer)
{
	LoadTexturesFromDirectory(directoryPath);
	m_vecLoadedTextures.clear();
	m_vecLoadedTextures.push_back(m_vecAllTextures.front());
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
				// ADD HANDLER FOR SPECULAR AND NORMAL TESXTURES
				m_texturesMap[texturePath] = std::make_shared<Texture>(texturePath, "diffuse");
				m_vecAllTextures.push_back(m_texturesMap[texturePath]->GetTextureStruct());
			}
		}
		else {
			std::cout << "[TextureManager::LoadTexturesFromDirectory] " << entry.path().string() << " is not a valid texture file" << std::endl;
			throw std::runtime_error("[TextureManager::LoadTexturesFromDirectory] " + entry.path().string() + " is not a valid texture file");
		}
	}
}
void TextureManager::SetActiveTexture(int currentTextureImGui) {
	TextureStruct selectedTexture;
	if (currentTextureImGui >= 0 && currentTextureImGui < m_vecAllTextures.size()) {
		selectedTexture = m_vecAllTextures.at(currentTextureImGui);
	}
	m_vecLoadedTextures.clear();
	m_vecLoadedTextures.push_back(selectedTexture);
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