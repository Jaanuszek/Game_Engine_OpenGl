#ifndef CYLINDER_H
#define CYLINDER_H
#include "Solid.h"

class Cylinder : public Solid {
private:
	float m_radius;
	float m_height;
	unsigned int m_sectors;
	void Initalize() override;
	std::vector<float> getUnitCircleVertices();
public:
	Cylinder(float radius = 0.5, float height = 1, unsigned int m_sectors = 50);
	~Cylinder() override;
};
#endif