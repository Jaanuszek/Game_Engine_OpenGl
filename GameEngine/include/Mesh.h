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
#include "objects/Solid.h"


class Mesh {
private:
	VAO m_VAO;
	void setupMesh();
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;
	
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures); //ew tu moze byc problem bo usunalem referencj
	~Mesh();
	void Draw(Shader& shader, Camera& camera);
};

#endif