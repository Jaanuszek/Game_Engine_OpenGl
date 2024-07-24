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


class Mesh {
private:
	//VAO m_VAO;
	//VBO m_VBO;
	//EBO m_EBO;
	//GLsizei m_Count;

	//unsigned int VAO, VBO, EBO;
	void setupMesh();
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	~Mesh();
	void Draw(Shader& shader, Camera& camera);	

};

#endif