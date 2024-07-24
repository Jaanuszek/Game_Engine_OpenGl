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
	VAO vao; // glGenVertexArrays(1, &m_RendererID)
	VBO vbo(vertices);
	VBL layout;
	EBO ebo(indices);
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 3);
	vao.AddBuffer(vbo, layout);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setupMesh();
}

Mesh::~Mesh()
{
}
