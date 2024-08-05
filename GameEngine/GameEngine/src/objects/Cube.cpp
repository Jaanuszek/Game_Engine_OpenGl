#include "Cube.h"

void Cube::Initalize()
{
	//	vertices[4*6] = {
	//	Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},
	//	Vertex {glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},
	//	Vertex {glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,0.0f,-1.0f)},
	//	Vertex {glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,0.0f,-1.0f)},

	//	Vertex {glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
	//	Vertex {glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
	//	Vertex {glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f)},
	//	Vertex {glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,0.0f,1.0f)},

	//	Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},
	//	Vertex {glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(-1.0f,0.0f,0.0f)},
	//	Vertex {glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(-1.0f,0.0f,0.0f)},
	//	Vertex {glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},

	//	Vertex {glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},
	//	Vertex {glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(1.0f,0.0f,0.0f)},
	//	Vertex {glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(1.0f,0.0f,0.0f)},
	//	Vertex {glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},

	//	Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
	//	Vertex {glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
	//	Vertex {glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
	//	Vertex {glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,-1.0f,0.0f)},

	//	Vertex {glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
	//	Vertex {glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
	//	Vertex {glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0,1.0f,0.0f)},
	//	Vertex {glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0,1.0f,0.0f)}
	//};
	//indices[24] = {
	//	// Back face
	//	0, 1, 2,
	//	2, 3, 0,
	//	// Front face
	//	4, 5, 6,
	//	6, 7, 4,
	//	// Left face
	//	8, 9, 10,
	//	10, 11, 8,
	//	// Right face
	//	12, 13, 14,
	//	14, 15, 12,
	//	// Bottom face
	//	16, 17, 18,
	//	18, 19, 16,
	//	// Top face
	//	20, 21, 22,
	//	22, 23, 20
	//};
}

Cube::Cube()
{
	Initalize();
}

Cube::~Cube()
{
}
