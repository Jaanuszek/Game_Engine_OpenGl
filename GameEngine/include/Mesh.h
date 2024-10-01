#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <vector>

#include <glad/glad.h>
#include "VAO.h"
//#include "VBO.h" // VBO is included in VAO
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "VBL.h"
#include <memory>

#include "objects/Solid.h"

class Mesh {
private:
	std::shared_ptr<VAO> m_VAO;
	std::shared_ptr<VBO> m_VBO;
	std::shared_ptr<VBL> m_layout;
	std::shared_ptr<EBO> m_EBO;
	bool m_updateVBO = false;
	void setupMesh();
	void setupMeshStruct();
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;
	std::vector<TextureStruct> m_texturesStruct;
	
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<TextureStruct>& textures);
	Mesh(Solid& solid, const std::vector<TextureStruct>& textures);
	~Mesh();
	void Draw(Shader& shader, Camera& camera);
	void DrawStruct(Shader& shader, Camera& camera);
	void updateMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	void updateMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<TextureStruct>& textures);
	void updateTexture(const std::vector<TextureStruct>& textures);
};

#endif