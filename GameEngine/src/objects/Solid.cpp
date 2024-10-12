#include "Solid.h"
std::vector<float> Solid::getUnitCircleVertices(unsigned int sectorCount) {
    const float sectorStep = 2 * PI / sectorCount; //360 / m_sectors
    float sectorAngle;
    std::vector<float> unitCircleVertices;
	unitCircleVertices.reserve(static_cast<size_t>(sectorCount) * 3 + 3); // 3 components per vertex
    for (int i = 0; i <= sectorCount; ++i) {
        sectorAngle = i * sectorStep; // fi
        unitCircleVertices.emplace_back(cos(sectorAngle)); // x
        unitCircleVertices.emplace_back(sin(sectorAngle)); // y 
        unitCircleVertices.emplace_back(0);                // 0 because i want to render xy plane
    }
    return unitCircleVertices;
}
