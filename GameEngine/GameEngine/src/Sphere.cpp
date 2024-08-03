#include "Sphere.h"

void Sphere::RenderSphere(float radius, unsigned int sectors, unsigned int stacks, std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	float const R = 1.0f / (float)(sectors - 1); //normalizing Sectors to be a value frome 0 to 1
	float const S = 1.0f / (float)(stacks - 1); //normalizing Stacks 

	//r sector step
	//s stack step
	int r, s; //r - sector(ring), s - stack


	vertices.resize(sectors * stacks * 11); //sectors * stacks * 11. 3 position, 2 texture, 3 colors, 3 normals
	std::vector<float>::iterator verticesIt = vertices.begin();
	for (r = 0; r < sectors; r++) {
		for (s = 0; s < stacks; s++) {
			float const x = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * cos(2 * glm::pi<float>() * r * R);
			float const y = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * sin(2 * glm::pi<float>() * r * R);
			float const z = sin(glm::half_pi<float>() - glm::pi<float>() * s * S);
			float const u = r * R;
			float const v = s * S;

			*verticesIt++ = x * radius;
			*verticesIt++ = y * radius;
			*verticesIt++ = z * radius;

			*verticesIt++ = u;
			*verticesIt++ = v;

			*verticesIt++ = (x + 1) * 0.5f;
			*verticesIt++ = (y + 1) * 0.5f;
			*verticesIt++ = (z + 1) * 0.5f;

			*verticesIt++ = x;
			*verticesIt++ = y;		
			*verticesIt++ = z;
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

void Sphere::RenderSphereVertex(float radius, unsigned int sectors, unsigned int stacks, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	float const R = 1.0f / (float)(sectors - 1); //normalizing Sectors to be a value frome 0 to 1
	float const S = 1.0f / (float)(stacks - 1); //normalizing Stacks 
	int r, s;
	vertices.resize(sectors * stacks);
	std::vector<Vertex>::iterator verticesIt = vertices.begin();
	for (r = 0; r < sectors; r++) {
		for (s = 0; s < stacks; s++) {
			float const x = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * cos(2 * glm::pi<float>() * r * R);
			float const y = cos(glm::half_pi<float>() - glm::pi<float>() * s * S) * sin(2 * glm::pi<float>() * r * R);
			float const z = sin(glm::half_pi<float>() - glm::pi<float>() * s * S);
			float const u = r * R;
			float const v = s * S;

			(*verticesIt).Position[0] = x * radius;
			(*verticesIt).Position[1] = y * radius;
			(*verticesIt).Position[2] = z * radius;

			(*verticesIt).TexCoords[0] = u;
			(*verticesIt).TexCoords[1] = v;
			
			(*verticesIt).Color[0] = (x+1) * 0.5f;
			(*verticesIt).Color[1] = (y+1) * 0.5f;
			(*verticesIt).Color[2] = (z+1) * 0.5f;
			
			(*verticesIt).Normal[0] = x;
			(*verticesIt).Normal[1] = y;
			(*verticesIt).Normal[2] = z;
			verticesIt++;
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
	//RenderSphere(radius, sectors, stacks, verticesSphere, indicesSphere);
	RenderSphereVertex(radius, sectors, stacks, verticesSphereVertex, indicesSphere);
}

const std::vector<float>& Sphere::GetVertices(void) const
{
	return verticesSphere;
}

const std::vector<Vertex>& Sphere::GetVerticesVertex(void) const
{
	return verticesSphereVertex;
}

const std::vector<unsigned int>& Sphere::GetIndices(void) const
{
	return indicesSphere;
}

