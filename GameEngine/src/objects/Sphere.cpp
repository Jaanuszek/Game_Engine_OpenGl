#include "Sphere.h"

void Sphere::Initalize()
{
	float const R = 1.0f / (float)(m_sectors - 1); //normalizing Sectors to be a value frome 0 to 1
	float const S = 1.0f / (float)(m_stacks - 1); //normalizing Stacks 
	int r, s;
	vertices.resize(m_sectors * m_stacks);
	std::vector<Vertex>::iterator verticesIt = vertices.begin();
	for (r = 0; r < m_sectors; r++) {
		for (s = 0; s < m_stacks; s++) {
			float const x = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * cos(2 * glm::pi<float>() * r * R);
			float const y = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * sin(2 * glm::pi<float>() * r * R);
			float const z = sin(glm::half_pi<float>() - glm::pi<float>() * s * S);
			float const u = r * R;
			float const v = s * S;

			(*verticesIt).Position[0] = x * m_radius;
			(*verticesIt).Position[1] = y * m_radius;
			(*verticesIt).Position[2] = z * m_radius;

			(*verticesIt).TexCoords[0] = u;
			(*verticesIt).TexCoords[1] = v;

			(*verticesIt).Color[0] = (x + 1) * 0.5f;
			(*verticesIt).Color[1] = (y + 1) * 0.5f;
			(*verticesIt).Color[2] = (z + 1) * 0.5f;

			(*verticesIt).Normal[0] = x;
			(*verticesIt).Normal[1] = y;
			(*verticesIt).Normal[2] = z;
			verticesIt++;
		}
	}
	indices.resize(m_sectors * m_stacks * 6); // 6 indices per quad because every quad have 2 triangles and 2 triangles have 6 indices
	std::vector<unsigned int>::iterator i = indices.begin();
	for (r = 0; r < m_sectors; r++) {
		for (s = 0; s < m_stacks; s++) {
			*i++ = r * m_stacks + s;
			*i++ = r * m_stacks + (s + 1);
			*i++ = (r + 1) * m_stacks + (s + 1);

			*i++ = r * m_stacks + s;
			*i++ = (r + 1) * m_stacks + (s + 1);
			*i++ = (r + 1) * m_stacks + s;
		}
	}
}

Sphere::Sphere(float radius, unsigned int sectors, unsigned int stacks)
	:  m_radius(radius), m_sectors(sectors), m_stacks(stacks)
{
	Initalize();
}

Sphere::~Sphere()
{
	
}

void Sphere::Update(float radius, unsigned int sectors, unsigned int stacks)
{
	m_radius = radius;
	m_sectors = sectors;
	m_stacks = stacks;
	Initalize();
}