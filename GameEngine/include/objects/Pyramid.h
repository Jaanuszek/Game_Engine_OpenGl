#ifndef PYRAMID_H
#define PYRAMID_H

#include "Solid.h"

class Pyramid : public Solid {
private:
	void Initalize() override;
	void CalculateNormals();
public:
	Pyramid();
	~Pyramid() override;
	void UpdateVerticesAndIndices() override;
	void UpdateParams() override;
};

#endif
