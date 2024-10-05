#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include "VBO.h"
#include "stb_image.h"
#include "Renderer.h"

class Texture {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	const char* m_type;
	TextureStruct m_textureStruct;
public:
	Texture(const std::string& path, const char* texType);
	//Default constructor because of the TextureManager map
	Texture();
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	TextureStruct GetTextureStruct() const { return m_textureStruct; }

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline const char* GetType() const { return m_type; }

	static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
};
#endif