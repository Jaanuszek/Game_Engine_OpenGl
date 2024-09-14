#include "Torus.h"
#include <iostream>

void Torus::Initalize() {
	float x, y, z, xy; // vertex position
	float nx, ny, nz; // vertex normal
	float lengthInv = 1.0f / m_minorRadius; // vertex normal
	float s, t; // vertex texCoord
	const float PI = glm::pi<float>();

	float sectorStep = 2 * PI / m_sectors;
	float sideStep = 2 * PI / m_sides;
	float sectorAngle, sideAngle;
	if (vertices.size() > 0) {
		vertices.clear();
	}
	unsigned int totalVertices = (m_sides + 1) * (m_sectors + 1);
	vertices.resize(totalVertices);
	std::vector<Vertex>::iterator verticesIt = vertices.begin();
	for (int i = 0; i <= m_sides; i++) {
		sideAngle = PI - i * sideStep; //from PI to -PI
		xy = m_minorRadius * cosf(sideAngle);
		z = m_minorRadius * sinf(sideAngle);
		for (int j = 0; j <= m_sectors; j++) {
			sectorAngle = j * sectorStep; //from 0 to 2pi
			// temp values to calculate normals
			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			//normals
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			// shifting x&y and vertex position
			x += m_majorRadius * cosf(sectorAngle);
			y += m_majorRadius * sinf(sectorAngle);
			//tex coords
			s = (float)j / m_sectors;
			t = (float)i / m_sides;

			(*verticesIt).Position[0] = x;
			(*verticesIt).Position[1] = y;
			(*verticesIt).Position[2] = z;

			(*verticesIt).TexCoords[0] = s;
			(*verticesIt).TexCoords[1] = t;

			(*verticesIt).Normal[0] = nx;
			(*verticesIt).Normal[1] = ny;
			(*verticesIt).Normal[2] = nz;
			verticesIt++;
		}
	}
	if (indices.size() > 0) {
		indices.clear();
	}
	unsigned int totalIndices = m_sides * m_sectors * 6;
	indices.resize(totalIndices);
	std::vector<unsigned int>::iterator indicesIt = indices.begin();
	unsigned int k1, k2;
	for (int i = 0; i < m_sides; i++) {
		k1 = i * (m_sectors + 1);
		k2 = k1 + m_sectors + 1;

		for (int j = 0; j < m_sectors; j++, k1++, k2++) {
			*indicesIt++ = k1;
			*indicesIt++ = k2;
			*indicesIt++ = k1 + 1;
			*indicesIt++ = k1 + 1;
			*indicesIt++ = k2;
			*indicesIt++ = k2 + 1;
		}
	}
}

Torus::Torus(float minorRadius, float majorRadius, unsigned int sectors, unsigned int sides) :
	m_minorRadius(minorRadius), m_majorRadius(majorRadius), m_sectors(sectors), m_sides(sides)
{
	Initalize();
}

Torus::~Torus(){

}

void Torus::Update(float minorRadius, float majorRadius, unsigned int sectors, unsigned int sides){
	m_minorRadius = minorRadius;
	m_majorRadius = majorRadius;
	m_sectors = sectors;
	m_sides = sides;
	Initalize();
}