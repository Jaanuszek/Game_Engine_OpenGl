#include "Sphere.h"

void Sphere::RenderSphere(float radius, unsigned int sectors, unsigned int stacks, std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	float const R = 1.0f / (float)(sectors - 1); //normalizing Sectors to be a value frome 0 to 1
	float const S = 1.0f / (float)(stacks - 1); //normalizing Stacks 

	//r sector step
	//s stack step
	int r, s; //r - sector(ring), s - stack


	vertices.resize(sectors * stacks * 6); //sectors * stacks * 6. 3 position, 3 colors
	std::vector<float>::iterator v = vertices.begin();
	for (r = 0; r < sectors; r++) {
		for (s = 0; s < stacks; s++) {
			float const x = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * cos(2 * glm::pi<float>() * r * R);
			float const y = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * sin(2 * glm::pi<float>() * r * R);
			float const z = sin(glm::half_pi<float>() - glm::pi<float>() * s * S);
			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			*v++ = (x + 1) * 0.5f;
			*v++ = (y + 1) * 0.5f;
			*v++ = (z + 1) * 0.5f;
		}
	}

	indices.resize(sectors * stacks * 6); // 6 indices per quad because every quad have 2 triangles and 2 triangles have 6 indices
	std::vector<unsigned int>::iterator i = indices.begin();
	for (r = 0; r < sectors; r++) {
		for (s = 0; s < stacks; s++) {
			*i++ = r * stacks + s;
			*i++ = r * stacks + (s + 1);
			*i++ = (r + 1) * stacks + (s + 1);

			*i++ = r * stacks + s;
			*i++ = (r + 1) * stacks + (s + 1);
			*i++ = (r + 1) * stacks + s;
		}
	}
}

Sphere::Sphere(float radius, unsigned int sectors, unsigned int stacks)
{
	RenderSphere(radius, sectors, stacks, verticesSphere, indicesSphere);
}

const std::vector<float>& Sphere::GetVertices(void) const
{
	return verticesSphere;
}

const std::vector<unsigned int>& Sphere::GetIndices(void) const
{
	return indicesSphere;
}

