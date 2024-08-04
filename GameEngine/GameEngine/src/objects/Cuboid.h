#ifndef CUBOID_H
#define CUBOID_H

#include "Solid.h"

class Cuboid : public Solid {
public:
	Cuboid() {
		indicesSize = 1;
	};
	~Cuboid() override;
	void Initalize() override;
};
#endif