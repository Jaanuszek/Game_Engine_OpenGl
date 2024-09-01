#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "VAO.h";
#include "EBO.h";
#include "Shader.h";
//#include "Mesh.h";


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer { // tu jest opcja na wzorzec singletona
public:
	void Clear() const;
	void Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const;
	//void Draw(const VAO& vaa, const Shader& shader, GLsizei count) const;
	//Mesh CreateMesh(const Solid& solid, const std::vector<Texture>& textures);
};
#endif