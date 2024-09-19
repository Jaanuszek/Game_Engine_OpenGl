#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "VAO.h";
#include "EBO.h";
#include "Shader.h";

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer { // tu jest opcja na wzorzec singletona
public:
	void Clear() const;
	void ShowGridLine() const;
	void ShowGridPoint() const;
	void DisableGrid() const;
	void Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const;
};
#endif