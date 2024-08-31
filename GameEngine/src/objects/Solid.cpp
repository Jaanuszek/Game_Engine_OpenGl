#include "Solid.h"

std::vector<float> Solid::getUnitCircleVertices(unsigned int sectorCount) {
    const float PI = glm::pi<float>();
    const float sectorStep = 2 * PI / sectorCount; //360 / m_sectors
    float sectorAngle;

    std::vector<float> unitCircleVertices;
    for (int i = 0; i <= sectorCount; ++i) {
        sectorAngle = i * sectorStep; // fi
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(sin(sectorAngle)); // y 
        unitCircleVertices.push_back(0);                // 0 because i want to render xy plane
    }
    return unitCircleVertices;
}