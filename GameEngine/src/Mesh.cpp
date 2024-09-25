#include "Mesh.h"

void Mesh::setupMesh()
{
	if (!m_updateVBO) {
		m_VAO->Bind(); // glGenVertexArrays(1, &m_RendererID)
		m_VBO->Bind();
		m_EBO->Bind();
		m_layout->Push(GL_FLOAT, 3);
		m_layout->Push(GL_FLOAT, 2);
		m_layout->Push(GL_FLOAT, 3);
		m_VAO->AddBuffer(*m_VBO, *m_layout);
		m_EBO->Unbind();
		m_VBO->Unbind();
		m_VAO->Unbind();
	}
	else {
		m_VBO->Bind();
		m_EBO->Bind();
		m_VBO->Update(m_vertices);
		m_EBO->Update(m_indices);
	}
}

void Mesh::setupMeshStruct() {
	if (!m_updateVBO) {
		m_VAO->Bind();
		m_VBO->Bind();
		m_EBO->Bind();
		m_layout->Push(GL_FLOAT, 3);
		m_layout->Push(GL_FLOAT, 2);
		m_layout->Push(GL_FLOAT, 3);
		m_VAO->AddBuffer(*m_VBO, *m_layout);
		m_EBO->Unbind();
		m_VBO->Unbind();
		m_VAO->Unbind();
	}
	else {
		m_VBO->Bind();
		m_EBO->Bind();
		m_VBO->Update(m_vertices);
		m_EBO->Update(m_indices);
	}
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_textures = textures;
	m_VAO = std::make_shared<VAO>();
	m_VBO = std::make_shared<VBO>(m_vertices);
	m_layout = std::make_shared<VBL>();
	m_EBO = std::make_shared<EBO>(m_indices);
	setupMesh();
	m_updateVBO = true;
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<TextureStruct>& textures)
{
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_texturesStruct = textures;
	m_VAO = std::make_shared<VAO>();
	m_VBO = std::make_shared<VBO>(m_vertices);
	m_layout = std::make_shared<VBL>();
	m_EBO = std::make_shared<EBO>(m_indices);
	setupMeshStruct();
	m_updateVBO = true;
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Bind();
	m_VAO->Bind();

	unsigned int  numDiffuse = 0;
	unsigned int  numSpecular = 0;

	for (unsigned int i = 0; i < m_textures.size(); i++) {
		if (i >= m_textures.size()) {
			break;
		}
		//glActiveTexture(GL_TEXTURE0 + i);
		std::string num;
		std::string type = m_textures[i].GetType();
		if(type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if(type == "specular") {
			num = std::to_string(numSpecular++);
		}
		shader.SetUniform1f(("material." + type + num).c_str(), i);
		m_textures[i].Bind(i);
		shader.SetUniform1i((type+num).c_str(), i);
		//shader.SetUniform3f("u_viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
		shader.SetUniform3f("u_viewPos", camera.GetCameraPos());
	}
	GLCall(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0));
	//Do I need this unbids?
	for (unsigned int i = 0; i < m_textures.size(); i++) {
		m_textures[i].Unbind();
	}
	shader.Unbind();
	m_VAO->Unbind();
}
void Mesh::DrawStruct(Shader& shader, Camera& camera) {
	shader.Bind();
	m_VAO->Bind();

	unsigned int  numDiffuse = 1;
	unsigned int  numSpecular = 1;

	for (unsigned int i = 0; i < m_texturesStruct.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string num;
		std::string type = m_texturesStruct[i].type;
		if (type == "texture_diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "texture_specular") {
			num = std::to_string(numSpecular++);
		}
		shader.SetUniform1f(("material." + type + num).c_str(), i);
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texturesStruct[i].id));
		shader.SetUniform1i((type + num).c_str(), i);
	}
	glActiveTexture(GL_TEXTURE0);
	m_VAO->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0));
	shader.Unbind();
	m_VAO->Unbind();
}
void Mesh::updateMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures) {
	m_vertices = vertices;
	m_indices = indices;
	m_textures = textures;
	setupMesh();
}
void Mesh::updateMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<TextureStruct>& textures) {
	m_vertices = vertices;
	m_indices = indices;
	m_texturesStruct = textures;
	setupMeshStruct();
}