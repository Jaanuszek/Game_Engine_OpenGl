#ifndef CUBOID_H
#define CUBOID_H

#include "Solid.h"

class Cuboid : public Solid {
private:
	float m_width;
	float m_height;
	float m_depth;
	void Initalize() override;
public:
	Cuboid(float width = 0.75, float height = 0.5, float depth = 0.5);
	~Cuboid() override;
};
#endif