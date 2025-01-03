#include "Cylinder.h"

// in case of any problems take a look at the post incremented values in loops, maybe it will be better if they were pre incremented

void Cylinder::Initalize()
{
	int verticesSize = (m_sectors + 1) * 4; // 2 for top and bottom center points, 2 for top and bottom circle vertices
	vertices.resize(verticesSize);
    std::vector<Vertex>::iterator verticesIt = vertices.begin();
	std::vector<float> unitVertices = getUnitCircleVertices(m_sectors);
	unsigned int baseCenterIndex = 0;
	//code for generating the walls of cylinder
	for (int i = 0; i < 2; i++) { //for positive and negative height
		float h = -m_height / 2.0f + i * m_height;
		float t = 1.0f - i; //tex cord [1,0]
		if (i == 0) {//bottom base
			for (int j = 0, k = 0; j <= m_sectors; j++, k += 3) {
				float ux = unitVertices[k];
				float uy = unitVertices[k + 1];
				float uz = unitVertices[k + 2];
				(*verticesIt).Position[0] = ux * m_radius * m_bottomBaseRadius;
				(*verticesIt).Position[1] = uy * m_radius * m_bottomBaseRadius;
				(*verticesIt).Position[2] = h;
				(*verticesIt).TexCoords[0] = (float)j / m_sectors;
				(*verticesIt).TexCoords[1] = t;
				(*verticesIt).Normal[0] = ux;
				(*verticesIt).Normal[1] = uy;
				(*verticesIt).Normal[2] = uz;
				verticesIt++;
				baseCenterIndex++;
			}
		}
		else {
			for (int j = 0, k = 0; j <= m_sectors; j++, k += 3) {
				float ux = unitVertices[k];
				float uy = unitVertices[k + 1];
				float uz = unitVertices[k + 2];
				(*verticesIt).Position[0] = ux * m_radius * m_topBaseRadius;
				(*verticesIt).Position[1] = uy * m_radius * m_topBaseRadius;
				(*verticesIt).Position[2] = h;
				(*verticesIt).TexCoords[0] = (float)j / m_sectors;
				(*verticesIt).TexCoords[1] = t;
				(*verticesIt).Normal[0] = ux;
				(*verticesIt).Normal[1] = uy;
				(*verticesIt).Normal[2] = uz;
				verticesIt++;
				baseCenterIndex++;
			}
		}
	}
	//these indexes are wrong, baseCenterIndex should be exactly in the middle of the vertices
	unsigned int topCenterIndex = baseCenterIndex + m_sectors + 1;
	for (int i = 0; i < 2; i++) {
		float h = -m_height / 2.0f + i * m_height; //z value in terms -h/2, h/2
		float nz = -1 + i * 2;						// z value of normal [-1, 1]
		//coords of center point
		(*verticesIt).Position[0] = 0;
		(*verticesIt).Position[1] = 0;
		(*verticesIt).Position[2] = h;
		(*verticesIt).TexCoords[0] = 0.5f;
		(*verticesIt).TexCoords[1] = 0.5f;
		(*verticesIt).Normal[0] = 0;
		(*verticesIt).Normal[1] = 0;
		(*verticesIt).Normal[2] = nz;
		verticesIt++;
		if (i == 0) {
			for (int j = 0, k = 0; j < m_sectors; ++j, k += 3) {
				float ux = unitVertices[k];
				float uy = unitVertices[k + 1];
				(*verticesIt).Position[0] = ux * m_radius * m_bottomBaseRadius;
				(*verticesIt).Position[1] = uy * m_radius * m_bottomBaseRadius;
				(*verticesIt).Position[2] = h;
				(*verticesIt).TexCoords[0] = -ux * 0.5f + 0.5f;
				(*verticesIt).TexCoords[1] = -uy * 0.5f + 0.5f;
				(*verticesIt).Normal[0] = 0;
				(*verticesIt).Normal[1] = 0;
				(*verticesIt).Normal[2] = nz;
				verticesIt++;
			}
		}
		else {
			for (int j = 0, k = 0; j < m_sectors; ++j, k += 3) {
				float ux = unitVertices[k];
				float uy = unitVertices[k + 1];
				(*verticesIt).Position[0] = ux * m_radius * m_topBaseRadius;
				(*verticesIt).Position[1] = uy * m_radius * m_topBaseRadius;
				(*verticesIt).Position[2] = h;
				(*verticesIt).TexCoords[0] = -ux * 0.5f + 0.5f;
				(*verticesIt).TexCoords[1] = -uy * 0.5f + 0.5f;
				(*verticesIt).Normal[0] = 0;
				(*verticesIt).Normal[1] = 0;
				(*verticesIt).Normal[2] = nz;
				verticesIt++;
			}
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

Cylinder::Cylinder(float radius, float height, unsigned int sectors, float bottomBaseRadius, float topBaseRadius)
	: m_radius(radius), m_height(height), m_sectors(sectors), m_bottomBaseRadius(bottomBaseRadius), m_topBaseRadius(topBaseRadius)
{
	if (m_radius < 0) m_radius = 0.1;
	if (m_height < 0) m_height = 0.1;
	if (m_sectors < 3) m_sectors = 3;
	if (m_radius > 1) m_radius = 1;
	if (m_height > 1) m_height = 1;
	if (m_sectors > 360) m_sectors = 360;
	if (m_bottomBaseRadius < 0) m_bottomBaseRadius = 0.1;
	if (m_bottomBaseRadius > 1) m_bottomBaseRadius = 1;
	if (m_topBaseRadius < 0) m_topBaseRadius = 0.1;
	if (m_topBaseRadius > 1) m_topBaseRadius = 1;
	Initalize();
}

Cylinder::~Cylinder()
{
}

void Cylinder::UpdateVerticesAndIndices() {
	Initalize();
}

void Cylinder::UpdateParams() {
	ImGui::Begin("Cylinder update");
	ImGui::SliderFloat("Cylinder radius", &m_radius, 0.01f, 1.0f);
	ImGui::SliderFloat("Cylinder height", &m_height, 0.01f, 1.0f);
	ImGui::SliderInt("Cylinder sectors", reinterpret_cast<int*>(&m_sectors), 4, m_maxSectors);
	ImGui::SliderFloat("Cylinder bottom base radius", &m_bottomBaseRadius, 0.01f, 1.0f);
	ImGui::SliderFloat("Cylinder top base radius", &m_topBaseRadius, 0.01f, 1.0f);
	ImGui::End();
	UpdateVerticesAndIndices();
}