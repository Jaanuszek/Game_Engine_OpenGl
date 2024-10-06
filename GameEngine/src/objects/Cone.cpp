#include "Cone.h"

std::vector<float> Cone::getSideNormals() {
	//const float PI = glm::pi<float>(); //acos(-1.0f) == pi interesting
	float sectorStep = 2 * PI / m_sectors;
	float sectorAngle;
	std::vector<float> sideNormals;
	sideNormals.reserve(m_sectors * 3 + 3);

	float zAngle = atan2(m_radius, m_height); // angle between the height and the side wall of the cone (APEX)
	float x0 = cos(zAngle); // x value of the normal
	float z0 = sin(zAngle); // y value of the normal

	for (int i = 0; i <= m_sectors; i++) {
		sectorAngle = i * sectorStep;
		sideNormals.emplace_back(x0 * cos(sectorAngle));
		sideNormals.emplace_back(x0 * sin(sectorAngle));
		sideNormals.emplace_back(z0);
	}
	return sideNormals;
}

void Cone::Initalize()
{
	float x, y, z;
	float radius;
	std::vector<float> unitCircleVertices = getUnitCircleVertices(m_sectors);
	std::vector<float> sideNormals = getSideNormals();
	vertices.clear();
	// Total body vertices = (m_stacks + 1) * (m_sectors + 1)
	// Base has a center vertex and one vertex per sector around the base 1 + m_sectors
	unsigned int totalVertices = (m_stacks + 1) * (m_sectors + 1) + 1 + m_sectors;
	vertices.resize(totalVertices);
	std::vector<Vertex>::iterator verticesIt = vertices.begin();
	unsigned int baseVertexIndex = 0;
	for (int i = 0; i <= m_stacks; i++) {
		z = -(m_height / 2.0f) + (float)i / m_stacks * m_height;
		radius = m_radius * (1.0f - (float)i / m_stacks);
		float t = 1.0f - (float)i / m_stacks;
		for (int j = 0, k = 0; j <= m_sectors; j++, k += 3) {
			x = unitCircleVertices[k];
			y = unitCircleVertices[k + 1];
			if (verticesIt == vertices.end()) {
				break;
			}
			(*verticesIt).Position[0] = x * radius;
			(*verticesIt).Position[1] = y * radius;
			(*verticesIt).Position[2] = z;
			(*verticesIt).TexCoords[0] = (float)j / m_sectors;
			(*verticesIt).TexCoords[1] = t;
			(*verticesIt).Normal[0] = sideNormals[k];
			(*verticesIt).Normal[1] = sideNormals[k + 1];
			(*verticesIt).Normal[2] = sideNormals[k + 2];
			verticesIt++;
			baseVertexIndex++;
		}
	}

	z = -m_height * 0.5f;
	(*verticesIt).Position[0] = 0;
	(*verticesIt).Position[1] = 0;
	(*verticesIt).Position[2] = z;
	(*verticesIt).TexCoords[0] = 0.5f;
	(*verticesIt).TexCoords[1] = 0.5f;
	(*verticesIt).Normal[0] = 0;
	(*verticesIt).Normal[1] = 0;
	(*verticesIt).Normal[2] = -1;
	verticesIt++;
	for (int i = 0, j = 0; i < m_sectors; i++, j += 3) {
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		(*verticesIt).Position[0] = x * m_radius;
		(*verticesIt).Position[1] = y * m_radius;
		(*verticesIt).Position[2] = z;
		(*verticesIt).TexCoords[0] = -x * 0.5f + 0.5f;
		(*verticesIt).TexCoords[1] = -y * 0.5f + 0.5f;
		(*verticesIt).Normal[0] = 0;
		(*verticesIt).Normal[1] = 0;
		(*verticesIt).Normal[2] = -1;
		verticesIt++;
	}

	unsigned int k1, k2;
	// each stack is made of quad, quads are made of two triangles 1 stack = 2*3
	// m_stacks * m_sectors number of quads
	// m_stack * m_secotrs * 2 number of triangles
	// m_stack * m_secotrs * 6 number of indices
	// body indices = m_stack * m_secotrs * 6
	// base indices = m_sectors * 3 because the base has a center vertex and m_sectors vertices around the base
	unsigned int totalIndices = m_sectors * m_stacks * 6 + m_sectors * 3;
	indices.resize(m_sectors * m_stacks * 6 + m_sectors * 3);
	std::vector<unsigned int>::iterator indicesIt = indices.begin();
	for (int i = 0; i < m_stacks; i++) {
		k1 = i * (m_sectors + 1);
		k2 = k1 + m_sectors + 1;

		for (int j = 0; j < m_sectors; j++, k1++, k2++) {
			*indicesIt++ = k1;
			*indicesIt++ = k1 + 1;
			*indicesIt++ = k2;
			*indicesIt++ = k2;
			*indicesIt++ = k1 + 1;
			*indicesIt++ = k2 + 1;
		}
	}
	unsigned int baseIndex = (unsigned int)indices.size();
	for (int i = 0, k = baseVertexIndex + 1; i < m_sectors; i++, k++) {
		if (i < (m_sectors - 1)) {
			*indicesIt++ = baseVertexIndex;
			*indicesIt++ = k + 1;
			*indicesIt++ = k;
		}
		else {
			*indicesIt++ = baseVertexIndex;
			*indicesIt++ = baseVertexIndex + 1;
			*indicesIt++ = k;
		}
	}
}

Cone::Cone(float radius, float height, unsigned int sectors, unsigned int stacks)
	: m_radius(radius), m_height(height), m_sectors(sectors), m_stacks(stacks)
{
	if (m_radius < 0) m_radius = 0.1;
	if (m_height < 0) m_height = 0.1;
	if (m_sectors < 3) m_sectors = 3;
	if (m_stacks < 1) m_stacks = 1;
	if (m_radius > 1) m_radius = 1;
	if (m_height > 1) m_height = 1;
	if (m_sectors > 360) m_sectors = 360;
	Initalize();
}

Cone::~Cone()
{
}

void Cone::UpdateVerticesAndIndices()
{
	Initalize();
}

void Cone::UpdateVerticesAndIndices(float radius, float height, unsigned int sectors, unsigned int stacks)
{
	m_radius = radius;
	m_height = height;
	m_sectors = sectors;
	m_stacks = stacks;
	Initalize();
}

void Cone::UpdateParams()
{
	// ADD THIS TO THE OTHER SOLIDS
	if (ImGui::SliderFloat("cone radius", &m_radius, 0.0f, 1.0f)) {
		m_isUpdated = true;
	}
	if (ImGui::SliderFloat("cone height", &m_height, 0.0f, 1.0f)) {
		m_isUpdated = true;
	}
	if(ImGui::SliderInt("cone sectors", reinterpret_cast<int*>(&m_sectors), 3, m_maxSectors) ){
		m_isUpdated = true;
	}
	if(ImGui::SliderInt("cone stacks", reinterpret_cast<int*>(&m_stacks), 3, m_maxStacks) ){
		m_isUpdated = true;
	}
	if (m_isUpdated)
		UpdateVerticesAndIndices();
	m_isUpdated = false;
}
