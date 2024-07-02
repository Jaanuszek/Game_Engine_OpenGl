#include "Cube.h"

Cube::Cube(VAO& vao, VBO& vbo, VBL& layout, EBO& ebo) : m_vao(vao), m_vbo(vbo), m_layout(layout), m_ebo(ebo)
{
	Setup();
}

void Cube::Setup()
{
	m_vbo.Update(verticesCube, sizeof(verticesCube));
	m_ebo.Update(indicesCube, sizeof(indicesCube)/sizeof(unsigned int));
	m_layout.Push(3, GL_FLOAT);
	m_layout.Push(2, GL_FLOAT);
	m_layout.Push(3, GL_FLOAT);
	m_vao.AddBuffer(m_vbo, m_layout);
}

void Cube::Render(Shader& shader, Renderer& render, glm::mat4& mvp)
{
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
}
