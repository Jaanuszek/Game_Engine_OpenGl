#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
}


//dorobic klase mesh, ktora bedzie przechowywala informacje o vao,ebo, shaderze, texture i innych rzeczach
//t¹ klase przekazywac jako argument do funkcji draw
// na podstawie informacji tej klasy bedziemy wiedziec czy obiekt ma byc rysowany przy pomocy indeksowania czy te¿ nie
void Renderer::Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	ebo.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

//void Renderer::Draw(const VAO& vao, const Shader& shader, GLsizei count) const
//{
//	shader.Bind();
//	vao.Bind();
//	GLCall(glDrawArrays(GL_TRIANGLES, 0, count));
//}

//Mesh Renderer::CreateMesh(const Solid& solid, const std::vector<Texture>& textures)
//{
//	std::vector<Vertex> vertices = solid.GetVertices();
//	std::vector<unsigned int> indices = solid.GetIndices();
//	std::vector<Texture> _textures = textures;
//	return Mesh(vertices,indices,_textures);
//}
