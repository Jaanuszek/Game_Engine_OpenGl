#include "Cuboid.h"

void Cuboid::Initalize()
{
	vertices = {
		Vertex{glm::vec3(-m_width,-m_height,-m_depth), glm::vec2(0.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		Vertex{glm::vec3(m_width,-m_height,-m_depth), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		Vertex{glm::vec3(m_width,m_height,-m_depth), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		Vertex{glm::vec3(-m_width,m_height,-m_depth), glm::vec2(0.0f,1.0f), glm::vec3(0.0f,0.0f,-1.0f)},

		Vertex{glm::vec3(-m_width,-m_height,m_depth), glm::vec2(0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
		Vertex{glm::vec3(m_width,-m_height,m_depth), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
		Vertex{glm::vec3(m_width,m_height,m_depth), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f)},
		Vertex{glm::vec3(-m_width,m_height,m_depth), glm::vec2(0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f)},

		Vertex{glm::vec3(-m_width,-m_height,-m_depth), glm::vec2(0.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},
		Vertex{glm::vec3(-m_width,m_height,-m_depth), glm::vec2(1.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},
		Vertex{glm::vec3(-m_width,m_height,m_depth), glm::vec2(1.0f,1.0f), glm::vec3(-1.0f,0.0f,0.0f)},
		Vertex{glm::vec3(-m_width,-m_height,m_depth), glm::vec2(0.0f,1.0f), glm::vec3(-1.0f,0.0f,0.0f)},

		Vertex{glm::vec3(m_width,-m_height,-m_depth), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},
		Vertex{glm::vec3(m_width,m_height,-m_depth), glm::vec2(1.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},
		Vertex{glm::vec3(m_width,m_height,m_depth), glm::vec2(1.0f,1.0f), glm::vec3(1.0f,0.0f,0.0f)},
		Vertex{glm::vec3(m_width,-m_height,m_depth), glm::vec2(0.0f,1.0f), glm::vec3(1.0f,0.0f,0.0f)},

		Vertex{glm::vec3(-m_width,-m_height,-m_depth), glm::vec2(0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		Vertex{glm::vec3(m_width,-m_height,-m_depth), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		Vertex{glm::vec3(m_width,-m_height,m_depth), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		Vertex{glm::vec3(-m_width,-m_height,m_depth), glm::vec2(0.0f,1.0f), glm::vec3(0.0f,-1.0f,0.0f)},

		Vertex{glm::vec3(-m_width,m_height,-m_depth), glm::vec2(0.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
		Vertex{glm::vec3(m_width,m_height,-m_depth), glm::vec2(1.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
		Vertex{glm::vec3(m_width,m_height,m_depth), glm::vec2(1.0f,1.0f), glm::vec3(0.0,1.0f,0.0f)},
		Vertex{glm::vec3(-m_width,m_height,m_depth), glm::vec2(0.0f,1.0f), glm::vec3(0.0,1.0f,0.0f)}
	};
	indices = {
		// Back face
		0, 1, 2,
		2, 3, 0,
		// Front face
		4, 5, 6,
		6, 7, 4,
		// Left face
		8, 9, 10,
		10, 11, 8,
		// Right face
		12, 13, 14,
		14, 15, 12,
		// Bottom face
		16, 17, 18,
		18, 19, 16,
		// Top face
		20, 21, 22,
		22, 23, 20
	};
}

Cuboid::Cuboid(float width, float height, float depth) : m_width(width), m_height(height), m_depth(depth)
{
	Initalize();
}

Cuboid::~Cuboid()
{
}


