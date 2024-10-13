#include "Renderer.h"

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
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::ShowGridLine()const {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void Renderer::ShowGridPoint()const {
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}
void Renderer::DisableGrid()const {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	ebo.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr));
}
