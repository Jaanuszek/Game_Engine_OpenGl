#ifndef CUBOID_H
#define CUBOID_H

#include "Solid.h"

class Cuboid : public Solid {
private:
	void Initalize() override;
public:
	Cuboid();
	~Cuboid() override;
};
#endif