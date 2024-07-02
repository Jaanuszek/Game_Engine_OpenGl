#pragma once

#include "VAO.h"
#include "VBO.h"
#include "VBL.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"

class RenderObject {
public:
	virtual void Setup() = 0;
	virtual void Render(Shader& shader, Renderer& render, glm::mat4& mvp) = 0;
	virtual ~RenderObject() = default; // virtual destructor, used for polymorphism to make sure that the destructor of the derived class is called
};