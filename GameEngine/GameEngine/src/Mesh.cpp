#include "Mesh.h"



void Mesh::setupMesh()
{
	m_VAO.Bind(); // glGenVertexArrays(1, &m_RendererID)
	VBO vbo(m_vertices);
	VBL layout;
	EBO ebo(m_indices);
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 3);
	m_VAO.AddBuffer(vbo, layout);

	m_VAO.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_textures = textures;
	setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Bind();
	m_VAO.Bind();

	unsigned int  numDiffuse = 0;
	unsigned int  numSpecular = 0;

	for (unsigned int i = 0; i < m_textures.size(); i++) {
		if (i >= m_textures.size()) {
			break;
		}
		std::string num;
		std::string type = m_textures[i].GetType();
		if(type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if(type == "specular") {
			num = std::to_string(numSpecular++);
		}
		m_textures[i].Bind(i);
		shader.SetUniform1i((type+num).c_str(), i);
		//shader.SetUniform3f("u_viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
		shader.SetUniform3f("u_viewPos", camera.GetCameraPos());
	}
	GLCall(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0));
	m_VAO.Unbind();
}

//Mesh Mesh::CreateMesh(const Solid& solid, const std::vector<Texture>& textures)
//{
//	std::vector<Vertex> vertices = solid.GetVertices();
//	std::vector<unsigned int> indices = solid.GetIndices();
//	std::vector<Texture> _textures = textures;
//	return Mesh(vertices,indices,_textures);
//}

