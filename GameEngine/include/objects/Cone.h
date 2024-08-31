#ifndef CONE_H
#define CONE_H
#include "Solid.h"

class Cone : public Solid {
private:
	float m_radius;
	float m_height;
	unsigned int m_sectors;
	unsigned int m_stacks;
	std::vector<float> getSideNormals();
	void Initalize() override;
public:
	Cone(float radius = 0.5, float height = 1, unsigned int sectors = 50, unsigned int stacks = 10);
	~Cone() override;
};

#endif
