#include "Cylinder.h"
#include <iostream>

// in case of any problems take a look at the post incremented values in loops, maybe it will be better if they were pre incremented

void Cylinder::Initalize()
{
	int verticesSize = (m_sectors + 1) * 4; // 2 for top and bottom center points, 2 for top and bottom circle vertices
	vertices.resize(verticesSize);
    std::vector<Vertex>::iterator verticesIt = vertices.begin();
    std::vector<float> unitVertices = getUnitCircleVertices();
	//code for generating the walls of cylinder
	for (int i = 0; i < 2; i++) { //for positive and negative height
		float h = -m_height / 2.0f + i * m_height;
		float t = 1.0f - i; //tex cord [1,0]
		for (int j = 0, k = 0; j <= m_sectors; j++, k += 3) {
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			float uz = unitVertices[k + 2];
			(*verticesIt).Position[0] = ux * m_radius;
			(*verticesIt).Position[1] = uy * m_radius;
			(*verticesIt).Position[2] = h;
			(*verticesIt).TexCoords[0] = (float)j / m_sectors;
			(*verticesIt).TexCoords[1] = t;
			(*verticesIt).Color[0] = 1;
			(*verticesIt).Color[1] = 0.5;
			(*verticesIt).Color[2] = 0.5;
			(*verticesIt).Normal[0] = ux;
			(*verticesIt).Normal[1] = uy;
			(*verticesIt).Normal[2] = uz;
			verticesIt++;
		}
	}
	//these indexes are wrong, baseCenterIndex should be exactly in the middle of the vertices
	int baseCenterIndex = verticesSize / 2;
	int topCenterIndex = baseCenterIndex + m_sectors + 1;

	for (int i = 0; i < 2; i++) {
		float h = -m_height / 2.0f + i * m_height; //z value in terms -h/2, h/2
		float nz = -1 + i * 2;						// z value of normal [-1, 1]
		//coords of center point
		(*verticesIt).Position[0] = 0;
		(*verticesIt).Position[1] = 0;
		(*verticesIt).Position[2] = 0;
		(*verticesIt).TexCoords[0] = 0.5f;
		(*verticesIt).TexCoords[1] = 0.5f;
		(*verticesIt).Color[0] = 1;
		(*verticesIt).Color[1] = 0.5;
		(*verticesIt).Color[2] = 0.5;
		(*verticesIt).Normal[0] = 0;
		(*verticesIt).Normal[1] = 0;
		(*verticesIt).Normal[2] = 0;
		verticesIt++;
		for (int j = 0, k = 0; j < m_sectors; ++j, k += 3) {
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			(*verticesIt).Position[0] = ux * m_radius;
			(*verticesIt).Position[1] = uy * m_radius;
			(*verticesIt).Position[2] = h;
			(*verticesIt).TexCoords[0] = -ux * 0.5f +0.5f;
			(*verticesIt).TexCoords[1] = -uy * 0.5f + 0.5f;
			(*verticesIt).Color[0] = 1;
			(*verticesIt).Color[1] = 0.5;
			(*verticesIt).Color[2] = 0.5;
			(*verticesIt).Normal[0] = 0;
			(*verticesIt).Normal[1] = 0;
			(*verticesIt).Normal[2] = nz;
			verticesIt++;
		}
	}
	indices.resize(m_sectors * 6 * 2);
	std::vector<unsigned int>::iterator indicesIt = indices.begin();
	int k1 = 0; //1st vertex index at base
	int k2 = m_sectors + 1; //1st vertex index at top
	//side indices
	for (int i = 0; i < m_sectors; i++, k1++, k2++) {
		//creation of quads
		//first triangle
		*indicesIt++ = k1;
		*indicesIt++ = k1 + 1;
		*indicesIt++ = k2;
		//second triangle
		*indicesIt++ = k2;
		*indicesIt++ = k1 + 1;
		*indicesIt++ = k2 + 1;
		//the result is 2 triangles per sector
	}

	for (int i = 0, k = baseCenterIndex + 1; i < m_sectors; i++, k++) {
		if (i < m_sectors - 1) {
			*indicesIt++ = baseCenterIndex;
			*indicesIt++ = k + 1;
			*indicesIt++ = k;
		}
		else { //last triangle
			*indicesIt++ = baseCenterIndex;
			*indicesIt++ = baseCenterIndex + 1;
			*indicesIt++ = k;
		}
	}
	for (int i = 0, k = topCenterIndex + 1; i < m_sectors; i++, k++) {
		if (i < m_sectors - 1) {
			*indicesIt++ = topCenterIndex;
			*indicesIt++ = k;
			*indicesIt++ = k + 1;
		}
		else { //last triangle
			*indicesIt++ = topCenterIndex;
			*indicesIt++ = k;
			*indicesIt++ = topCenterIndex + 1;
		}
	}
}

std::vector<float> Cylinder::getUnitCircleVertices()
{
	const float PI = glm::pi<float>();
	const float sectorStep = 2 * PI / m_sectors; //360 / m_sectors
    float sectorAngle;

    std::vector<float> unitCircleVertices;
    for (int i = 0; i <= m_sectors; ++i) {
        sectorAngle = i * sectorStep; // fi
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(sin(sectorAngle)); // y 
		unitCircleVertices.push_back(0);                // 0 because i want to render xy plane
    }
    return unitCircleVertices;
}

Cylinder::Cylinder(float radius, float height, unsigned int m_sectors) : m_radius(radius), m_height(height), m_sectors(m_sectors)
{
	Initalize();
}

Cylinder::~Cylinder()
{
}
