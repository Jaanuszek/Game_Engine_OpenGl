#ifndef CYLINDER_H
#define CYLINDER_H
#include "Solid.h"

class Cylinder : public Solid {
private:
	float m_radius;
	float m_height;
	unsigned int m_sectors;
	float m_bottomBaseRadius;
	float m_topBaseRadius;
	void Initalize() override;
public:
	Cylinder(float radius = 0.5, float height = 1, unsigned int sectors = 50, float bottomBaseRadius = 0.5, float topBaseRadius = 0.1);
	~Cylinder() override;
};
#endif