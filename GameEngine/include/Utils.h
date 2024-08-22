#ifndef UTILS_H
#define UTILS_H
// I have to create this,because i got circular dependency 
// It will contain defines
#include <glad/glad.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif // !UTILS_H
