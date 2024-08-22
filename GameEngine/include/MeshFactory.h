#include "objects/Solid.h"
#include "Mesh.h"
#include <vector>

class MeshFactory {
public:
	static Mesh CreateMesh (Solid& solid, std::vector<Texture>& textures);
};