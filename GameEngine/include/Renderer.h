#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "VBO.h"

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
	// TODO
	void HandleRendering(Mesh& mesh, std::map<ShaderType, std::shared_ptr<Shader>> chosedShader, const ShadersParams& shaderParams,
		const std::vector<TextureStruct>& updatedTexture);
	void Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const;
};
#endif