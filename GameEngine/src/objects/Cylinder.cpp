#include "Cylinder.h"

void Cylinder::Initalize()
{
	vertices.resize(m_sectors * m_stacks);
	std::vector<Vertex>::iterator verticesIt = vertices.begin();

	std::vector<float> unitVertices = getUnitCircleVertices();
}

std::vector<float> Cylinder::getUnitCircleVertices()
{
	const float PI = glm::pi<float>();
	float sectorStep = 2 * PI / m_sectors;
	float sectorAngle; //fi 

	std::vector<float> unitCircleVertices;
	for (int i = 0; i <= m_sectors; i++)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle)); //x
		unitCircleVertices.push_back(sin(sectorAngle)); //y
		unitCircleVertices.push_back(0); //z
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
