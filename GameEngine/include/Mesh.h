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

class Mesh {
private:
	std::shared_ptr<VAO> m_VAO;
	std::shared_ptr<VBO> m_VBO;
	std::shared_ptr<VBL> m_layout;
	std::shared_ptr<EBO> m_EBO;
	bool m_updateVBO = false;
	void setupMesh();
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;
	
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures); //ew tu moze byc problem bo usunalem referencj
	~Mesh();
	void Draw(Shader& shader, Camera& camera);
	void updateMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
};

#endif