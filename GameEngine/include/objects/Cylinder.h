#ifndef SOLID_H
#define SOLID_H
#include "Solid.h"

class Cylinder : public Solid {
private:
	float m_radius;
	float m_height;
	unsigned int m_sectors;
	void Initalize() override;
	std::vector<float> getUnitCircleVertices();
public:
	Cylinder(float radius = 0.5, float height = 0.5, unsigned int m_sectors = 3);
	~Cylinder() override;
};
#endif