#pragma once

class Cube{
private:
	//float verticesCube[8 * 8] = {
	//	-0.5f,-0.5f,-0.5f, 0.0f,0.0f, 1.0f,0.0f,0.0f, //left bottom back 0
	//	0.5f, -0.5f,-0.5f, 1.0f,0.0f, 0.0f,1.0f,0.0f, //right bottom back 1
	//	0.5f,  0.5f,-0.5f, 1.0f,1.0f, 0.0f,0.0f,1.0f, //right top back 2
	//	-0.5f, 0.5f,-0.5f, 0.0f,1.0f, 0.5f,0.5f,0.5f, //left top back 3

	//	-0.5f,-0.5f,0.5f, 0.0f,0.0f, 0.2f,0.5f,0.7f, //left bottom front 4
	//	0.5f, -0.5f,0.5f, 1.0f,0.0f, 1.0f,1.0f,0.0f, //right bottom front 5
	//	0.5f,  0.5f,0.5f, 1.0f,1.0f, 0.0f,1.0f,1.0f, //right top front	6
	//	-0.5f, 0.5f,0.5f, 0.0f,1.0f, 0.7f,0.5f,0.2f //left top front	7
	//};

	//unsigned int indicesCube[3 * 12] = {
	//	//back wall
	//	0,1,2,
	//	2,3,0,
	//	//front wall
	//	4,5,6,
	//	6,7,4,
	//	//left wall
	//	0,3,7,
	//	7,4,0,
	//	//right wall
	//	1,2,6,
	//	6,5,1,
	//	//bottom wall
	//	0,1,5,
	//	5,4,0,
	//	//top wall
	//	3,2,6,
	//	6,7,3
	//};
	float verticesCube[6 * 4 * 8] = {
		// Back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left bottom back
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // right bottom back
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // right top back
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f, // left top back

		// Front face
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.2f, 0.5f, 0.7f, // left bottom front
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // right bottom front
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // right top front
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.7f, 0.5f, 0.2f, // left top front

		// Left face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left bottom back
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, // left top back
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.7f, 0.5f, 0.2f, // left top front
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 0.7f, // left bottom front

		// Right face
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // right bottom back
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // right top back
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // right top front
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // right bottom front

		 // Bottom face
		 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left bottom back
		  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // right bottom back
		  0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // right bottom front
		 -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 0.7f, // left bottom front

		 // Top face
		 -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, // left top back
		  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // right top back
		  0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // right top front
		 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.7f, 0.5f, 0.2f  // left top front
	};

	unsigned int indicesCube[6 * 2 * 3] = {
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
public:
	const float* GetVertices(void) const {
		return verticesCube;
	}
	const unsigned int* GetIndices(void) const {
		return indicesCube;
	}
	const unsigned int GetVerticesSize(void) const {
		return sizeof(verticesCube)/sizeof(float);
	}
	const unsigned int GetIndicesSize(void) const {
		return sizeof(indicesCube)/sizeof(unsigned int);
	}
};