#ifndef CONE_H
#define CONE_H
#include "Solid.h"

class Cone : public Solid {
private:
	float m_radius;
	float m_height;
	unsigned int m_sectors;
	unsigned int m_stacks;
	unsigned int m_maxSectors = m_sectors;
	unsigned int m_maxStacks = m_stacks;
	std::vector<float> getSideNormals() const;
	void Initalize() override;
public:
	Cone(float radius = 0.5f, float height = 1.0f, unsigned int sectors = 50, unsigned int stacks = 10);
	~Cone() override;
	void UpdateVerticesAndIndices() override;
	void UpdateVerticesAndIndices(float radius, float height, unsigned int sectors, unsigned int stacks);
	void UpdateParams() override;
};

#endif
