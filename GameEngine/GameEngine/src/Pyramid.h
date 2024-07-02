#pragma once

class Pyramid {
private:
	float verticesPyramid[8*5] = {
		//adding colors as layout 2
		-0.5f,-0.5f,-0.5f,0.0f,0.0f, 1.0f,0.0f,0.0f, //left bottom back 0
		0.5f,-0.5f,-0.5f,1.0f,0.0f, 0.0f, 1.0f, 0.0f, //right bottom back 1
		0.5f,0.5f,-0.5f,1.0f,1.0f, 0.0f, 0.0f,1.0f, //right top back 2
		-0.5f,0.5f,-0.5f,0.0f,1.0f, 0.5f,0.5f,0.5f, //left top back 3

		0.0f,0.0f,0.5f,0.5f,0.5f, 1.0f,1.0f,0.0f //top of the pyramid 4
	};
	unsigned int indicesPyramid[3*6] = {
		//back wall
		0,1,2,
		2,3,0,
		//left wall
		0,3,4,
		//right wall
		1,2,4,
		//front wall
		0,1,4,
		2,3,4
	};
public:
	const float* GetVertices(void) const {
		return verticesPyramid;
	}
	const unsigned int* GetIndices(void) const {
		return indicesPyramid;
	}
};