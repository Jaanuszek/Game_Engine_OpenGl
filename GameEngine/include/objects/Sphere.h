#ifndef SPHERE_H
#define SPHERE_H

#include "Solid.h"

class Sphere : public Solid {
private:
	float m_radius;
	unsigned int m_sectors;
	unsigned int m_stacks;
	int m_maxSectors = m_sectors;
	int m_maxStacks = m_stacks;
	void Initalize() override;
public:
	Sphere(float radius = 1.0f, unsigned int sectors = 24, unsigned int stacks = 48);
	~Sphere() override;
	void UpdateVerticesAndIndices() override;
	void UpdateVerticesAndIndices(float radius, unsigned int sectors, unsigned int stacks);
	void UpdateParams() override;
};

#endif
