#pragma once

#include "VAO.h"
#include "VBO.h"
#include "VBL.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"

class Rendering {
public:
	virtual void Setup() = 0;
	virtual void Render(Shader& shader, Renderer& render, glm::mat4& mvp) = 0;
	virtual ~Rendering() = default; // virtual destructor, used for polymorphism to make sure that the destructor of the derived class is called
};