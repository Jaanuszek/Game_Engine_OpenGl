#ifndef SPHERE_H
#define SPHERE_H

#include "Solid.h"

class Sphere : public Solid {
private:
	void Initalize() override;
	float m_radius;
	unsigned int m_sectors;
	unsigned int m_stacks;
public:
	Sphere(float radius, unsigned int sectors, unsigned int stacks);
	~Sphere() override;
};

#endif
