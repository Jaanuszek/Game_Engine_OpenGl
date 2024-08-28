#include "Cylinder.h"
#include <iostream>

void Cylinder::Initalize()
{
    vertices.resize((m_sectors + 1) * 2 + 2); // (m_sectors + 1) vertices per circle, 2 circles, and 2 center vertices
    std::vector<Vertex>::iterator verticesIt = vertices.begin();

    // Generate the unit circle vertices
    std::vector<float> unitVertices = getUnitCircleVertices();

    // Generate vertices for the cylinder's sides
    for (int i = 0; i < 2; i++) {
        float h = -m_height / 2.0f + i * m_height; // -h/2 or h/2 for bottom and top circles
        float t = 1.0f - i;

        for (int j = 0; j <= m_sectors; j++) { // <= to include the last point connecting back to the first
            float const x = unitVertices[j * 3];
            float const z = unitVertices[j * 3 + 2];
            float const u = (float)j / m_sectors;
            float const v = t;

            (*verticesIt).Position[0] = x * m_radius;
            (*verticesIt).Position[1] = h; // height for top or bottom circle
            (*verticesIt).Position[2] = z * m_radius;

            (*verticesIt).TexCoords[0] = u;
            (*verticesIt).TexCoords[1] = v;

            (*verticesIt).Color[0] = (x + 1) * 0.5f;
            (*verticesIt).Color[1] = 0.5f;
            (*verticesIt).Color[2] = (z + 1) * 0.5f;

            (*verticesIt).Normal[0] = x;
            (*verticesIt).Normal[1] = 0.0f;
            (*verticesIt).Normal[2] = z;
            verticesIt++;
        }
    }

    // Add the top and bottom center vertices
    (*verticesIt).Position[0] = 0.0f;
    (*verticesIt).Position[1] = -m_height / 2.0f; // bottom center
    (*verticesIt).Position[2] = 0.0f;
    verticesIt++;

    (*verticesIt).Position[0] = 0.0f;
    (*verticesIt).Position[1] = m_height / 2.0f; // top center
    (*verticesIt).Position[2] = 0.0f;

    verticesIt++;

    // Indexing
    int baseCenterIndex = (int)vertices.size() - 2;
    int topCenterIndex = (int)vertices.size() - 1;

    indices.resize(m_sectors * 6 + m_sectors * 3 * 2); // Correct index buffer size
    std::vector<unsigned int>::iterator indicesIt = indices.begin();

    // Side faces (quads)
    int k1 = 0;
    int k2 = m_sectors + 1; // Next circle offset

    for (int i = 0; i < m_sectors; i++, k1++, k2++) {
        *indicesIt++ = k1;
        *indicesIt++ = k1 + 1;
        *indicesIt++ = k2;
        *indicesIt++ = k2;
        *indicesIt++ = k1 + 1;
        *indicesIt++ = k2 + 1;
    }

    // Bottom face
    for (int i = 0; i < m_sectors; i++) {
        *indicesIt++ = baseCenterIndex;
        *indicesIt++ = i;
        *indicesIt++ = (i + 1) % (m_sectors + 1); // Correct wrap-around to the first vertex
    }

    // Top face
    for (int i = 0; i < m_sectors; i++) {
        *indicesIt++ = topCenterIndex;
        *indicesIt++ = k2 + i;
        *indicesIt++ = k2 + (i + 1) % (m_sectors + 1);
    }
}

std::vector<float> Cylinder::getUnitCircleVertices()
{
	const float PI = glm::pi<float>();
    std::vector<float> unitVertices;
    const float sectorStep = 2 * PI / m_sectors;
    for (int i = 0; i <= m_sectors; ++i) {
        float sectorAngle = i * sectorStep;
        unitVertices.push_back(cos(sectorAngle)); // x
        unitVertices.push_back(0);                // y, it's 0 since we're in the XZ plane
        unitVertices.push_back(sin(sectorAngle)); // z
    }
    return unitVertices;
}

Cylinder::Cylinder(float radius, float height, unsigned int m_sectors) : m_radius(radius), m_height(height), m_sectors(m_sectors)
{
	Initalize();
}

Cylinder::~Cylinder()
{
}
