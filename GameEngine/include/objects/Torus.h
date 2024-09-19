#ifndef TORUS_H
#define TORUS_H

#include "Solid.h"

class Torus : public Solid
{
private:
	float m_minorRadius;
	float m_majorRadius;
	unsigned int m_sectors;
	unsigned int m_sides;
	int m_maxSectors = m_sectors;
	int m_maxSides = m_sides;
	void Initalize() override;
public:
	Torus(float minorRadius = 0.2f, float majorRadius = 0.5f, unsigned int sectors = 48, unsigned int side = 24);
	~Torus() override;
	void UpdateVerticesAndIndices() override;
	void UpdateVerticesAndIndices(float minorRadius, float majorRadius, unsigned int sectors, unsigned int sides);
	void UpdateParams();
};

#endif