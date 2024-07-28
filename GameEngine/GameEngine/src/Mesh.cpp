#include "Mesh.h"



void Mesh::setupMesh()
{
	//VAO vao1;
	////cube
	//VBO vbo1(verticesCu, cube.GetVerticesSize() * sizeof(VertexCube));
	//VBL layout1;
	//layout1.Push(GL_FLOAT, 3);
	//layout1.Push(GL_FLOAT, 2);
	//layout1.Push(GL_FLOAT, 3);
	//layout1.Push(GL_FLOAT, 3); //Lightning purposes 
	//vao1.AddBuffer(vbo1, layout1);
	//EBO ebo1(indicesCube, cube.GetIndicesSize());

	//Shader shader1("res/shaders/LightningShader.shader");
	//shader1.Bind();
	//shader1.SetUniform3f("u_objectColor", 1.0f, 0.2f, 0.8f);
	//shader1.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
	//shader1.SetUniform3f("u_lightPos", lightCubeTranslation);

	//Texture texture1("res/textures/monkey.png");
	//texture1.Bind();
	//shader1.SetUniform1i("u_Texture", 0);

	//vao1.Unbind();
	//vbo1.Unbind();
	//ebo1.Unbind();
	//shader1.Unbind();
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
		shader.SetUniform3f("u_viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
		GLCall(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0));
	}
}
