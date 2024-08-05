#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Solid.h"

class Cube : public Solid {
private:
	void Initalize() override;
public:
	Cube();
	~Cube() override;
};

#endif