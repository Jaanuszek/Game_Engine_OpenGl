#ifndef CUBE_H
#define CUBE_H

#include "Solid.h"

class Cube : public Solid {
private:
	void Initalize() override;
public:
	Cube();
	~Cube() override;
};

#endif